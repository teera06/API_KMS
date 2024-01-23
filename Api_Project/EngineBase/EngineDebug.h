#pragma once
#include <Windows.h>
#include <assert.h>

#define LeakCheck _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

#define MsgBoxAssert(TEXT) MessageBoxA(nullptr, TEXT, "치명적 에러", MB_OK); assert(false);

class EngineDebug
{
public:
	// constrcuter destructer
	EngineDebug(); // 디폴트 생성자
	~EngineDebug(); // 디폴트 소멸자

	// delete Function
	EngineDebug(const EngineDebug& _Other) = delete; // 디폴트 복사 생성자
	EngineDebug(EngineDebug&& _Other) noexcept = delete; 
	EngineDebug& operator=(const EngineDebug& _Other) = delete; // 디폴트 대입 연산자
	EngineDebug& operator=(EngineDebug&& _Other) noexcept = delete;

protected:

private:
};

