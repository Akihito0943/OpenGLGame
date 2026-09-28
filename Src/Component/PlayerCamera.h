/**
 * @file PlayerCamera.h
 */


#pragma once


#include "Component.h"


/**
* プレイヤーカメラ操作コンポーネント
*/
class PlayerCamera : public Component
{
public:
	PlayerCamera() = default;
	virtual ~PlayerCamera() = default;

public:
	/// <summary>
	/// 毎フレーム更新処理
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void Update(float deltaTime) override;
};