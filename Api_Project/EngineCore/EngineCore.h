#pragma once
// 엔진 영역 -> 절대 변경 금지
#include <EnginePlatform\EngineWindow.h> // 값형으로 쓰기 위한 헤더 선언

// 설명 : 엔진과 콘텐츠의 중간다리 역할
class EngineCore
{
public:
	// constrcuter destructer
	EngineCore();
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	// 하나는 무조건 만들어지고 사라질일이 없을것이므ㅗ.
	EngineWindow MainWindow; // 엔진 코어에서 윈도우창 생성

	void CoreInit(HINSTANCE _Init);

	// 가상함수 -> 가상테이블 형태로 
	virtual void EngineStart();
	virtual void EngineUpdate();
	virtual void EngineEnd();

protected:

private:
	bool EngineInit = false;

};

// wWinMain을 유저들에게부터 숨기기 위해 #define 처리
#define ENGINESTART(USERCORE) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
	USERCORE NewUserCore; \
	EngineCore* Ptr = &NewUserCore; \
	Ptr->CoreInit(hInstance); \
	Ptr->EngineStart(); \
	EngineWindow::WindowMessageLoop(); \
}

// 게임이 시작하면서 Game_Core를 가지고 들어옴
// Game_Core가 생기고 업캐스팅을 통해
// 부모인 EngineCore에게 Game_Core를 넘겨줌
// EngineCore는 받은 Game_Core를 바탕으로 윈도우창 실행