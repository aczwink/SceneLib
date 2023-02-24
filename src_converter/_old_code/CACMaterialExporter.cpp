//Class header
#include "CACMaterialExporter.h"
//Local
#include "ACFF.h"

//Private methods
void CACMaterialExporter::ExportMaterial(const CMaterial &refMaterial, ASeekableOutputStream &refOutput)
{
	CTextWriter writer(refOutput);
	
	//write file header
	refOutput.WriteUInt32BE(ACFF_SIGNATURE);
	refOutput.WriteUInt16LE(ACFF_TYPE_MATERIAL);

	//write material header
	refOutput.WriteByte(false); //use blending

	//write body
	refOutput.WriteFloat32LE(refMaterial.diffuseColor.x);
	refOutput.WriteFloat32LE(refMaterial.diffuseColor.y);
	refOutput.WriteFloat32LE(refMaterial.diffuseColor.z);
	writer.WriteUTF8_ZeroTerminated(refMaterial.GetTexture().GetUTF16());
}

//Public methods
void CACMaterialExporter::ExportScene(const CScene &refScene, const CPath &refDirectory)
{
	for(CMaterial *const& refpMaterial : refScene.GetMaterials())
	{
		CFileOutputStream output(refDirectory / (refpMaterial->GetName() + ".acmat"));

		this->ExportMaterial(*refpMaterial, output);
	}
}