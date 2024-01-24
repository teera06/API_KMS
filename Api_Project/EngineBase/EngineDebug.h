#pragma once
#include <Windows.h>
#include <assert.h>

// 기능 : 릭체크 및 에러 경고
namespace EngineDebug
{
// (1) 릭체크
#define LeakCheck _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
// (2) 에러 경고
#define MsgBoxAssert(Value) \
	std::string ErrorText = std::string(Value); \
	MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK); assert(false);
}

