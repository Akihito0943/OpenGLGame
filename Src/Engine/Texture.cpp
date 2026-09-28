/**
 * @file Texture.cpp
 */


#include <fstream>
#include <filesystem>
#include <vector>
#include <Windows.h>

#include "Texture.h"


/// <summary>
/// コンストラクタ（テクスチャをロードする）
/// </summary>
/// <param name="filename">ファイル名</param>
Texture::Texture(const char* filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		// エラーメッセージを出力して終了
		char s[256];
		snprintf(s, 256, "[ERROR] %s: %sを開けません\n", __func__, filename);
		OutputDebugStringA(s);
		return;
	}

	// ファイルを読み込む
	const size_t fileSize = std::filesystem::file_size(filename);
	std::vector<uint8_t> buffer(fileSize);
	file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
	file.close();

	// ヘッダからの情報を取得
	const size_t tgaHeaderSize = 18; // ヘッダ情報のバイト数
	width = buffer[12] | buffer[13] << 8; // 8バイトを結合して2バイト幅を取得
	height = buffer[14] | buffer[15] << 8;

	// テクスチャの作成
	GLuint texture = 0;
	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	glTextureStorage2D(texture, 1, GL_RGBA8, width, height); // GPUメモリにテクスチャ用の領域を確保
	glTextureSubImage2D(texture, 0, 0, 0, width, height,
		GL_BGRA, GL_UNSIGNED_BYTE, buffer.data() + tgaHeaderSize);

	id = texture;
	name = filename;
}


/// <summary>
/// デストラクタ（テクスチャを削除する
/// </summary>
Texture::~Texture()
{
	glDeleteTextures(1, &id);
}
