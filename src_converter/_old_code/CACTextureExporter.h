//Local
#include "IExporter.h"

class CACTextureExporter : public IExporter
{
private:
	//Methods
	void ExportTexture(const CTexture &refTexture, AOutputStream &refOutput);

public:
	//Methods
	void ExportScene(const CScene &refScene, const CPath &refDirectory);
};