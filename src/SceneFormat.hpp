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
using namespace ACStdLib;
//Local
#include "Exporter.hpp"
#include "Importer.hpp"

class SceneFormat
{
public:
	virtual IExporter *CreateExporter() const = NULL;
	virtual Importer *CreateImporter() const = NULL;
	virtual CString GetFileExtension() const = NULL;
	virtual CString GetName() const = NULL;
	virtual float32 MatchesFormat(byte *pBuffer, uint32 bufferSize) const = NULL;
};