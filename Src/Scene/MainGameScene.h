/**
 * @file MainGameScene.h
 */


#pragma once


#include "Scene.h"


// 先行宣言
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;


/**
* メインゲームシーン
*/
class MainGameScene : public Scene
{
public:
	MainGameScene() = default;
	virtual~MainGameScene() = default;

public:
	/// <summary>
	/// シーンを初期化する
	/// </summary>
	/// <param name="engine">ゲームエンジンの参照</param>
	/// <returns>初期化成功フラグ</returns>
	virtual bool Initialize(Engine& engine) override;

private:
	// プレイヤー
	GameObjectPtr player = nullptr;

};