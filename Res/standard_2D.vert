/**
 * @file standerd_2D.vert
 */

 #version 450


 // シェーダへの入力
 layout(location = 0) in vec3 inPosition; // 頂点座標
 layout(location = 1) in vec2 inTexcoord; // 頂点テクスチャ座標

 // シェーダからの出力
 layout(location = 1) out vec2 outTexcoord; // 頂点テクスチャ座標

 // プログラムからの入力
 layout(location = 0) uniform vec3 scale; // スケール
 layout(location = 1) uniform vec3 position; // 位置
 layout(location = 2) uniform vec2 rotationY; // Y軸回転
 layout(location = 3) uniform vec2 aspectRatioAndScaleFov; // アスペクト比と視野角による拡大率
 layout(location = 4) uniform vec3 cameraPosition; // カメラの位置
 layout(location = 5) uniform vec2 cameraRotationY; // カメラのY軸回転


 void main()
 {
	// テクスチャ座標の設定
	outTexcoord = inTexcoord;


	// ローカル座標系からワールド座標系に変換
 	vec3 pos = inPosition * scale;

	float sinY = rotationY.x;
	float cosY = rotationY.y;
	gl_Position.x = pos.x * cosY + pos.z * sinY;
	gl_Position.y = pos.y;
	gl_Position.z = pos.x * -sinY + pos.z * cosY;
	
	gl_Position.xyz += position;

	// ワールド座標系からビュー座標系に変換
	pos = gl_Position.xyz - cameraPosition;
	float cameraSinY = cameraRotationY.x;
	float cameraCosY = cameraRotationY.y;
	gl_Position.x = pos.x * cameraCosY + pos.z * cameraSinY;
	gl_Position.y = pos.y;
	gl_Position.z = pos.x * -cameraSinY + pos.z * cameraCosY;

	// ビュー座標系からクリップ座標系に変換
	gl_Position.xy *= aspectRatioAndScaleFov;

	// 深度値の計算結果が-1~+1になるようなA,Bを計算
	const float near = 0.5;
	const float far = 1000;
	const float A = -2 * far * near / (far - near);
	const float B = (far + near) / (far - near);

	// 遠近法を有効か
	gl_Position.w = -gl_Position.z;
	gl_Position.z = -gl_Position.z * B + A; 
 }