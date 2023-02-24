//Class header
#include "CMaterial.h"

//Private methods
void CMaterial::SetTextureFromFileName(const CString &refFileName)
{
	int32 index;

	index = refFileName.FindReverse('.');
	if(index != -1)
		this->textureName = refFileName.SubString(0, index);
	else
		this->textureName = refFileName;
}