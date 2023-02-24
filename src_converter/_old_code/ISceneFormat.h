#pragma once
#include <ACStdLib.h>
using namespace ACStdLib;
//Local
#include "IExporter.h"
#include "IImporter.h"

class ISceneFormat
{
public:
	virtual IExporter *CreateExporter() const = NULL;
	virtual IImporter *CreateImporter() const = NULL;
	virtual CString GetFileExtension() const = NULL;
	virtual CString GetName() const = NULL;
	virtual float32 MatchesFormat(byte *pBuffer, uint32 bufferSize) const = NULL;
};