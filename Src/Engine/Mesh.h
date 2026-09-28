/**
 * @file Mesh.h
 */


#pragma once


#include "glad/glad.h"

#include "Math.h"


/**
* 描画パラメータ
*/
struct DrawParams
{
	// プリミティブの種類
	GLenum mode = GL_TRIANGLES;

	// 描画するインデックス数
	GLsizei indexCount = 0;

	// 描画開始インデックスのバイトオフセット
	const void* indicesByteOffset = 0;

	// インデックス0となる頂点配列内の位置
	GLint baseVertex = 0;
};


/**
* 頂点データ
*/
struct Vertex
{
	// 頂点座標
	vec3 position;

	// テクスチャ座標
	vec2 texcoord;
};


/**
* 図形のデータ情報
*/
struct MeshData {
	// 頂点データのバイト数
	size_t vertexByteSize;

	// インデックスデータのバイト数	
	size_t indexByteSize;

	// 頂点データのアドレス
	const void* vertexData;

	// インデックスデータのアドレス
	const void* indexData;
};