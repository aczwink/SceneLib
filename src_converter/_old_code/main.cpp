#include <ACStdLib.h>
using namespace ACStdLib;
//Local
#include "CConverter.h"

//Global Variables
CPath g_inputPath;
CPath g_outputPath;
CString g_outputFormat;

//Function prototypes
bool EvaluateArguments(const CLinkedList<CString> &refArgs);
void PrintManual();

int32 Main(const CString &refProgramName, const CLinkedList<CString> &refArgs)
{
	if(EvaluateArguments(refArgs))
	{
		CConverter converter(g_inputPath, g_outputPath, g_outputFormat);
		
		converter.Convert();

		stdOut << "Done." << endl;
		
		return EXIT_SUCCESS;
	}

	PrintManual();
	return EXIT_FAILURE;
}

bool CheckArguments()
{
	if(!g_inputPath.Exists() || g_inputPath.IsDirectory())
	{
		stdErr << "File \"" << g_inputPath << "\" does not exist or is not a file." << endl;
		return false;
	}
	if((g_outputPath.Exists() && !g_outputPath.IsDirectory()))
	{
		stdErr << "\"" << g_outputPath << "\" is a file but should be a directory." << endl;
		return false;
	}

	return true;
}

bool EvaluateArguments(const CLinkedList<CString> &refArgs)
{
	if(refArgs.GetNumberOfElements() != 3)
		return false;
	g_inputPath = refArgs[0];
	g_outputPath = refArgs[1];
	g_outputFormat = refArgs[2];
	
	return CheckArguments();
}

void PrintManual()
{
	stdOut << "SceneConverter by Amir Czwink" << endl << endl
		<< "Usage: " << endl
		<< "  SceneConverter input output outformat" << endl << endl
		<< "   input      path to a import file/dir" << endl
		<< "   output     path to a output dir" << endl
		<< "   outformat  format for output. Can be 'AC' or 'OBJ'" << endl;
}