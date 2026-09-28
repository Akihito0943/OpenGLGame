/**
 * @file Debug.cpp
 */


#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <Windows.h>

#include "Debug.h"


/// <summary>
/// OpenGLからのメッセージを処理するコールバック関数
/// </summary>
/// <param name="source">メッセージ送信者</param>
/// <param name="type">メッセージの種類</param>
/// <param name="id">メッセージのID</param>
/// <param name="severity">メッセージの重要度</param>
/// <param name="length">メッセージの長さ</param>
/// <param name="message">メッセージ本体</param>
/// <param name="userParam"></param>
/// <returns></returns>
void __stdcall DebugCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::string s;
	// ヌル終端文字までの文字列をコピーする(lengthが負の場合はヌル終端)
	if (length < 0) {
		s = message;
	}
	// 指定された長さ分だけ文字列をコピーする(lengthが負でない場合はヌル終端あるか不明)
	else {
		s.assign(message, message + length);
	}

	std::string severityStr;
	severityStr.assign(severity == GL_DEBUG_SEVERITY_HIGH ? "HIGH" :
		severity == GL_DEBUG_SEVERITY_MEDIUM ? "MEDIUM" :
		severity == GL_DEBUG_SEVERITY_LOW ? "LOW" :
		severity == GL_DEBUG_SEVERITY_NOTIFICATION ? "NOTIFICATION" : "UNKNOWN");

	std::string typeStr;
	typeStr.assign(type == GL_DEBUG_TYPE_ERROR ? "ERROR" :
		type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR ? "DEPRECATED_BEHAVIOR" :
		type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR ? "UNDEFINED_BEHAVIOR" :
		type == GL_DEBUG_TYPE_PORTABILITY ? "PORTABILITY" :
		type == GL_DEBUG_TYPE_PERFORMANCE ? "PERFORMANCE" :
		type == GL_DEBUG_TYPE_MARKER ? "MARKER" :
		type == GL_DEBUG_TYPE_PUSH_GROUP ? "PUSH_GROUP" :
		type == GL_DEBUG_TYPE_POP_GROUP ? "POP_GROUP" :
		type == GL_DEBUG_TYPE_OTHER ? "OTHER" : "UNKNOWN");

	s += " (severity: " + severityStr + ", type: " + typeStr + ", id: " + std::to_string(id) + ")";
	s += "\n";
	OutputDebugStringA(s.c_str());
}