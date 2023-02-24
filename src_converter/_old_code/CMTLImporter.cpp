//Class Header
#include "CMTLImporter.h"
//Namespaces
using namespace ACStdLib::Math;

//Private methods
CString CMTLImporter::ReadNextToken(AInputStream &refInput)
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

void CMTLImporter::SkipToNextLine(AInputStream &refInput)
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

void CMTLImporter::SkipToNextToken(AInputStream &refInput)
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
CScene *CMTLImporter::ImportScene(ASeekableInputStream &refInput, const CString &refName)
{
	CScene *pScene;
	CMaterial *pCurrentMaterial;
	CString command;

	pCurrentMaterial = nullptr;

	CBufferedInputStream bufferedInput(refInput);

	pScene = new CScene;

	this->lookahead = ' '; //make read new lookahead
	while(true)
	{
		command = this->ReadNextToken(bufferedInput);
		if(bufferedInput.HitEnd())
			break;
		
		if(command == "bump")
		{
			//bump map texture
			this->ReadNextToken(bufferedInput);
		}
		else if(command == "d")
		{
			//dissolved
			this->ReadFloat(bufferedInput);
		}
		else if(command == "Ka")
		{
			//ambient color
			this->ReadFloat(bufferedInput);
			this->ReadFloat(bufferedInput);
			this->ReadFloat(bufferedInput);
		}
		else if(command == "Kd")
		{
			pCurrentMaterial->diffuseColor.x = this->ReadFloat(bufferedInput);
			pCurrentMaterial->diffuseColor.y = this->ReadFloat(bufferedInput);
			pCurrentMaterial->diffuseColor.z = this->ReadFloat(bufferedInput);
		}
		else if(command == "Ke")
		{
			//emissive color
			this->ReadFloat(bufferedInput);
			this->ReadFloat(bufferedInput);
			this->ReadFloat(bufferedInput);
		}
		else if(command == "Ks")
		{
			//specular color
			this->ReadFloat(bufferedInput);
			this->ReadFloat(bufferedInput);
			this->ReadFloat(bufferedInput);
		}
		else if(command == "map_bump")
		{
			//bump map texture
			this->ReadNextToken(bufferedInput);
		}
		else if(command == "map_Bump")
		{
			//bump map texture
			this->ReadNextToken(bufferedInput);
		}
		else if(command == "map_Kd")
		{
			CString textureName;

			textureName = this->ReadNextToken(bufferedInput);
			pCurrentMaterial->SetTextureFromFileName(textureName);
		}
		else if(command == "map_Ks")
		{
			//specular map texture
			this->ReadNextToken(bufferedInput);
		}
		else if(command == "newmtl")
		{
			CString name;

			name = this->ReadNextToken(bufferedInput);
			pCurrentMaterial = new CMaterial(name);

			pScene->AddMaterial(pCurrentMaterial);
		}
		else if(command == "Ni")
		{
			//optical density
			this->ReadFloat(bufferedInput);
		}
		else if(command == "Ns")
		{
			//specular exponent
			this->ReadNextToken(bufferedInput);
		}
		else if(command == "illum")
		{
			//illumination flag
			this->ReadNextToken(bufferedInput);
		}
		else
		{
			ASSERT_MSG(false, "Illegal command: " + command);
		}
	}

	return pScene;
}