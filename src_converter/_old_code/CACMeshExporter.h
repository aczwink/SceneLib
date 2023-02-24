//Local
#include "IExporter.h"

class CACMeshExporter : public IExporter
{
	class CPackedVertex
	{
	public:
		Math::CVector3 position;
		Math::CVector2 uv;
		Math::CVector3 normal;

		bool operator<(const CPackedVertex &refOther) const
		{
			return MemCmp(this, &refOther, sizeof(CPackedVertex)) < 0;
		}

		bool operator>(const CPackedVertex &refOther) const
		{
			return MemCmp(&refOther, this, sizeof(CPackedVertex)) < 0;
		}
	};
private:
	//Members
	CArray<uint32> indices;
	CArray<CPackedVertex> packedVertices;

	//Methods
	void DoVBOIndexing(const CArray<CPackedVertex> &refVertices);
	void ExportMesh(const CMesh &refMesh, ASeekableOutputStream &refOutput);
	bool FindSimilarVertex(const CPackedVertex &refSearch, const CMap<CPackedVertex, uint32> &refVerticesToIndexMap, uint32 &refIndex);
	void PrepareData(const CMesh &refMesh);

public:
	//Methods
	void ExportScene(const CScene &refScene, const CPath &refDirectory);
};