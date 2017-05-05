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
//Local
#include "Material.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

namespace SceneLib
{
    class Scene
    {
    private:
        //Members
        ACStdLib::CArray<Material *> materials;
        ACStdLib::CArray<Mesh *> meshes;
        ACStdLib::CArray<Texture *> textures;

    public:
        //Destructor
        ~Scene();

        //Methods
        void MoveAdd(Scene &refSource);

        //Inline
        inline void AddMaterial(Material *pMaterial)
        {
            this->materials.Push(pMaterial);
        }

        inline void AddMesh(Mesh *pMesh)
        {
            this->meshes.Push(pMesh);
        }

        inline void AddTexture(Texture *pTexture)
        {
            this->textures.Push(pTexture);
        }

        inline ACStdLib::CArray<Material *> &GetMaterials()
        {
            return this->materials;
        }

        inline const ACStdLib::CArray<Material *> &GetMaterials() const
        {
            return this->materials;
        }

        inline const ACStdLib::CArray<Mesh *> &GetMeshes() const
        {
            return this->meshes;
        }

        inline const ACStdLib::CArray<Texture *> &GetTextures() const
        {
            return this->textures;
        }
    };

    //Functions
    Scene *ImportScene(ACStdLib::ASeekableInputStream &refInput);
    Scene *ImportSceneFromFile(const ACStdLib::CPath &path);
}