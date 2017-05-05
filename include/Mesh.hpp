/*
 * Copyright (c) 2017 Amir Czwink (amir130@hotmail.de)
 *
 * This file is part of SceneLib.
 *
 * SceneLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SceneLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SceneLib.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <ACStdLib.hpp>

namespace SceneLib
{
	struct VertexTable
	{
		uint32 positionIndex;
		uint32 uvIndex;
		uint32 normalsIndex;
	};

	struct Face
	{
		uint32 materialIndex;
		ACStdLib::CArray<VertexTable> vertexIndices;
	};

	class Mesh
	{
	private:
		//Members
		ACStdLib::CString name;
		ACStdLib::CArray <ACStdLib::Math::CVector3> positions;
		ACStdLib::CArray <ACStdLib::Math::CVector3> normals;
		ACStdLib::CArray <ACStdLib::Math::CVector2> uvs;
		ACStdLib::CArray <Face> faces;
		ACStdLib::CLinkedList <ACStdLib::CString> materials;

	public:
		//Constructor
		inline Mesh(const ACStdLib::CString &refName)
		{
			this->name = refName;
		}

		//Inline
		inline uint32 AddFace(const Face &refFace)
		{
			return this->faces.Push(refFace);
		}

		inline uint32 AddMaterial(const ACStdLib::CString &refName)
		{
			this->materials.InsertTail(refName);

			return this->materials.GetNumberOfElements() - 1;
		}

		inline uint32 AddNormal(const ACStdLib::Math::CVector3 &refNormal)
		{
			return this->normals.Push(refNormal);
		}

		inline uint32 AddPosition(const ACStdLib::Math::CVector3 &refPosition)
		{
			return this->positions.Push(refPosition);
		}

		inline uint32 AddUV(const ACStdLib::Math::CVector2 &refUV)
		{
			return this->uvs.Push(refUV);
		}

		inline const ACStdLib::CArray <Face> &GetFaces() const
		{
			return this->faces;
		}

		inline const ACStdLib::CLinkedList <ACStdLib::CString> &GetMaterials() const
		{
			return this->materials;
		}

		inline const ACStdLib::CString &GetName() const
		{
			return this->name;
		}

		inline const ACStdLib::Math::CVector3 &GetNormal(uint32 index) const
		{
			return this->normals[index];
		}

		inline uint32 GetNumberOfMaterials() const
		{
			return this->materials.GetNumberOfElements();
		}

		inline uint32 GetNumberOfNormals() const
		{
			return this->normals.GetNumberOfElements();
		}

		inline uint32 GetNumberOfPositions() const
		{
			return this->positions.GetNumberOfElements();
		}

		inline uint32 GetNumberOfUVCoordinates() const
		{
			return this->uvs.GetNumberOfElements();
		}

		inline const ACStdLib::Math::CVector3 &GetPosition(uint32 index) const
		{
			return this->positions[index];
		}

		inline const ACStdLib::Math::CVector2 &GetUV(uint32 index) const
		{
			return this->uvs[index];
		}
	};
}