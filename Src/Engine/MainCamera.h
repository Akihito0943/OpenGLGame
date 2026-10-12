/**
* @file MainCamera.h
*/


#pragma once


#include "GameObject.h"


/**
* メインカメラ
*/
class MainCamera : public GameObject
{
public:
	MainCamera() = default;
	virtual ~MainCamera() = default;

public:
	/// <summary>
	/// カメラの座標変換行列を作成する
	/// </summary>
	/// <returns>座標変換行列</returns>
	mat4 GetCameraTransformMatrix();
};