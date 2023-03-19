/*
//Class header
#include "CFreelancerUTF_Importer.h"
//Namespaces
using namespace ACStdLib::Math;

enum EUTF_Flags
{
	UTF_FLAG_NONLEAF = 0x10,
	UTF_FLAG_LEAF = 0x80,
};

struct SMesh
{
	uint16 firstVertex;
	uint16 lastVertex;
	uint16 nIndices;
};

struct SVertex
{
	CVector3 pos;
	CVector3 normal;
	CVector2 UV;
};

//Private methods
void CFreelancerUTF_Importer::ReadTreeNodes(uint32 nNodes, uint32 stringSegmentOffset, uint32 dataSegmentOffset, ASeekableInputStream &refInput)
{
	uint32 i, nameOffset, flags, offset, size;
	
	for(i = 0; i < nNodes; i++)
	{
		refInput.Skip(4); //unknown
		nameOffset = refInput.ReadUInt32LE();
		flags = refInput.ReadUInt32LE();
		refInput.Skip(4); //unknown
		offset = refInput.ReadUInt32LE(); //for leafs this is the offset in the data segment, for non-leafs this is the offset to the child
		refInput.Skip(4); //unknown
		size = refInput.ReadUInt32LE();
		refInput.Skip(4); //unknown

		refInput.Skip(12); //3 times time_t

		if(flags & UTF_FLAG_LEAF)
		{
			uint64 currentOffset;
			C8BitString name;
			
			CTextReader reader(refInput);
			
			//read name, NOTE: it is not only available for leafs but we don't need non leafs
			currentOffset = refInput.GetCurrentOffset();
			refInput.SetCurrentOffset(stringSegmentOffset + nameOffset);
			name = reader.ReadASCII_ZeroTerminated();
			
			if(name == "VMeshData")
			{
				refInput.SetCurrentOffset(dataSegmentOffset + offset);
				this->ReadVMeshData(refInput);
			}

			refInput.SetCurrentOffset(currentOffset);
		}
	}
}

void CFreelancerUTF_Importer::ReadVMeshData(AInputStream &refInput)
{
	uint16 nMeshes, i, nIndices, nVertices, j, indicesBase;
	uint32 i0, i1, i2;
	CMesh *pMesh;
	CArray<SMesh> meshes;
	CArray<uint16> indices;
	CArray<SVertex> vertices;

	//header
	ASSERT(refInput.ReadUInt32LE() == 1);
	ASSERT(refInput.ReadUInt32LE() == 4);
	nMeshes = refInput.ReadUInt16LE();
	nIndices = refInput.ReadUInt16LE();
	refInput.Skip(2); //unknown
	nVertices = refInput.ReadUInt16LE();

	meshes.Resize(nMeshes);
	indices.Resize(nIndices);
	vertices.Resize(nVertices);
	
	for(i = 0; i < nMeshes; i++)
	{
		refInput.Skip(4); //material id
		meshes[i].firstVertex = refInput.ReadUInt16LE();
		meshes[i].lastVertex = refInput.ReadUInt16LE();
		meshes[i].nIndices = refInput.ReadUInt16LE();
		refInput.Skip(2); //unknown
	}
	
	//read indices
	for(i = 0; i < nIndices; i++)
		indices[i] = refInput.ReadUInt16LE();
	
	//read vertices
	for(i = 0; i < nVertices; i++)
	{
		vertices[i].pos.x = refInput.ReadFloat32LE();
		vertices[i].pos.y = refInput.ReadFloat32LE();
		vertices[i].pos.z = refInput.ReadFloat32LE();

		vertices[i].normal.x = refInput.ReadFloat32LE();
		vertices[i].normal.y = refInput.ReadFloat32LE();
		vertices[i].normal.z = refInput.ReadFloat32LE();
		
		vertices[i].UV.x = refInput.ReadFloat32LE();
		vertices[i].UV.y = refInput.ReadFloat32LE();
	}

	//add meshes to scene
	indicesBase = 0;
	for(i = 0; i < nMeshes; i++)
	{
		static uint32 meshcounter = 0;
		
		pMesh = new CMesh(this->currentName + ToString((uint64)meshcounter++));
		this->pCurrentScene->AddMesh(pMesh);
		
		pMesh->AddMaterial("cube"); //TODO!!!
		
		//set vertices
		nVertices = meshes[i].lastVertex - meshes[i].firstVertex + 1;
		pMesh->SetNumberOfPositions(nVertices);
		pMesh->SetNumberOfNormals(nVertices);
		pMesh->SetNumberOfUVs(nVertices);

		for(j = 0; j < nVertices; j++)
		{
			const SVertex &refVertex = vertices[meshes[i].firstVertex + j];
			
			pMesh->SetPosition(j, refVertex.pos);
			pMesh->SetNormal(j, refVertex.normal);
			pMesh->SetUV(j, refVertex.UV);
		}
		
		//set faces
		pMesh->SetNumberOfFaces(meshes[i].nIndices / 3);
		
		for(j = 0; j < meshes[i].nIndices; j += 3)
		{
			i0 = indices[indicesBase + j]; // - meshes[i].firstVertex;
			i1 = indices[indicesBase + j + 1]; // -meshes[i].firstVertex;
			i2 = indices[indicesBase + j + 2]; // -meshes[i].firstVertex;
			pMesh->SetTriangle(j / 3, 0, i0, i1, i2);
		}
		
		indicesBase += meshes[i].nIndices;
	}
}

//Public methods
CScene *CFreelancerUTF_Importer::ImportScene(ASeekableInputStream &refInput, const CString &refName)
{
	uint32 version, treeSegmentOffset, treeSegmentSize, nodeHeaderSize, stringSegmentOffset, dataSegmentOffset;

	this->pCurrentScene = new CScene;

	//read file header
	refInput.Skip(4); //signature
	version = refInput.ReadUInt32LE();
	treeSegmentOffset = refInput.ReadUInt32LE();
	treeSegmentSize = refInput.ReadUInt32LE();
	refInput.Skip(4); //unknown
	nodeHeaderSize = refInput.ReadUInt32LE();
	stringSegmentOffset = refInput.ReadUInt32LE();
	refInput.Skip(4); //unknown
	refInput.Skip(4); //unknown
	dataSegmentOffset = refInput.ReadUInt32LE();
	refInput.Skip(4); //unknown
	refInput.Skip(12); //unknown

	ASSERT(version == 0x101);
	ASSERT(nodeHeaderSize == 44);
	ASSERT(treeSegmentOffset == refInput.GetCurrentOffset());
	
	this->ReadTreeNodes(treeSegmentSize / nodeHeaderSize, stringSegmentOffset, dataSegmentOffset, refInput);
	
	return this->pCurrentScene;
}
*/