//Local
#include "ISceneFormat.h"

class CACTextureFormat : public ISceneFormat
{
public:
	//Methods
	IExporter *CreateExporter() const;
	IImporter *CreateImporter() const;
	CString GetFileExtension() const;
	CString GetName() const;
	float32 MatchesFormat(byte *pBuffer, uint32 bufferSize) const;
};