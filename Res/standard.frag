/**
 * @file standerd.frag
 */

#version 450


// textureの座標
layout(location = 1) in vec2 inTexCoord;

// テクスチャサンプラ
layout(binding = 0) uniform sampler2D tex;

// プログラムから入力
layout(location = 100) uniform vec4 color;

// 出力する色データ
out vec4 outColor;


void main()
{
	// テクスチャの色を取得（座標を適切にスケーリング）
	vec4 texColor = texture(tex, inTexCoord);

	// 出力する色を設定
	outColor = color * texColor;
}