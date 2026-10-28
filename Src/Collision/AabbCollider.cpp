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
	// 座標変換したコライダーのコピー
	std::shared_ptr<AabbCollider> p = std::make_shared<AabbCollider>();
	p->aabb.min = vec3(transform * vec4(aabb.min, 1));
	p->aabb.max = vec3(transform * vec4(aabb.max, 1));

	// 回転やスケーリングされるとmin > maxとなる場合があるため
	// minの方が大きければ入れ替える
	for (int i = 0; i < 3; i++)	{
		if (p->aabb.min[i] > p->aabb.max[i]) {
			const float tmp = p->aabb.max[i];
			p->aabb.max[i] = p->aabb.min[i];
			p->aabb.min[i] = tmp;
		}
	}

	return p;
}
