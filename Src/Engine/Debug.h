/**
 * @file Debug.h
 */


#pragma once


/// <summary>
/// OpenGLからのメッセージを処理するコールバック関数
/// </summary>
/// <param name="source">メッセージ送信者</param>
/// <param name="type">メッセージの種類</param>
/// <param name="id">メッセージのID</param>
/// <param name="severity">メッセージの重要度</param>
/// <param name="length">メッセージの長さ</param>
/// <param name="message">メッセージ本体</param>
/// <param name="userParam">ユーザーパラメータ</param>
/// <returns></returns>
void __stdcall DebugCallback(unsigned int source, unsigned int type, unsigned int id,
    unsigned int severity, int length, const char* message, const void* userParam);