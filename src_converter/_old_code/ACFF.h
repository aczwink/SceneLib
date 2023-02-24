#pragma once

#define ACFF_SIGNATURE (('A' << 24) | ('C' << 16) | ('F' << 8) | 'F')

enum EACFFType
{
	ACFF_TYPE_MATERIAL,
	ACFF_TYPE_MESH_RENDER_OPT,
	ACFF_TYPE_TEXTURE,
};