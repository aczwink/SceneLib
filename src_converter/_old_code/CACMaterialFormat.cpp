//Class Header
#include "CACMaterialFormat.h"
//Local
#include "ACFF.h"
#include "CACMaterialExporter.h"

//Public methods
IExporter *CACMaterialFormat::CreateExporter() const
{
	return new CACMaterialExporter;
}

IImporter *CACMaterialFormat::CreateImporter() const
{
	ASSERT(0);

	return NULL;
}

CString CACMaterialFormat::GetFileExtension() const
{
	return "acmat";
}

CString CACMaterialFormat::GetName() const
{
	return "Amir Czwink File Formats - Material";
}

float32 CACMaterialFormat::MatchesFormat(byte *pBuffer, uint32 bufferSize) const
{
	CBufferInputStream input(pBuffer, bufferSize);

	if(bufferSize < 6)
		return -1;

	if(input.ReadUInt32BE() == ACFF_SIGNATURE)
	{
		if(input.ReadUInt16LE() == ACFF_TYPE_MATERIAL)
			return 1;
	}

	return 0;
}