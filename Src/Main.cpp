/**
 * @file Main.cpp
 */


#include <Windows.h>

#include "Engine/Engine.h"


/**
 * エントリーポイント
 */
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	Engine engine;
	return engine.Run();
}