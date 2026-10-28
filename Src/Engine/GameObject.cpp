/**
 * @file GameObject.cpp
 */


#include <algorithm>

#include "GameObject.h"


/// <summary>
/// デストラクタ
/// </summary>
GameObject::~GameObject()
{
	// オブジェクトが消える際に親子関係を解除する
	SetParent(nullptr);

	// 自身を親にしているオブジェクトから親を解除する
	for (auto& c : children) {
		c->parent = nullptr;
	}
}


/// <summary>
 /// ゲームオブジェクトから削除されたコンポーネントを削除する
 /// </summary>
void GameObject::RemoveDestroyedComponent()
{
	if (components.empty()) return;

	// 廃棄予定の有無でコンポーネントを分ける
	std::vector<ComponentPtr>::iterator iter = std::stable_partition(
		components.begin(), components.end(),
		[](const ComponentPtr& c) { return !c->IsDestroyed(); });

	// 廃棄予定のコンポーネントを別の配列に移動する
	std::vector<ComponentPtr> destroyedComponentList(
		std::move_iterator(iter), std::move_iterator(components.end())
	);

	// オリジナル配列から移動済みコンポーネントを削除
	components.erase(iter, components.end());

	// コライダーはcollidersにも登録されているためこちらも削除
	std::vector<ColliderPtr>::iterator iter2 = std::remove_if(
		colliders.begin(), colliders.end(),
		[](const ColliderPtr& c) { return c->IsDestroyed(); });
	colliders.erase(iter2, colliders.end());

	// 廃棄予定コンポーネントリストのOnDestroyを実行
	for (ComponentPtr& p : destroyedComponentList) {
		p->OnDestroy();
	}

	/*
	* ローカル変数のdestroyedComponentListがここで寿命つき、
	* 削除予定コンポーネントの参照が全て消えるのでコンポーネント
	* 自体もここで削除される。
	*/
}


/// <summary>
/// 親オブジェクトを設定する(nullptrを指定すると解消)
/// </summary>
/// <param name="parent">親オブジェクト</param>
void GameObject::SetParent(GameObject* parent)
{
	// 同じ親を設定された場合は何もしない
	if (parent == this->parent) return;

	// 別の親が設定されている場合は、その親との関係を解除
	if (this->parent) {
		std::vector<GameObject*>& c = this->parent->children;
		auto itr = std::find(c.begin(), c.end(), this);
		// 配列から自身を削除
		if (itr != c.end()) c.erase(itr);
	}

	// 新しい親を設定
	if (parent) {
		parent->children.push_back(this);
	}
	this->parent = parent;
}

void GameObject::SetParent(const GameObjectPtr& parent)
{
	SetParent(parent.get());
}


/// <summary>
/// ゲームオブジェクトを初期化する
/// </summary>
void GameObject::Start()
{
	for (ComponentPtr& p : components) {
		if (!p->isStarted) {
			p->Start();
			p->isStarted = true;
		}
	}
}


/// <summary>
/// ゲームオブジェクトを更新する
/// </summary>
/// <param name="deltaTime"></param>
void GameObject::Update(float deltaTime)
{
	for (ComponentPtr& p : components) {
		p->Update(deltaTime);
	}
	RemoveDestroyedComponent();
}


/// <summary>
/// 衝突が起きた際の処理
/// </summary>
/// <param name="self">自身のコンポーネント</param>
/// <param name="other">衝突相手のコンポーネント</param>
void GameObject::OnCollision(const ComponentPtr& self, const ComponentPtr& other)
{
	for (ComponentPtr& p : components) {
		p->OnCollision(self, other);
	}
}


/// <summary>
/// ゲームオブジェクトがエンジンから削除される際の処理
/// </summary>
void GameObject::OnDestroy()
{
	for (ComponentPtr& p : components) {
		p->OnDestroy();
	}
}
