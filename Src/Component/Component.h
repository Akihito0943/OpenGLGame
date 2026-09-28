/**
 * @file Component.h
 */


#pragma once


#include <memory>


 // 先行宣言
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;
class Component;
using ComponentPtr = std::shared_ptr<Component>;


/**
* コンポーネント基底クラス
*/
class Component
{
	friend GameObject;

public:
	Component() = default;
	virtual ~Component() = default;

public:
	/// <summary>
	/// コンポーネントの所有者を取得する
	/// </summary>
	/// <returns>コンポーネントの所有者</returns>
	GameObject* GetOwner() const { return owner; }


	/// <summary>
	/// コンポーネントをゲームオブジェクトから削除する
	/// </summary>
	void Destroy() { isDestroyed = true; }


	/// <summary>
	/// コンポーネントが削除されていたらTrueを返す
	/// </summary>
	/// <returns>削除されたかどうか</returns>
	bool IsDestroyed() const { return isDestroyed; }


	/// <summary>
	/// ゲームオブジェクトに追加された時の処理
	/// </summary>
	virtual void Awake() {}


	/// <summary>
	/// 最初のUpdate時に呼び出される処理
	/// </summary>
	virtual void Start() {}


	/// <summary>
	/// 毎フレーム更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void Update(float deltaTime) {}


	/// <summary>
	/// 衝突が起きた際に呼び出される処理
	/// </summary>
	/// <param name="self">自身のコンポーネント</param>
	/// <param name="other">衝突相手のコンポーネント</param>
	virtual void OnCollision(const ComponentPtr& self, const ComponentPtr& other) {}


	/// <summary>
	/// ゲームオブジェクトがエンジンから削除される際に呼び出される処理
	/// </summary>
	virtual void OnDestroy() {}

private:
	// このコンポーネントの所有者
	GameObject* owner = nullptr;

	// Startが実行されたかどうか
	bool isStarted = false;

	// Destoryが実行されたかどうか
	bool isDestroyed = false;
};