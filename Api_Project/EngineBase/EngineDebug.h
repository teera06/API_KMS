#pragma once
#include <Windows.h>
#include <assert.h>

#define LeakCheck _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

#define MsgBoxAssert(TEXT) MessageBoxA(nullptr, TEXT, "ġ���� ����", MB_OK); assert(false);

class EngineDebug
{
public:
	// constrcuter destructer
	EngineDebug(); // ����Ʈ ������
	~EngineDebug(); // ����Ʈ �Ҹ���

	// delete Function
	EngineDebug(const EngineDebug& _Other) = delete; // ����Ʈ ���� ������
	EngineDebug(EngineDebug&& _Other) noexcept = delete; 
	EngineDebug& operator=(const EngineDebug& _Other) = delete; // ����Ʈ ���� ������
	EngineDebug& operator=(EngineDebug&& _Other) noexcept = delete;

protected:

private:
};

