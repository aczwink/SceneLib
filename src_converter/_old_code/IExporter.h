#pragma once
//Local
#include "CScene.h"

class IExporter
{
public:
	//Destructor
	virtual ~IExporter() {}

	//Abstract
	virtual void ExportScene(const CScene &refScene, const CPath &refDirectory) = NULL;
};