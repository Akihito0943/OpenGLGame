/**
 * @file Render.cpp
 */


#include <fstream>
#include <filesystem>
#include <Windows.h>

#include "Render.h"
#include "Engine.h"
#include "Mesh.h"

#include "../../Res/Mesh/square_mesh.h"
#include "../../Res/Mesh/crystal_mesh.h"


 /// <summary>
 /// シェーダーをコンパイルする
 /// </summary>
 /// <param name="shaderType">シェーダーのタイプ</param>
 /// <param name="filename">シェーダーのファイル名</param>
 /// <returns></returns>
GLuint Render::CompileShader(GLenum shaderType, const char* filename)
{
	// ファイルを開く
	std::ifstream file(filename, std::ios::binary);

	if (!file) {
		// エラーメッセージを出力して終了
		char s[256];
		snprintf(s, 256, "[ERROR] %s: %sを開けません\n", __func__, filename);
		OutputDebugStringA(s);
		return 0;
	}

	// ファイルの内容を読み込む
	const size_t fileSize = std::filesystem::file_size(filename);
	std::vector<char>buffer(fileSize);
	file.read(buffer.data(), fileSize); // data()はvectorの先頭アドレスを返す
	file.close();

	// ソースコードを設定してコンパイル
	const char* source[] = { buffer.data() };
	const GLint length[] = { int(buffer.size()) };
	const GLuint object = glCreateShader(shaderType);
	glShaderSource(object, 1, source, length);
	glCompileShader(object);

	return object;
}


/// <summary>
/// 初期化処理
/// </summary>
/// <returns>正常終了：0</returns>
int Render::Initialize(Engine* engine)
{
	this->engine = engine;

	// シェーダーのコンパイル
	vertexShader = CompileShader(GL_VERTEX_SHADER, "Res/standard_2D.vert");
	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, "Res/standard.frag");

	// 2つのシェーダーをリンク
	program3D = glCreateProgram();
	glAttachShader(program3D, vertexShader);
	glAttachShader(program3D, fragmentShader);
	glLinkProgram(program3D);

	// 図形データ情報
	const MeshData meshes[] = {
		{ sizeof(square_vertices), sizeof(square_indices), square_vertices, square_indices },
		{ sizeof(crystal_vertices), sizeof(crystal_indices), crystal_vertices, crystal_indices },
	};

	// メッシュの数だけバッファを作成
	size_t totalVertexByteSize = 0;
	size_t  totalIndexByteSize = 0;
	for (const MeshData& mesh : meshes) {
		totalVertexByteSize += mesh.vertexByteSize;
		totalIndexByteSize += mesh.indexByteSize;
	}

	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, totalVertexByteSize, nullptr, 0);

	glCreateBuffers(1, &ibo);
	glNamedBufferStorage(ibo, totalIndexByteSize, nullptr, 0);

	drawParamsList.reserve(std::size(meshes));
	// コピーするデータのバッファのサイズ
	GLintptr vboSize = 0;
	GLintptr iboSize = 0;
	for (const MeshData& mesh : meshes) {
		// GPUメモリにデータをコピー
		GLuint tmp[2];
		glCreateBuffers(2, tmp);
		glNamedBufferStorage(tmp[0], mesh.vertexByteSize, mesh.vertexData, 0);
		glNamedBufferStorage(tmp[1], mesh.indexByteSize, mesh.indexData, 0);
		glCopyNamedBufferSubData(tmp[0], vbo, 0, vboSize, mesh.vertexByteSize);
		glCopyNamedBufferSubData(tmp[1], ibo, 0, iboSize, mesh.indexByteSize);
		glDeleteBuffers(2, tmp);

		// 図形データから描画パラメータを作成
		DrawParams params;
		params.mode = GL_TRIANGLES;
		params.indexCount = static_cast<GLsizei>(mesh.indexByteSize / sizeof(uint16_t));
		params.indicesByteOffset = reinterpret_cast<void*>(iboSize);
		params.baseVertex = static_cast<GLint>(vboSize / sizeof(Vertex)); // 新しく追加した頂点データがVBO全体の何番目かを計算
		drawParamsList.push_back(params);

		// バッファのサイズを更新
		vboSize += mesh.vertexByteSize;
		iboSize += mesh.indexByteSize;
	}


	// 頂点属性配列オブジェクトの作成
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// IBOをVAOとOpenGLコンテキストの両方にバインド
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	// vboをOpenGLコンテキストにバインド
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// 0番目の頂点属性の有効化
	glEnableVertexAttribArray(0);

	// 0番目の頂点属性の設定
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// 1番目の頂点属性の有効化
	glEnableVertexAttribArray(1);

	// 1番目の頂点属性の設定
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		reinterpret_cast<void*>(offsetof(Vertex, texcoord)));

	return 0;
}


/// <summary>
/// 画面の描画処理
/// </summary>
void Render::Rendering()
{
	// バックバッファのクリア
	glClearColor(0.9f, 0.6f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 描画に使うシェーダープログラムの指定
	glUseProgram(program3D);

	// 図形を描画
	glBindVertexArray(vao);

	// フレームバッファの取得
	int fbWidth, fbHeight;
	glfwGetFramebufferSize(engine->GetWindow(), &fbWidth, &fbHeight);

	// ビューポートを設定
	glViewport(0, 0, fbWidth, fbHeight);

	// アスペクト比と視野角を設定
	const float aspectRatio = static_cast<float>(fbWidth) / static_cast<float>(fbHeight);
	const float degreeFogY = 60; // 垂直視野角
	const float radianFogY = degreeFogY * 3.1415926535f / 180;
	const float scaleFov = tanf(radianFogY / 2); // 視野角による拡大率		
	glProgramUniform2f(program3D, glGetUniformLocation(program3D, "aspectRatioAndScaleFov"), 1 / (scaleFov * aspectRatio), 1 / scaleFov);

	// カメラのパラメータを設定
	glProgramUniform3fv(program3D, glGetUniformLocation(program3D, "cameraPosition"), 1, &engine->GetMainCamera().position.x);
	glProgramUniform2f(program3D, glGetUniformLocation(program3D, "cameraRotationY"), sinf(-engine->GetMainCamera().rotation.y), cosf(-engine->GetMainCamera().rotation.y));

	// 深度テストを有効か
	glEnable(GL_DEPTH_TEST);

	// ゲームオブジェクトを描画
	for (const GameObjectPtr& p : engine->GetGameObjectList()) {
		// 図形番号がリストにない場合は描画しない
		if (p->meshId < 0 || p->meshId >= drawParamsList.size()) continue;

		// 描画に使うテクスチャの指定
		if (p->texColor) {
			const GLuint tex = *p->texColor;
			glBindTextures(0, 1, &tex);
		}

		// ユニフォーム変数にデータをコピー
		glProgramUniform4fv(program3D, glGetUniformLocation(program3D, "color"), 1, p->color);
		glProgramUniform3fv(program3D, glGetUniformLocation(program3D, "scale"), 1, &p->scale.x);
		glProgramUniform3fv(program3D, glGetUniformLocation(program3D, "position"), 1, &p->position.x);
		glProgramUniform2f(program3D, glGetUniformLocation(program3D, "rotationY"), sinf(p->rotation.y), cosf(p->rotation.y));

		// 図形を描画
		const DrawParams& params = drawParamsList[p->meshId];
		glDrawElementsInstancedBaseVertex(params.mode, params.indexCount, GL_UNSIGNED_SHORT,
			params.indicesByteOffset, 1, params.baseVertex);
	}

	glBindVertexArray(0); // VAOのバインドを解除

	glfwSwapBuffers(engine->GetWindow());
	glfwPollEvents();
}
