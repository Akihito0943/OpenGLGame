#include "Collision.h"
/**
* @file Collision.cpp
*/


/// <summary>
/// AABB同士の交差判定処理
/// </summary>
/// <param name="a">AABBその①</param>
/// <param name="b">AABBその②</param>
/// <param name="penetration">貫通距離</param>
/// <returns>交差しているかどうか</returns>
bool Intersect(const AABB& a, const AABB& b, vec3& penetration)
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


	// 交差確定
	return true;
}
