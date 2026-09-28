/**
* @file Collision.h
*/


#pragma once


#include "../Engine/Math.h"


/**
* 軸平行境界ボックス
*/
struct AABB
{
	vec3 min;
	vec3 max;
};


/// <summary>
/// AABB同士の交差判定処理
/// </summary>
/// <param name="a">AABBその①</param>
/// <param name="b">AABBその②</param>
/// <param name="penetration">貫通距離</param>
/// <returns>交差しているかどうか</returns>
bool Intersect(const AABB& a, const AABB& b, vec3& penetration);
