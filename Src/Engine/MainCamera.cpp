/**
* @file MainCamera.h
*/


#include "MainCamera.h"


/// <summary>
/// カメラの座標変換行列を作成する
/// </summary>
/// <returns>座標変換行列</returns>
mat4 MainCamera::GetCameraTransformMatrix()
{
	// カメラの逆移動
	mat4 translate = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(-position, 1)
	);
	// カメラの回転
	mat4 rotation = mat4(GetRotationMatrix(-this->rotation));

	// ゲームオブジェクトとは逆順でかける
	return rotation * translate;
}
