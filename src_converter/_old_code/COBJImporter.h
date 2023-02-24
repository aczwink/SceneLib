//Local
#include "IImporter.h"

class COBJImporter : public IImporter
{
private:
	//Members
	byte lookahead;
	uint32 indexBasePos;
	uint32 indexBaseNormal;
	uint32 indexBaseUV;
	uint32 currentMaterialIndex;

	//Methods
	void ReadFaceValue(SVertexTable &refVT, AInputStream &refInput);
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