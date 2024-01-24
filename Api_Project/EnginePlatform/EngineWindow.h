#pragma once
#include <Windows.h>
#include <string>
// 설명 :
class EngineWindow
{
public:
	// constrcuter destructer
	EngineWindow();
	~EngineWindow();

	// delete Function
	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

	//----------------------------------------------------------------

	void Open(std::string_view _Title = "Title");

	static void Init(HINSTANCE _hInst);
	static unsigned __int64 WindowMessageLoop(void(*_Update)(), void(*_End)());

	HDC GetWindowDC()
	{
		return hDC;
	}

protected:

private:
	// 클래스의 객체 모두가 공유하는 개념의 값 -> 클래스 안의 전역 변수와 같은 느낌
	static bool WindowLive; 
	static HINSTANCE hInstance; // 프로그램 핸들 
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	// 프로그래머야 네가 함수포인터를 넣어주면 윈도우에 무슨일이 생겼을때 그걸 내가 대신 실행해줄께. (CALLBack)
	// 윈도우가 변화에 대해 대신 실행

	HWND hWnd = nullptr; // 윈도우 핸들
	HDC hDC = nullptr; // 윈도우 그리기 기능
};

