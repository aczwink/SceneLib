//Class Header
#include "COBJImporter.h"
//Namespaces
using namespace ACStdLib::Math;

//Private methods
void COBJImporter::ReadFaceValue(SVertexTable &refVT, AInputStream &refInput)
{
	refVT.positionIndex = this->ReadUInt(refInput) - 1 - this->indexBasePos;
	ASSERT(this->ReadNextToken(refInput) == '/');

	refVT.uvIndex = this->ReadUInt(refInput) - 1 - this->indexBaseUV;
	ASSERT(this->ReadNextToken(refInput) == '/');

	refVT.normalsIndex = this->ReadUInt(refInput) - 1 - this->indexBaseNormal;
}

CString COBJImporter::ReadNextToken(AInputStream &refInput)
{
	CString buffer;

	this->SkipToNextToken(refInput);

	if(this->lookahead == '/')
	{
		this->lookahead = refInput.ReadByte();
		return "/";
	}

	while(!refInput.HitEnd())
	{
		switch(this->lookahead)
		{
		case '\r':
		case '\n':
		case ' ':
		case '/':
			return buffer;
		default:
			buffer += (char)this->lookahead;
		}

		this->lookahead = refInput.ReadByte();
	}

	return buffer;
}

void COBJImporter::SkipToNextLine(AInputStream &refInput)
{
	while(true)
	{
		this->lookahead = refInput.ReadByte();
		if(refInput.HitEnd())
			ASSERT(0);

		if(this->lookahead == '\n')
		{
			this->lookahead = refInput.ReadByte();
			break;
		}
	}
}

void COBJImporter::SkipToNextToken(AInputStream &refInput)
{
	while(true)
	{
		switch(this->lookahead)
		{
		case ' ':
		case '\r':
		case '\n':
			{
				//skip
				this->lookahead = refInput.ReadByte();
				if(refInput.HitEnd())
					return;
			}
			break;
		case '#':
			this->SkipToNextLine(refInput);
			break;
		default:
			return;
		}
	}
}

//Public methods
CScene *COBJImporter::ImportScene(ASeekableInputStream &refInput, const CString &refName)
{
	CScene *pScene;
	CMesh *pCurrentMesh;
	CString command;

	pCurrentMesh = nullptr;

	CBufferedInputStream bufferedInput(refInput);

	pScene = new CScene;

	this->lookahead = ' '; //make read new lookahead
	while(true)
	{
		command = this->ReadNextToken(bufferedInput);
		if(bufferedInput.HitEnd())
			break;

		if(command == "f")
		{
			SFace face;

			//TODO: models with more than 3 vertices are not supported currently
			//TODO: also correctly parse which kind of indices are available

			face.faceType = 3;
			face.materialIndex = this->currentMaterialIndex;

			this->ReadFaceValue(face.vertexTable[0], bufferedInput);
			this->ReadFaceValue(face.vertexTable[1], bufferedInput);
			this->ReadFaceValue(face.vertexTable[2], bufferedInput);

			pCurrentMesh->AddFace(face);
		}
		else if(command == "g")
		{
			//group name
			//TODO: this can be more than one
			this->ReadNextToken(bufferedInput);
		}
		else if(command == "mtllib")
		{
			this->ReadNextToken(bufferedInput);
		}
		else if(command == "o")
		{
			CString name;

			if(pCurrentMesh == nullptr)
			{
				this->indexBaseNormal = 0;
				this->indexBasePos = 0;
				this->indexBaseUV = 0;
			}
			else
			{
				this->indexBaseNormal += pCurrentMesh->GetNumberOfNormals();
				this->indexBasePos += pCurrentMesh->GetNumberOfPositions();
				this->indexBaseUV += pCurrentMesh->GetNumberOfUVCoordinates();
			}

			name = this->ReadNextToken(bufferedInput);
			pCurrentMesh = new CMesh(name);

			pScene->AddMesh(pCurrentMesh);
		}
		else if(command == "s")
		{
			this->ReadNextToken(bufferedInput);
		}
		else if(command == "usemtl")
		{
			CString name;

			name = this->ReadNextToken(bufferedInput);
			this->currentMaterialIndex = pCurrentMesh->AddMaterial(name);
		}
		else if(command == "v")
		{
			CVector3 pos;

			pos.x = this->ReadFloat(bufferedInput);
			pos.y = this->ReadFloat(bufferedInput);
			pos.z = this->ReadFloat(bufferedInput);

			pCurrentMesh->AddPosition(pos);
		}
		else if(command == "vn")
		{
			CVector3 normal;

			normal.x = this->ReadFloat(bufferedInput);
			normal.y = this->ReadFloat(bufferedInput);
			normal.z = this->ReadFloat(bufferedInput);

			pCurrentMesh->AddNormal(normal);
		}
		else if(command == "vt")
		{
			CVector2 uv;

			uv.x = this->ReadFloat(bufferedInput);
			uv.y = this->ReadFloat(bufferedInput);

			pCurrentMesh->AddUV(uv);
		}
		else
		{
			ASSERT_MSG(false, "Illegal command: " + command);
		}
	}

	return pScene;
}