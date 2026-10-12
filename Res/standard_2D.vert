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
 layout(location = 0) uniform mat4 transform; // 座標変換ベクトル
 layout(location = 1) uniform mat4 cameraTransform; // カメラの座標変換ベクトル
 layout(location = 2) uniform vec2 aspectRatioAndScaleFov; // アスペクト比と視野角による拡大率


 void main()
 {
	// テクスチャ座標の設定
	outTexcoord = inTexcoord;

	// ローカル座標系からワールド座標系に変換
	gl_Position = transform * vec4(inPosition, 1);

	// ワールド座標系からビュー座標系に変換
	gl_Position = cameraTransform * gl_Position;

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