/*
//Class Header
#include "COFFImporter.h"
//Namespaces
using namespace ACStdLib::Math;

//Private methods
CString COFFImporter::ReadNextValue(AInputStream &refInput)
{
	char c;
	CString buffer;

	//search for begin
	while(true)
	{
		c = (char)refInput.ReadByte();
		if(refInput.HitEnd())
			ASSERT(0);

		switch(c)
		{
		case '\r':
		case '\n':
		case ' ':
			//do nothing
			break;
		default:
			goto foundBegin;
		}
	}

	ASSERT(0);
foundBegin:;
	buffer += c;

	while(true)
	{
		c = (char)refInput.ReadByte();
		if(refInput.HitEnd())
			ASSERT(0);

		switch(c)
		{
		case '\r':
		case '\n':
		case ' ':
			goto foundEnd;
		default:
			buffer += c;
		}
	}

	ASSERT(0);
foundEnd:;

	return buffer;
}

//Public methods
CScene *COFFImporter::ImportScene(ASeekableInputStream &refInput, const CString &refName)
{
	uint32 i, faceType;
	Math::CVector3 vertex;
	SFace face;
	CMesh *pMesh;
	CScene *pScene;
	
	CBufferedInputStream bufferedInput(refInput);

	pMesh = new CMesh(refName);
	pScene = new CScene;

	pScene->AddMesh(pMesh);
	
	bufferedInput.Skip(3); //"OFF"

	pMesh->SetNumberOfPositions(this->ReadUInt(bufferedInput));
	pMesh->SetNumberOfFaces(this->ReadUInt(bufferedInput));
	this->ReadUInt(bufferedInput); //nEdges
	
	//read vertices
	for(i = 0; i < pMesh->GetNumberOfPositions(); i++)
	{
		vertex.x = this->ReadFloat(bufferedInput);
		vertex.y = this->ReadFloat(bufferedInput);
		vertex.z = this->ReadFloat(bufferedInput);
		
		pMesh->SetPosition(i, vertex);
	}

	//read faces
	for(i = 0; i < pMesh->GetNumberOfFaces(); i++)
	{
		faceType = this->ReadUInt(bufferedInput);

		ASSERT(faceType == 3 || faceType == 4);

		face.faceType = (uint8)faceType;
		face.materialIndex = 0;
		
		face.vertexTable[0].positionIndex = this->ReadUInt(bufferedInput);
		face.vertexTable[1].positionIndex = this->ReadUInt(bufferedInput);
		face.vertexTable[2].positionIndex = this->ReadUInt(bufferedInput);
		if(faceType == 4)
			face.vertexTable[3].positionIndex = this->ReadUInt(bufferedInput);

		//use indices also for normals and UV
		for(uint8 j = 0; j < 4; j++)
			face.vertexTable[j].uvIndex = 0;
		
		pMesh->SetFace(i, face);
	}

	//there are no UV's :S we can't generate this data => set all UVs to zero
	pMesh->SetNumberOfUVs(1);
	pMesh->SetUV(0, CVector2());
	
	pMesh->ComputeVertexNormals();

	return pScene;
}
*/