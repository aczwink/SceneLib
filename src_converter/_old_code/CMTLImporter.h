//Local
#include "IImporter.h"

class CMTLImporter : public IImporter
{
private:
	//Members
	byte lookahead;

	//Methods
	CString ReadNextToken(AInputStream &refInput);
	void SkipToNextLine(AInputStream &refInput);
	void SkipToNextToken(AInputStream &refInput);

	//Inline
	inline float32 ReadFloat(AInputStream &refInput)
	{
		return (float32)StringToFloat64(this->ReadNextToken(refInput));
	}

	inline uint32 ReadUInt(AInputStream &refInput)
	{
		return (uint32)StringToUInt64(this->ReadNextToken(refInput));
	}

public:
	//Methods
	CScene *ImportScene(ASeekableInputStream &refInput, const CString &refName);
};