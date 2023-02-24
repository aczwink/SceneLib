//Class header
#include "CScene.h"

//Destructor
CScene::~CScene()
{
	for(CMaterial *const& refpMaterial : this->materials)
	{
		delete refpMaterial;
	}

	for(CMesh *const& refpMesh : this->meshes)
	{
		delete refpMesh;
	}

	for(CTexture *const& refpTexture : this->textures)
	{
		delete refpTexture;
	}
}

//Public methods
void CScene::MoveAdd(CScene &refSource)
{
	for(CMaterial *const& refpMaterial : refSource.materials)
	{
		this->AddMaterial(refpMaterial);
	}

	for(CMesh *const& refpMesh : refSource.meshes)
	{
		this->AddMesh(refpMesh);
	}

	for(CTexture *const& refpTexture : refSource.textures)
	{
		this->AddTexture(refpTexture);
	}
	
	refSource.materials.Clear();
	refSource.meshes.Clear();
	refSource.textures.Clear();
}