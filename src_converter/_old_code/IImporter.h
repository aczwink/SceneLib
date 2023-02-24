#pragma once
#include <ACStdLib.h>
using namespace ACStdLib;
//Local
#include "CScene.h"

class IImporter
{
public:
	//Destructor
	virtual ~IImporter() {}

	//Abstract
	virtual CScene *ImportScene(ASeekableInputStream &refInput, const CString &refName) = NULL;
};