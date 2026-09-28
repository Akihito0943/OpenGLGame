/**
 * @file GameObject.h
 */


#pragma once


#include <vector>
#include <string>
#include <memory>

#include "Math.h"
#include "Texture.h"
#include "../Component/Component.h"


 // 先行宣言
class Engine;
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectList = std::vector<GameObjectPtr>;


/**
* 物体の基底クラス
*/
class GameObject
{
	friend Engine;

public:
	GameObject() = default;
	virtual ~GameObject() = default;

public:
	/// <summary>
	/// ゲームエンジンを取得する
	/// </summary>
	/// <returns>ゲームエンジン</returns>
	Engine* GetEngine() const { return engine; }


	/// <summary>
	/// ゲームオブジェクトをエンジンから削除する
	/// </summary>
	void Destroy() { isDestroyed = true; }


	/// <summary>
	/// ゲームオブジェクトが削除されていたらTrueを返す
	/// </summary>
	/// <returns>削除されたかどうか</returns>
	bool IsDestroyed() const { return isDestroyed; }


	/// <summary>
	/// ゲームオブジェクトにコンポーネントを追加する
	/// </summary>
	/// <typeparam name="T">Component及びその派生クラス</typeparam>
	/// <returns>作成したコンポーネント</returns>
	template<typename T> std::shared_ptr<T> AddComponent()
	{
		auto p = std::make_shared<T>();
		p->owner = this;
		components.push_back(p);
		p->Awake();
		return p;
	}


	/// <summary>
	/// ゲームオブジェクトから削除されたコンポーネントを削除する
	/// </summary>
	void RemoveDestroyedComponent();


	/// <summary>
	/// ゲームオブジェクトを初期化する
	/// </summary>
	virtual void Start();


	/// <summary>
	/// ゲームオブジェクトを更新する
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void Update(float deltaTime);


	/// <summary>
	/// 衝突が起きた際の処理
	/// </summary>
	/// <param name="self">自身のコンポーネント</param>
	/// <param name="other">衝突相手のコンポーネント</param>
	virtual void OnCollision(const ComponentPtr& self, const ComponentPtr& other);


	/// <summary>
	/// ゲームオブジェクトがエンジンから削除される際の処理
	/// </summary>
	virtual void OnDestroy();

public:
	// オブジェクト名
	std::string name = "";

	// 物体の位置
	vec3 position = { 0, 0,0 };

	// 物体の回転
	vec3 rotation = { 0, 0,0 };

	// 物体の拡大率
	vec3 scale = { 1,1,1 };

	// 物体の色
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	// カラーテクスチャー
	TexturePtr texColor = nullptr;

	// メッシュID(デフォルトで正方形
	int meshId = 0;

private:
	// エンジンのアドレス
	Engine* engine = nullptr;

	// 死亡フラグ
	bool isDestroyed = false;

	// コンポーネントの配列
	std::vector<ComponentPtr> components = {};
};
