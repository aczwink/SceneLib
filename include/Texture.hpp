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
	class Texture
	{
	private:
		//Members
		ACStdLib::CString name;
		ACStdLib::Multimedia::AImage *pImage;

	public:
		//Constructor
		Texture(const ACStdLib::CString &refName, ACStdLib::Multimedia::AImage *pImage);

		//Destructor
		~Texture();

		//Inline
		inline const ACStdLib::Multimedia::ARGBAImage &GetAlphaImage() const
		{
			return *(ACStdLib::Multimedia::ARGBAImage *)this->pImage;
		}

		inline const ACStdLib::Multimedia::AImage &GetImage() const
		{
			return *this->pImage;
		}

		inline const ACStdLib::CString &GetName() const
		{
			return this->name;
		}

		inline bool HasAlpha() const
		{
			return this->pImage->GetColorSpace() == ACStdLib::Multimedia::EColorSpace::RGBA;
		}

		inline const ACStdLib::Multimedia::ARGBImage &GetRGBImage() const
		{
			return *(ACStdLib::Multimedia::ARGBImage *)this->pImage;
		}
	};
}