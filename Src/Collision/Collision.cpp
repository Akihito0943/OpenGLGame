/**
* @file Collision.cpp
*/


#include "Collision.h"
#include "../Engine/GameObject.h"


/// <summary>
/// ゲームオブジェクト同士の当たり判定を行う
/// </summary>
/// <param name="gameObjects">ゲームオブジェクト配列</param>
void Collision::HandleGameObjectCollision(const GameObjectList& gameObjects)
{
	// ワールド座標系の衝突判定を作成
	std::vector<WorldColliderList> colliders;
	colliders.reserve(gameObjects.size());
	for (const GameObjectPtr& e : gameObjects) {
		if (e->colliders.empty()) continue;

		WorldColliderList list(e->colliders.size());
		for (int i = 0; i < e->colliders.size(); i++) {
			// オリジナルのコライダーをコピー
			list[i].origin = e->colliders[i];
			list[i].world = e->colliders[i]->GetTransformedCollider(e->GetTransform());
		}
	}
}


/// <summary>
/// AABB同士の交差判定処理
/// </summary>
/// <param name="a">AABBその①</param>
/// <param name="b">AABBその②</param>
/// <param name="penetration">貫通距離</param>
/// <returns>交差しているかどうか</returns>
bool Collision::Intersect(const AABB& a, const AABB& b, vec3& penetration)
{
	// aの左側がbの右側より右にある場合は交差していない
	const float dx0 = b.max.x - a.min.x;
	if (dx0 <= 0) return false;

	// aの右側がbの左側より左にある場合は交差していない
	const float dx1 = a.max.x - b.min.x;
	if (dx1 <= 0) return false;

	// aの下側がbの上側よりも上にある場合は交差していない
	const float dy0 = b.max.y - a.min.y;
	if (dy0 <= 0) return false;

	// aの上側がbの下側よりも下にある場合は交差していない
	const float dy1 = a.max.y - b.min.y;
	if (dy1 <= 0) return false;

	// aの奥側がbの手前側より手前にある場合は交差していない
	const float dz0 = b.max.z - a.min.z;
	if (dz0 <= 0) return false;

	// aの手前側がbの奥側より奥にある場合は交差していない
	const float dz1 = a.max.z - b.min.z;
	if (dz1 <= 0) return false;


	/**
	* 交差確定
	*/


	// 貫通距離を計算

	vec3 length = { dx1, dy1, dz1 }; // 貫通距離の絶対値
	vec3 signedLength = length;		 // 符号付きの貫通距離

	// XYZの各軸で重なっている距離が短い方向を選択
	if (dx0 < dx1) {
		length.x = dx0;
		signedLength.x = -dx0;
	}
	if (dy0 < dy1) {
		length.y = dy0;
		signedLength.y = -dy0;
	}
	if (dz0 < dz1) {
		length.z = dz0;
		signedLength.z = -dz0;
	}

	// XYZの内、最も短い方向を選択
	if (length.x < length.y) {
		if (length.x < length.z) {
			penetration = { signedLength.x, 0, 0 };
			return true;
		}
	}
	else if (length.y < length.z) {
		penetration = { 0,signedLength.y,0 };
		return true;
	}
	penetration = { 0, 0,signedLength.z };
	return true;
}