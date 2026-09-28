/**
 * @file MainGameScene.cpp
 */


#include "MainGameScene.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObject.h"
#include "../Component/PlayerCamera.h"


/// <summary>
/// シーンを初期化する
/// </summary>
/// <param name="engine">ゲームエンジンの参照</param>
/// <returns>初期化成功フラグ</returns>
bool MainGameScene::Initialize(Engine& engine)
{
	player = engine.CreateGameObject<GameObject>("player");
	player->AddComponent<PlayerCamera>();
	player->meshId = -1;

	GameObjectPtr box1 = engine.CreateGameObject<GameObject>("box1");
	box1->texColor = std::make_shared<Texture>("Res/test.tga");
	box1->scale = { 0.2f, 0.2f, 0.2f };
	box1->color[0] = 0.5f;
	box1->position.z = -2;

	GameObjectPtr crystal = engine.CreateGameObject<GameObject>("crystal");
	crystal->meshId = 1;
	crystal->position = { 2, 2, -2 };
	crystal->texColor = std::make_shared<Texture>("Res/crystal_blue.tga");

	return true;
}
