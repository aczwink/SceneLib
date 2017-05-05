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
//Class header
#include "Scene.hpp"
//Local
#include "SceneFormat.hpp"
//Namespaces
using namespace ACStdLib;
using namespace SceneLib;

//Prototypes
const CLinkedList<const SceneFormat *> &GetFormats();

//Local functions
static const SceneFormat *FindFormat(ASeekableInputStream &refInput)
{
	byte buffer[4];

	const CLinkedList<const SceneFormat *> &refFormats = GetFormats();

	refInput.ReadBytes(buffer, sizeof(buffer));

	for(const SceneFormat *const &refpFormat : refFormats)
	{
		if(refpFormat->MatchesFormat(buffer, sizeof(buffer)) == 1)
		{
			refInput.SetCurrentOffset(0);
			return refpFormat;
		}
	}

	refInput.SetCurrentOffset(0);
	return nullptr;
}

static const SceneFormat *FindFormatByFileExtension(const CString &extension)
{
	const CLinkedList<const SceneFormat *> &refFormats = GetFormats();

	for(const SceneFormat *const &refpFormat : refFormats)
	{
		if(refpFormat->GetFileExtension() == extension.ToLowercase())
		{
			return refpFormat;
		}
	}

	return nullptr;
}

//Namespace functions
Scene *SceneLib::ImportScene(ASeekableInputStream &refInput)
{
	const SceneFormat *format;

	format = FindFormat(refInput);
	if(!format) //no format found
		return nullptr;

	NOT_IMPLEMENTED_ERROR;
}

Scene *SceneLib::ImportSceneFromFile(const CPath &path)
{
	Scene *scene;
	const SceneFormat *format;

	CFileInputStream file(path);

	scene = ImportScene(file);
	if(scene)
		return scene;

	//second try by file extension
	format = FindFormatByFileExtension(path.GetFileExtension());
	if(!format)
		return nullptr;

	NOT_IMPLEMENTED_ERROR;
}