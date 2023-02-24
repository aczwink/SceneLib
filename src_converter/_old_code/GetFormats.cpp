#include<ACStdLib.h>
using namespace ACStdLib;
//Local
#include "ISceneFormat.h"
//Formats
#include "CACMeshFormat.h"
#include "CACMaterialFormat.h"
#include "CACTextureFormat.h"
#include "CMTLFormat.h"
#include "COBJFormat.h"
/*
#include "CFreelancerUTF_Format.h"
#include "COFFFormat.h"
*/

class CFormatCollection
{
public:
	//Members
	CLinkedList<const ISceneFormat *> formats;

	//Constructor
	inline CFormatCollection()
	{
		formats.InsertTail(new CACMeshFormat);
		formats.InsertTail(new CACMaterialFormat);
		formats.InsertTail(new CACTextureFormat);
		formats.InsertTail(new CMTLFormat);
		formats.InsertTail(new COBJFormat);

		/*
		formats.InsertTail(new CFreelancerUTF_Format);
		formats.InsertTail(new COFFFormat);
		*/
	}

	//Destructor
	inline ~CFormatCollection()
	{
		for(const ISceneFormat *const &refpFormat : formats)
		{
			delete refpFormat;
		}
	}
};

const CLinkedList<const ISceneFormat *> &GetFormats()
{
	static CFormatCollection collection;

	return collection.formats;
}

const ISceneFormat *GetFormatFromFileExtension(const CString &refFileExtension)
{
	const CLinkedList<const ISceneFormat *> &refFormats = GetFormats();
	for(const ISceneFormat *const &refpFormat : refFormats)
	{
		if(refpFormat->GetFileExtension() == refFileExtension)
			return refpFormat;
	}

	return NULL;
}