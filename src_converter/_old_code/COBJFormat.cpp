//Class Header
#include "COBJFormat.h"
//Local
#include "COBJImporter.h"

//Public methods
IExporter *COBJFormat::CreateExporter() const
{
	ASSERT(0);

	return NULL;
}

IImporter *COBJFormat::CreateImporter() const
{
	return new COBJImporter;
}

CString COBJFormat::GetFileExtension() const
{
	return "obj";
}

CString COBJFormat::GetName() const
{
	return "Wavefront OBJ";
}

float32 COBJFormat::MatchesFormat(byte *pBuffer, uint32 bufferSize) const
{
	return 0;
}