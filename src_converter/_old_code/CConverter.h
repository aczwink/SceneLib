#pragma once
#include <ACStdLib.h>
using namespace ACStdLib;
//Local
#include "ISceneFormat.h"

class CConverter
{
private:
	//Members
	CPath inputPath;
	CPath outputPath;
	CString outputFormat;
	CScene *pScene;
	
	//Methods
	const IFormat *CheckAVFormat(ASeekableInputStream &refInput, const CString &refFileExtension);
	const ISceneFormat *CheckSceneFormat(ASeekableInputStream &refInput, const CString &refFileExtension);
	bool ImportAV(ASeekableInputStream &refInput, const IFormat *pFormat, const CString &refTitle);
	void ImportFile(const CPath &refPath);
	bool ImportScene(ASeekableInputStream &refInput, const ISceneFormat *pFormat, const CString &refTitle);
	void OutputAC();
	void OutputAC(const CString &refFileExtension, const CString &refDirName);

public:
	//Constructor
	CConverter(const CPath &refInputPath, const CPath &refOutputPath, const CString &refOutputFormat);

	//Destructor
	~CConverter();

	//Methods
	void Convert();
};