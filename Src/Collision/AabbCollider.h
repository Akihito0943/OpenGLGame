/**
* @file AabbCollider.h
*/


#pragma once


#include "Collider.h"
#include "Collision.h"


/**
* 軸並行境界ボックスコライダー
*/
class AabbCollider : public Collider
{
public:
	AabbCollider() = default;
	virtual ~AabbCollider() = default;

public:
	/// <summary>
	/// 図形の種類を取得する
	/// </summary>
	/// <returns>図形の種類</returns>
	virtual Type GetType() const override { return Type::AABB; }


	/// <summary>
	/// 衝突後の座標を調整する
	/// </summary>
	/// <param name="translate">移動量</param>
	virtual void AddPosition(const vec3& translate) override;


	/// <summary>
	/// 座標変換したコライダーを取得する
	/// </summary>
	/// <param name="transform">変換行列</param>
	/// <returns>座標変換したコライダー</returns>
	virtual ColliderPtr GetTransformedCollider(const mat4& transform) const override;


	/// <summary>
	/// 図形を取得する
	/// </summary>
	/// <returns>自身の図形</returns>
	const AABB& GetShape() const { return aabb; }

public:
	// AABBのサイズ
	AABB aabb = { { -0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f } };

};
