/**
* @file AabbCollider.h
*/


#include "AabbCollider.h"


/// <summary>
/// 衝突後の座標を調整する
/// </summary>
/// <param name="translate">移動量</param>
void AabbCollider::AddPosition(const vec3& translate)
{
	aabb.min += translate;
	aabb.max += translate;
}


/// <summary>
/// 座標変換したコライダーを取得する
/// </summary>
/// <param name="transform">変換行列</param>
/// <returns>座標変換したコライダー</returns>
ColliderPtr AabbCollider::GetTransformedCollider(const mat4& transform) const
{
	return ColliderPtr();
}
