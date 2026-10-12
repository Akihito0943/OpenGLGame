/**
* @file Collider.h
*/


#pragma once


#include <memory>

#include "../Component/Component.h"
#include "../Engine/Math.h"


// 先行宣言
class Collider;
using ColliderPtr = std::shared_ptr<Collider>;


/**
* コライダーの基底クラス
*/
class Collider : public Component
{
public:
	Collider() = default;
	virtual ~Collider() = default;

public:
	/// <summary>
	/// 図形の種類
	/// </summary>
	enum class Type
	{
		AABB,	// 軸並行境界ボックス
		Sphere, // 球体
	};


	/// <summary>
	/// 図形の種類を取得する(派生クラスで設定)
	/// </summary>
	/// <returns>図形の種類</returns>
	virtual Type GetType() const = 0;


	/// <summary>
	/// 衝突後の座標を調整する
	/// </summary>
	/// <param name="translate">移動量</param>
	virtual void AddPosition(const vec3& translate) = 0;


	/// <summary>
	/// 座標変換したコライダーを取得する
	/// </summary>
	/// <param name="transform">変換行列</param>
	/// <returns>座標変換したコライダー</returns>
	virtual ColliderPtr GetTransformedCollider(const mat4& transform) const = 0;


public:
	// 衝突するかどうか
	bool isTrigger = false;

	// 動く物体かどうか
	bool isStatic = false;
};