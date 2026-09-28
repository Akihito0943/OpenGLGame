/**
 * @file PlayerCamera.cpp
 */


#include "PlayerCamera.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObject.h"


/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name="deltaTime"></param>
void PlayerCamera::Update(float deltaTime)
{
	// カメラの移動
	GameObject& camera = GetOwner()->GetEngine()->GetMainCamera();
	const float cameraSpeed = 0.0005f;
	const float cameraCos = cosf(camera.rotation.y);
	const float cameraSin = sinf(camera.rotation.y);
	Engine* engine = GetOwner()->GetEngine();
	if (engine->GetKey(GLFW_KEY_A)) {
		camera.position.x -= cameraSpeed * cameraCos;
		camera.position.z -= cameraSpeed * -cameraSin;
	}
	if (engine->GetKey(GLFW_KEY_D)) {
		camera.position.x += cameraSpeed * cameraCos;
		camera.position.z += cameraSpeed * -cameraSin;
	}
	if (engine->GetKey(GLFW_KEY_W)) {
		camera.position.x -= cameraSpeed * cameraSin;
		camera.position.z -= cameraSpeed * cameraCos;
	}
	if (engine->GetKey(GLFW_KEY_S)) {
		camera.position.x += cameraSpeed * cameraSin;
		camera.position.z += cameraSpeed * cameraCos;
	}
	if (engine->GetKey(GLFW_KEY_E)) {
		camera.rotation.y -= 0.0005f;
	}
	if (engine->GetKey(GLFW_KEY_Q)) {
		camera.rotation.y += 0.0005f;
	}
}
