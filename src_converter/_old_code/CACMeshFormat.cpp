//Class Header
#include "CACMeshFormat.h"
//Local
#include "ACFF.h"
#include "CACMeshExporter.h"

//Public methods
IExporter *CACMeshFormat::CreateExporter() const
{
	return new CACMeshExporter;
}

IImporter *CACMeshFormat::CreateImporter() const
{
	ASSERT(0);

	return NULL;
}

CString CACMeshFormat::GetFileExtension() const
{
	return "acmsh";
}

CString CACMeshFormat::GetName() const
{
	return "Amir Czwink File Formats - Mesh";
}

float32 CACMeshFormat::MatchesFormat(byte *pBuffer, uint32 bufferSize) const
{
	CBufferInputStream input(pBuffer, bufferSize);

	if(bufferSize < 6)
		return -1;

	if(input.ReadUInt32BE() == ACFF_SIGNATURE)
	{
		if(input.ReadUInt16LE() == ACFF_TYPE_MESH_RENDER_OPT)
			return 1;
	}

	return 0;
}