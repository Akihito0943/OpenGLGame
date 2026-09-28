/**
 * @file Engine.h
 */


#pragma once


#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>

#include "GameObject.h"
#include "Render.h"
#include "../Scene/Scene.h"


 /**
 * ゲームエンジン
 */
class Engine
{
public:
	Engine() = default;
	~Engine() = default;

public:
	/// <summary>
	/// プログラム実行関数
	/// </summary>
	/// <returns>正常終了：0</returns>
	int Run();

public:
	/// <summary>
	/// ゲームオブジェクトを作成する
	/// </summary>
	/// <typeparam name="T">GameObject及びその派生クラス</typeparam>
	/// <param name="name">オブジェクト名</param>
	/// <param name="position">オブジェクト配置座標</param>
	/// <param name="rotation">オブジェクト回転角度</param>
	/// <returns>作成したオブジェクト</returns>
	template<typename T>
	std::shared_ptr<T> CreateGameObject(const std::string& name,
		const vec3& position = { 0.0f, 0.0f, 0.0f },
		const vec3& rotation = { 0.0f, 0.0f, 0.0f })
	{
		std::shared_ptr<T> p = std::make_shared<T>();
		p->engine = this;
		p->name = name;
		p->position = position;
		p->rotation = rotation;
		gameObjectList.push_back(p);
		return p;
	}


	/// <summary>
	/// 全てのゲームオブジェクトを削除する
	/// </summary>
	void ClearGameObjectAll();


	/// <summary>
	/// ゲームオブジェクトリストを取得する
	/// </summary>
	/// <returns></returns>
	const GameObjectList& GetGameObjectList() const { return gameObjectList; }


	/// <summary>
	/// メインカメラを取得する
	/// </summary>
	/// <returns>メインカメラ</returns>
	GameObject& GetMainCamera() { return camera; } // 変更可
	const GameObject& GetMainCamera() const { return camera; } // 変更不可


	/// <summary>
	/// Windowオブジェクトを取得する
	/// </summary>
	/// <returns>Windowオブジェクト</returns>
	GLFWwindow* GetWindow() { return window; }


	/// <summary>
	/// キーが押されているかを取得する
	/// </summary>
	/// <param name="key">押しているキー</param>
	/// <returns>押しているかどうか</returns>
	bool GetKey(int key) const { return glfwGetKey(window, key) == GLFW_PRESS; }


	/// <summary>
	/// 次のシーンを設定する
	/// </summary>
	/// <typeparam name="T">シーンの派生クラス</typeparam>
	template<typename T>
	void SetNextScene() { nextScene = std::make_shared<T>(); }

private:
	/// <summary>
	/// プログラムの初期化
	/// </summary>
	/// <returns>正常終了：0</returns>
	int Initialize();


	/// <summary>
	/// プログラムの毎フレーム更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// ゲームオブジェクトを毎フレーム更新する
	/// </summary>
	/// <param name="deltaTime">前フレームからの経過時間</param>
	void UpdateGameObject(float deltaTime);


	/// <summary>
	/// 廃棄予定のオブジェクトを削除する
	/// </summary>
	void RemoveDestroyedGameObject();

private:
	// ウィンドウオブジェクト
	GLFWwindow* window = nullptr;

	// ウィンドウタイトル
	const std::string title = "OpenGLGame";

	// カメラオブジェクト
	GameObject camera;

	// レンダーオブジェクト
	Render render;

	// ゲームオブジェクト配列
	GameObjectList gameObjectList = {};

	// 前回更新時の時刻
	double previousTime = 0;

	// 前回更新時からの経過時間
	float deltaTime = 0;

	// 実行中のシーン
	ScenePtr scene = nullptr;

	// 次に実行されるシーン
	ScenePtr nextScene = nullptr;
};