/**
 * @file Scene.h
 */


#pragma once


#include <memory>


// 先行宣言
class Engine;
class Scene;
using ScenePtr = std::shared_ptr<Scene>;


/**
* シーン基底クラス
*/
class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	/// <summary>
	/// シーンを初期化する
	/// </summary>
	/// <param name="engine">ゲームエンジンの参照</param>
	/// <returns>初期化成功フラグ</returns>
	virtual bool Initialize(Engine& engine) { return true; }


	/// <summary>
	/// シーンを更新する
	/// </summary>
	/// <param name="engine">ゲームエンジンの参照</param>
	/// <param name="deltaTime">前フレームからの経過時間</param>
	virtual void Update(Engine& engine, float deltaTime) {}


	/// <summary>
	/// シーンを終了する
	/// </summary>
	/// <param name="engine">ゲームエンジンの参照</param>
	virtual void Finalize(Engine& engine) {}
};