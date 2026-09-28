/**
 * @file GameObject.cpp
 */


#include <algorithm>

#include "GameObject.h"


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
