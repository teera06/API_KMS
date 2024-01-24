#pragma once
#include <Windows.h>
#include <assert.h>

// ��� : ��üũ �� ���� ���
namespace EngineDebug
{
// (1) ��üũ
#define LeakCheck _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
// (2) ���� ���
#define MsgBoxAssert(Value) \
	std::string ErrorText = std::string(Value); \
	MessageBoxA(nullptr, ErrorText.c_str(), "ġ���� ����", MB_OK); assert(false);
}

