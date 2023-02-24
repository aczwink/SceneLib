//Class header
#include "CTexture.h"

//Constructor
CTexture::CTexture(const CString &refName, AImage *pImage)
{
	this->name = refName;
	this->pImage = pImage;
	
	ASSERT(pImage->GetColorSpace() == EColorSpace::RGB || pImage->GetColorSpace() == EColorSpace::RGBA);

	/*
	//resize
	if(!IS_POWER_OF_TWO(refImage.GetWidth()) || !IS_POWER_OF_TWO(refImage.GetHeight()))
	{
	uint16 newWidth, newHeight;

	newWidth = GetNextNumberOfTwo(refImage.GetWidth());
	newHeight = GetNextNumberOfTwo(refImage.GetHeight());

	*pImage = pImage->Resample(newWidth, newHeight);
	}
	else
	{
	pImage = &refImage;
	}
	*/
}

//Destructor
CTexture::~CTexture()
{
	delete this->pImage;
}