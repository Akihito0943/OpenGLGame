/**
 * @file Engine.cpp
 */


#include <algorithm>

#include "Engine.h"
#include "Debug.h"
#include "Render.h"
#include "Texture.h"
#include "../Scene/MainGameScene.h"


 /// <summary>
 /// ゲームエンジンを実行する
 /// </summary>
 /// <returns>正常終了したかどうか</returns>
int Engine::Run()
{
	const int result = Initialize();

	if (result) {
		return result;
	}
	while (!glfwWindowShouldClose(window)) {
		Update();
		render.Rendering();
		RemoveDestroyedGameObject();
	}

	// GLFWの終了処理
	glfwTerminate();

	return 0; // 正常終了
}


/// <summary>
/// 全てのゲームオブジェクトを削除する
/// </summary>
void Engine::ClearGameObjectAll()
{
	for (GameObjectPtr& p : gameObjectList) {
		p->OnDestroy();
	}
	gameObjectList.clear();
}


/// <summary>
/// ゲームエンジンを初期化する
/// </summary>
/// <returns>0：正常終了</returns>
int Engine::Initialize()
{
	// GLFWの初期化
	if (glfwInit() == GLFW_FALSE)
	{
		return -1; // 初期化に失敗した場合は-1を返す
	}

	// ウィンドウの作成
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	window = glfwCreateWindow(1280, 720, title.c_str(), nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1; // ウィンドウの作成に失敗した場合は-1を返す
	}

	// ウィンドウのコンテキストを現在のスレッドに関連付ける
	glfwMakeContextCurrent(window);

	// OpenGLの関数ポインタをロードする
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		glfwTerminate();
		return -1; // OpenGLの関数ポインタのロードに失敗した場合は-1を返す
	}

	// メッセージコールバック関数の登録
	glDebugMessageCallback(DebugCallback, nullptr);

	// レンダーオブジェクトの初期化
	render.Initialize(this);

	// 最初のシーンを作成する
	scene = std::make_shared<MainGameScene>();
	scene->Initialize(*this);

	// ゲームオブジェクト配列の容量を予約する
	gameObjectList.reserve(1000);

	return 0;
}


/// <summary>
/// ゲームエンジンの状態を更新する
/// </summary>
void Engine::Update()
{
	// デルタタイムを計算
	const double currentTime = glfwGetTime();
	deltaTime = static_cast<float>(currentTime - previousTime);
	previousTime = currentTime;

	// debugで一時停止する間もcurrentTimeは経過するので
	// 一定範囲を超えた場合は、1フレーム60FPS相当の経過時間に補正する
	if (deltaTime >= 0.5f) {
		deltaTime = 0.0166f; // = 1.0f / 60.0f
	}

	// シーンの切り替え処理
	if (nextScene) {
		if (scene) {
			scene->Finalize(*this);
		}
		nextScene->Initialize(*this);
		scene = std::move(nextScene);
	}

	// シーンの更新
	if (scene) {
		scene->Update(*this, deltaTime);
	}

	// ゲームオブジェクトの更新処理
	UpdateGameObject(deltaTime);
}


/// <summary>
/// ゲームオブジェクトを毎フレーム更新する
/// </summary>
/// <param name="deltaTime">前フレームからの経過時間</param>
void Engine::UpdateGameObject(float deltaTime)
{
	// 要素の途中追加に対応するため添え字for文を選択
	for (int i = 0; i < gameObjectList.size(); ++i) {
		const GameObjectPtr& p = gameObjectList[i];
		if (!p->IsDestroyed()) {
			p->Start();
			p->Update(deltaTime);
		}
	}
}


/// <summary>
/// 廃棄予定のオブジェクトを削除する
/// </summary>
void Engine::RemoveDestroyedGameObject()
{
	if (gameObjectList.empty()) return;

	// 廃棄予定の有無でリストを並び替える
	GameObjectList::iterator iter = std::stable_partition(
		gameObjectList.begin(), gameObjectList.end(),
		[](const GameObjectPtr& p) { return !p->IsDestroyed(); }
	);

	// 廃棄予定のオブジェクトを別のリストに移動
	GameObjectList destroyedGameObjectList(
		std::move_iterator(iter), std::move_iterator(gameObjectList.end())
	);

	// オリジナルリストから移動済みオブジェクトを削除
	gameObjectList.erase(iter, gameObjectList.end());

	// 廃棄予定のオブジェクトのOnDestroyを実行
	for (GameObjectPtr& p : destroyedGameObjectList) {
		p->OnDestroy();
	}
}
