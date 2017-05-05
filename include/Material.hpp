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
    class Material
    {
    private:
        //Members
        ACStdLib::CString name;
        ACStdLib::CString textureName;

    public:
        //Members
        ACStdLib::Math::CVector3 diffuseColor;

        //Constructor
        inline Material(const ACStdLib::CString &refName)
        {
            this->name = refName;
        }

        //Methods
        void SetTextureFromFileName(const ACStdLib::CString &refFileName);

        //Inline
        inline const ACStdLib::CString &GetName() const
        {
            return this->name;
        }

        inline const ACStdLib::CString &GetTexture() const
        {
            return this->textureName;
        }

        inline void SetTexture(const ACStdLib::CString &refTextureName)
        {
            this->textureName = refTextureName;
        }
    };
}