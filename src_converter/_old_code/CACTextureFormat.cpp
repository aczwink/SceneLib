//Class Header
#include "CACTextureFormat.h"
//Local
#include "ACFF.h"
#include "CACTextureExporter.h"

//Public methods
IExporter *CACTextureFormat::CreateExporter() const
{
	return new CACTextureExporter;
}

IImporter *CACTextureFormat::CreateImporter() const
{
	ASSERT(0);

	return NULL;
}

CString CACTextureFormat::GetFileExtension() const
{
	return "actex";
}

CString CACTextureFormat::GetName() const
{
	return "Amir Czwink File Formats - Texture";
}

float32 CACTextureFormat::MatchesFormat(byte *pBuffer, uint32 bufferSize) const
{
	CBufferInputStream input(pBuffer, bufferSize);
	
	if(bufferSize < 6)
		return -1;
	
	if(input.ReadUInt32BE() == ACFF_SIGNATURE)
	{
		if(input.ReadUInt16LE() == ACFF_TYPE_TEXTURE)
			return 1;
	}
	
	return 0;
}