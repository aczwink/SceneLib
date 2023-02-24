//Local
#include "IExporter.h"

class CACMaterialExporter : public IExporter
{
private:
	//Methods
	void ExportMaterial(const CMaterial &refMaterial, ASeekableOutputStream &refOutput);

public:
	//Methods
	void ExportScene(const CScene &refScene, const CPath &refDirectory);
};