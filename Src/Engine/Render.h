/**
 * @file Render.h
 */


#pragma once


#include "glad/glad.h"
#include <vector>

#include "Mesh.h"


 // 先行宣言
class Engine;


 /**
 * 描画管理クラス
 */
class Render
{
public:
	Render() = default;
	~Render() = default;

public:
	/// <summary>
	/// シェーダーをコンパイルする
	/// </summary>
	/// <param name="shaderType">シェーダーのタイプ</param>
	/// <param name="filename">シェーダーのファイル名</param>
	/// <returns></returns>
	GLuint CompileShader(GLenum shaderType, const char* filename);


	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <returns>正常終了：0</returns>
	int Initialize(Engine* engine);


	/// <summary>
	/// 画面の描画処理
	/// </summary>
	void Rendering();

private:
	// エンジンのアドレス
	Engine* engine = nullptr;

	// 頂点シェーダの管理番号
	GLuint vertexShader = 0;

	// フラグメントシェーダの管理番号
	GLuint fragmentShader = 0;

	// シェーダプログラムの管理番号
	GLuint program3D = 0;

	// 頂点バッファオブジェクト管理番号
	GLuint vbo = 0;

	// インデックスバッファオブジェクト管理番号
	GLuint ibo = 0;

	// 頂点配列オブジェクト管理番号
	GLuint vao = 0;

	// 描画パラメータ配列
	std::vector<DrawParams> drawParamsList;

	// 頂点配列のインデックス数
	GLsizei indexCount = 0;

};
