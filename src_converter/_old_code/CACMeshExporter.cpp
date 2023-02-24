//Class Header
#include "CACMeshExporter.h"

//Local fucntions
static void WriteVec3(const CVector3 &refV, AOutputStream &refOutput)
{
	refOutput.WriteFloat32LE(refV.x);
	refOutput.WriteFloat32LE(refV.y);
	refOutput.WriteFloat32LE(refV.z);
}

//Private methods
void CACMeshExporter::DoVBOIndexing(const CArray<CPackedVertex> &refVertices)
{
	uint32 index;
	CMap<CPackedVertex, uint32> verticesToIndexMap;

	for(uint32 i = 0; i < refVertices.GetNumberOfElements(); i++)
	{
		if(this->FindSimilarVertex(refVertices[i], verticesToIndexMap, index))
		{
			this->indices.Push(index);
		}
		else
		{
			index = this->packedVertices.Push(refVertices[i]);
			this->indices.Push(index);

			verticesToIndexMap[refVertices[i]] = index;
		}
	}
}

void CACMeshExporter::ExportMesh(const CMesh &refMesh, ASeekableOutputStream &refOutput)
{
	AxisAlignedBox bbox;
	
	this->indices.Release();
	this->packedVertices.Release();

	this->PrepareData(refMesh);

	//write file header
	refOutput.WriteBytes("ACFF", 4);
	refOutput.WriteUInt16LE(1); //file type... should be "3D model"

	//packed vertices
	refOutput.WriteUInt32LE(this->packedVertices.GetNumberOfElements());
	for(const CPackedVertex &refPV : this->packedVertices)
	{
		bbox.Merge(refPV.position);
		
		//position
		refOutput.WriteFloat32LE(refPV.position.x);
		refOutput.WriteFloat32LE(refPV.position.y);
		refOutput.WriteFloat32LE(refPV.position.z);

		//normal
		refOutput.WriteFloat32LE(refPV.normal.x);
		refOutput.WriteFloat32LE(refPV.normal.y);
		refOutput.WriteFloat32LE(refPV.normal.z);

		//uv
		refOutput.WriteFloat32LE(refPV.uv.x);
		refOutput.WriteFloat32LE(refPV.uv.y);
	}

	//indices
	refOutput.WriteUInt32LE(this->indices.GetNumberOfElements());
	if(this->packedVertices.GetNumberOfElements() > UINT16_MAX)
	{
		for(const uint32 &refIdx : this->indices)
		{
			refOutput.WriteUInt32LE(refIdx);
		}
	}
	else
	{
		for(const uint32 &refIdx : this->indices)
		{
			refOutput.WriteUInt16LE((uint16)refIdx);
		}
	}

	//materials
	ASSERT(refMesh.GetNumberOfMaterials() == 1);
	refOutput << refMesh.GetMaterials()[0] << endl;

	//mesh info
	WriteVec3(bbox.min, refOutput);
	WriteVec3(bbox.max, refOutput);
}

bool CACMeshExporter::FindSimilarVertex(const CPackedVertex &refSearch, const CMap<CPackedVertex, uint32> &refVerticesToIndexMap, uint32 &refIndex)
{
	auto it = refVerticesToIndexMap.Find(refSearch);

	if(it != refVerticesToIndexMap.end())
	{
		refIndex = (*it).value;
		return true;
	}

	return false;
}

void CACMeshExporter::PrepareData(const CMesh &refMesh)
{
	CPackedVertex current;
	CArray<CPackedVertex> packedVertices;

	for(const SFace &refFace : refMesh.GetFaces())
	{
		current.position = refMesh.GetPosition(refFace.vertexTable[0].positionIndex);
		current.uv = refMesh.GetUV(refFace.vertexTable[0].uvIndex);
		current.normal = refMesh.GetNormal(refFace.vertexTable[0].normalsIndex);
		packedVertices.Push(current);

		current.position = refMesh.GetPosition(refFace.vertexTable[1].positionIndex);
		current.uv = refMesh.GetUV(refFace.vertexTable[1].uvIndex);
		current.normal = refMesh.GetNormal(refFace.vertexTable[1].normalsIndex);
		packedVertices.Push(current);

		current.position = refMesh.GetPosition(refFace.vertexTable[2].positionIndex);
		current.uv = refMesh.GetUV(refFace.vertexTable[2].uvIndex);
		current.normal = refMesh.GetNormal(refFace.vertexTable[2].normalsIndex);
		packedVertices.Push(current);

		if(refFace.faceType == 4)
		{
			current.position = refMesh.GetPosition(refFace.vertexTable[0].positionIndex);
			current.uv = refMesh.GetUV(refFace.vertexTable[0].uvIndex);
			current.normal = refMesh.GetNormal(refFace.vertexTable[0].normalsIndex);
			packedVertices.Push(current);

			current.position = refMesh.GetPosition(refFace.vertexTable[2].positionIndex);
			current.uv = refMesh.GetUV(refFace.vertexTable[2].uvIndex);
			current.normal = refMesh.GetNormal(refFace.vertexTable[2].normalsIndex);
			packedVertices.Push(current);

			current.position = refMesh.GetPosition(refFace.vertexTable[3].positionIndex);
			current.uv = refMesh.GetUV(refFace.vertexTable[3].uvIndex);
			current.normal = refMesh.GetNormal(refFace.vertexTable[3].normalsIndex);
			packedVertices.Push(current);
		}
	}

	this->DoVBOIndexing(packedVertices);
}

//Public methods
void CACMeshExporter::ExportScene(const CScene &refScene, const CPath &refDirectory)
{
	for(CMesh *const& refpMesh : refScene.GetMeshes())
	{
		CFileOutputStream output(refDirectory / (refpMesh->GetName() + ".acmsh"));

		this->ExportMesh(*refpMesh, output);
	}
}