/**
 * @file Texture.h
 */


#pragma once


#include "glad/glad.h"
#include <string>
#include <memory>


// 先行宣言
class Texture;
using TexturePtr = std::shared_ptr<Texture>;


/**
* テクスチャ管理クラス
*/
class Texture
{
public:
	explicit Texture(const char* filename);
	~Texture();
	Texture(const Texture&) = delete; // コピー禁止
	Texture& operator=(const Texture&) = delete; // 代入禁止

public:
	/// <summary>
	/// 管理番号を取得する
	/// </summary>
	operator GLuint() const { return id; }


	/// <summary>
	/// テクスチャ幅を取得する
	/// </summary>
	/// <returns></returns>
	int GetWidth() const { return width; }


	/// <summary>
	/// テクスチャ高さを取得する
	/// </summary>
	/// <returns></returns>
	int GetHeight() const { return height; }

private:
	// テクスチャ名
	std::string name = "";

	// オブジェクト管理番号
	GLuint id = 0;

	// テクスチャ幅
	int width = 0;

	// テクスチャ高さ
	int height = 0;
};