//Class header
#include "CACTextureExporter.h"
//Local
#include "ACFF.h"

//Private methods
void CACTextureExporter::ExportTexture(const CTexture &refTexture, AOutputStream &refOutput)
{
	byte textureCodingType;
	ECodecId codec;
	IEncoder *pEncoder;
	SPacket packet;
	
	//first encode texture
	CVideoFrame frame((AImage *)&refTexture.GetImage());
	
	if(refTexture.HasAlpha())
	{
		codec = ECodecId::S3TC_DXT5;
		textureCodingType = 1; //DXT5
	}
	else
	{
		codec = ECodecId::S3TC_DXT1;
		textureCodingType = 0; //DXT1
	}
	
	pEncoder = ICodec::GetCodec(codec)->CreateEncoder();
	
	pEncoder->Encode(frame, packet);

	//file header
	refOutput.WriteUInt32BE(ACFF_SIGNATURE);
	refOutput.WriteUInt16LE(ACFF_TYPE_TEXTURE);

	//texture header
	refOutput.WriteUInt16LE(refTexture.GetImage().GetWidth());
	refOutput.WriteUInt16LE(refTexture.GetImage().GetHeight());
	refOutput.WriteByte(textureCodingType);
	refOutput.WriteUInt32LE(packet.size);
								
	//data
	refOutput.WriteBytes(packet.pData, packet.size);

	//clean up
	frame.SetImage(nullptr); //careful with cleaning up here
	FreePacket(packet);
	delete pEncoder;
}

//Public methods
void CACTextureExporter::ExportScene(const CScene &refScene, const CPath &refDirectory)
{
	for(CTexture *const& refpTexture : refScene.GetTextures())
	{
		CFileOutputStream output(refDirectory / (refpTexture->GetName() + ".actex"));

		this->ExportTexture(*refpTexture, output);
	}
}