/**
* @file Collision.h
*/


#pragma once

#include <vector>

#include "../Engine/Math.h"
#include "Collider.h"


// 先行宣言
class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectList = std::vector<GameObjectPtr>;


/**
* 軸平行境界ボックス
*/
struct AABB
{
	vec3 min;
	vec3 max;
};


/*
* ワールド座標系に変換したコライダー
*/
struct WorldCollider
{
	ColliderPtr origin;
	ColliderPtr world;
};
using WorldColliderList = std::vector<WorldCollider>;


namespace Collision {
	/// <summary>
	/// ゲームオブジェクト同士の当たり判定を行う
	/// </summary>
	/// <param name="gameObjects">ゲームオブジェクト配列</param>
	void HandleGameObjectCollision(const GameObjectList& gameObjects);


	/// <summary>
	/// AABB同士の交差判定処理
	/// </summary>
	/// <param name="a">AABBその①</param>
	/// <param name="b">AABBその②</param>
	/// <param name="penetration">貫通距離</param>
	/// <returns>交差しているかどうか</returns>
	bool Intersect(const AABB& a, const AABB& b, vec3& penetration);
}