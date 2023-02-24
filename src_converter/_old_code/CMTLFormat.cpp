//Class Header
#include "CMTLFormat.h"
//Local
#include "CMTLImporter.h"

//Public methods
IExporter *CMTLFormat::CreateExporter() const
{
	ASSERT(0);

	return NULL;
}

IImporter *CMTLFormat::CreateImporter() const
{
	return new CMTLImporter;
}

CString CMTLFormat::GetFileExtension() const
{
	return "mtl";
}

CString CMTLFormat::GetName() const
{
	return "Wavefront Material Template Library (MTL)";
}

float32 CMTLFormat::MatchesFormat(byte *pBuffer, uint32 bufferSize) const
{
	return 0;
}