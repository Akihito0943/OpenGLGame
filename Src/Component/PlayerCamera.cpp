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

	GameObject* player = GetOwner();
	Engine* engine = GetOwner()->GetEngine();
	
	if (engine->GetKey(GLFW_KEY_A)) {
		player->position.x -= cameraSpeed * cameraCos;
		player->position.z -= cameraSpeed * -cameraSin;
	}
	if (engine->GetKey(GLFW_KEY_D)) {
		player->position.x += cameraSpeed * cameraCos;
		player->position.z += cameraSpeed * -cameraSin;
	}
	if (engine->GetKey(GLFW_KEY_W)) {
		player->position.x -= cameraSpeed * cameraSin;
		player->position.z -= cameraSpeed * cameraCos;
	}
	if (engine->GetKey(GLFW_KEY_S)) {
		player->position.x += cameraSpeed * cameraSin;
		player->position.z += cameraSpeed * cameraCos;
	}
	if (engine->GetKey(GLFW_KEY_E)) {
		player->rotation.y -= 0.0005f;
	}
	if (engine->GetKey(GLFW_KEY_Q)) {
		player->rotation.y += 0.0005f;
	}
	if (engine->GetKey(GLFW_KEY_T)) {
		player->rotation.x -= 0.0005f;
	}
	if (engine->GetKey(GLFW_KEY_U)) {
		player->rotation.x += 0.0005f;
	}
	if (engine->GetKey(GLFW_KEY_I)) {
		player->rotation.z -= 0.0005f;
	}
	if (engine->GetKey(GLFW_KEY_O)) {
		player->rotation.z += 0.0005f;
	}

	//if (engine->GetKey(GLFW_KEY_A)) {
	//	camera.position.x -= cameraSpeed * cameraCos;
	//	camera.position.z -= cameraSpeed * -cameraSin;
	//}
	//if (engine->GetKey(GLFW_KEY_D)) {
	//	camera.position.x += cameraSpeed * cameraCos;
	//	camera.position.z += cameraSpeed * -cameraSin;
	//}
	//if (engine->GetKey(GLFW_KEY_W)) {
	//	camera.position.x -= cameraSpeed * cameraSin;
	//	camera.position.z -= cameraSpeed * cameraCos;
	//}
	//if (engine->GetKey(GLFW_KEY_S)) {
	//	camera.position.x += cameraSpeed * cameraSin;
	//	camera.position.z += cameraSpeed * cameraCos;
	//}
	//if (engine->GetKey(GLFW_KEY_E)) {
	//	camera.rotation.y -= 0.0005f;
	//}
	//if (engine->GetKey(GLFW_KEY_Q)) {
	//	camera.rotation.y += 0.0005f;
	//}
	//if (engine->GetKey(GLFW_KEY_T)) {
	//	camera.rotation.x -= 0.0005f;
	//}
	//if (engine->GetKey(GLFW_KEY_U)) {
	//	camera.rotation.x += 0.0005f;
	//}
	//if (engine->GetKey(GLFW_KEY_I)) {
	//	camera.rotation.z -= 0.0005f;
	//}
	//if (engine->GetKey(GLFW_KEY_O)) {
	//	camera.rotation.z += 0.0005f;
	//}
}
