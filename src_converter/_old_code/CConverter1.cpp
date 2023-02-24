//Class header
#include "CConverter.h"

//Prototypes
const ISceneFormat *GetFormatFromFileExtension(const CString &refFileExtension);
const CLinkedList<const ISceneFormat *> &GetFormats();

//Constructor
CConverter::CConverter(const CPath &refInputPath, const CPath &refOutputPath, const CString &refOutputFormat)
{
	this->inputPath = refInputPath;
	this->outputPath = refOutputPath;
	this->outputFormat = refOutputFormat;

	this->pScene = new CScene;
}

//Destructor
CConverter::~CConverter()
{
	delete this->pScene;
}

//Private methods
const IFormat *CConverter::CheckAVFormat(ASeekableInputStream &refInput, const CString &refFileExtension)
{
	const IFormat *pFormat;

	//find format
	pFormat = IFormat::Find(refInput);
	if(!pFormat)
	{
		//second try by extension
		pFormat = IFormat::FindByExtension(refFileExtension);
	}

	return pFormat;
}

const ISceneFormat *CConverter::CheckSceneFormat(ASeekableInputStream &refInput, const CString &refFileExtension)
{
	byte buffer[4];
	
	const CLinkedList<const ISceneFormat *> &refFormats = GetFormats();

	refInput.ReadBytes(buffer, sizeof(buffer));

	for(const ISceneFormat *const &refpFormat : refFormats)
	{
		if(refpFormat->MatchesFormat(buffer, sizeof(buffer)) == 1)
		{
			refInput.SetCurrentOffset(0);
			return refpFormat;
		}
	}
	
	for(const ISceneFormat *const &refpFormat : refFormats)
	{
		if(refpFormat->GetFileExtension() == refFileExtension.ToLowercase())
		{
			refInput.SetCurrentOffset(0);
			return refpFormat;
		}
	}

	refInput.SetCurrentOffset(0);
	return nullptr;
}

bool CConverter::ImportAV(ASeekableInputStream &refInput, const IFormat *pFormat, const CString &refTitle)
{
	ADemuxer *pDemuxer;
	ADecoder *pDecoder;
	AFrame *pFrame;
	SPacket packet;

	//get demuxer
	pDemuxer = pFormat->CreateDemuxer(refInput);
	if(!pDemuxer)
		return false;

	//for most formats reading the header should give all the info needed
	pDemuxer->ReadHeader();
	pDemuxer->FindStreamInfo();

	//stream evaluation
	ASSERT(pDemuxer->GetNumberOfStreams() == 1);
	ASSERT(pDemuxer->GetStream(0)->GetType() == EDataType::Video);
	pDecoder = pDemuxer->GetStream(0)->GetDecoder();

	//get data
	if(!pDecoder->IsFrameReady())
	{
		if(!pDemuxer->ReadFrame(packet))
		{
			delete pDemuxer;
			return false;
		}

		pDecoder->Decode(packet);
		FreePacket(packet);
	}

	pFrame = pDecoder->GetNextFrame();

	if((CVideoFrame *)pFrame)
	{
		CVideoFrame *pVideoFrame;
		AImage *pImage;

		pVideoFrame = (CVideoFrame *)pFrame;
		pImage = pVideoFrame->GetImage();
		pVideoFrame->SetImage(nullptr); //take away image from frame

		this->pScene->AddTexture(new CTexture(refTitle, pImage));
		
		delete pFrame;
	}

	//clean up
	delete pDemuxer;

	return true;
}

void CConverter::ImportFile(const CPath &refPath)
{
	bool success;
	const IFormat *pAVFormat;
	const ISceneFormat *pSceneFormat;
	
	success = false;
	pSceneFormat = nullptr;
	
	CFileInputStream file(refPath);
	
	pAVFormat = this->CheckAVFormat(file, refPath.GetFileExtension());
	if(!pAVFormat)
		pSceneFormat = this->CheckSceneFormat(file, refPath.GetFileExtension());
	
	if(pAVFormat || pSceneFormat)
		stdOut << "Importing file '" << refPath << "'..." << endl;
	
	if(pAVFormat)
		success = this->ImportAV(file, pAVFormat, refPath.GetTitle());
	else if(pSceneFormat)
		success = this->ImportScene(file, pSceneFormat, refPath.GetTitle());
	
	if(!success)
		stdErr << "Failed to import '" << refPath << "'" << endl;
}

bool CConverter::ImportScene(ASeekableInputStream &refInput, const ISceneFormat *pFormat, const CString &refTitle)
{
	IImporter *pImporter;
	CScene *pScene;
	
	pImporter = pFormat->CreateImporter();
	
	pScene = pImporter->ImportScene(refInput, refTitle);
	if(!pScene)
	{
		stdErr << "Failed to import scene" << endl;
		delete pImporter;

		return false;
	}

	this->pScene->MoveAdd(*pScene);

	delete pScene;
	delete pImporter;
	
	return true;
}

void CConverter::OutputAC()
{
	if(!this->pScene->GetMaterials().IsEmpty())
		this->OutputAC("acmat", "materials");
	if(!this->pScene->GetMeshes().IsEmpty())
		this->OutputAC("acmsh", "meshes");
	if(!this->pScene->GetTextures().IsEmpty())
		this->OutputAC("actex", "textures");
}

void CConverter::OutputAC(const CString &refFileExtension, const CString &refDirName)
{
	const ISceneFormat *pOutputFormat;
	IExporter *pExporter;
	CPath dirPath;
	
	pOutputFormat = GetFormatFromFileExtension(refFileExtension);
	pExporter = pOutputFormat->CreateExporter();
	
	//create directories first
	dirPath = this->outputPath / refDirName;
	dirPath.CreateDirectoryTree();

	pExporter->ExportScene(*this->pScene, dirPath);

	delete pExporter;
}

//Public methods
void CConverter::Convert()
{
	//import first
	if(this->inputPath.IsDirectory())
	{
		NOT_IMPLEMENTED_ERROR;
	}
	else
	{
		this->ImportFile(this->inputPath);
	}

	//now export
	stdOut << "Exporting..." << endl;

	if(this->outputFormat == "AC")
	{
		this->OutputAC();
	}
	else
	{
		NOT_IMPLEMENTED_ERROR;
	}
}