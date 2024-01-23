#pragma once
// 엔진 영역 -> 절대 건들지 말기
#include <Windows.h>
#include <string>
// 설명 : 엔진 -> 윈도우창 관리
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

	void Open(std::string_view _Title = "Title");
	// const string& -> 사용하지 않은 이유 -> 
	// string -> vector<char> 로 생각 -> vector 안에서는 동적 할당이 발생
	// 그렇기에 최적화 방법인 string_view 사용 -> 얕은 복사처럼 사용 -> 동적할당 새로 발생 안함

	static void Init(HINSTANCE _hInst); // Set -> HINSTANCE
	static unsigned __int64 WindowMessageLoop(); // 윈도우 루프 -> 화면창을 띄우는것을 유지시켜준다.

protected:

private:
	static bool WindowLive;
	static HINSTANCE hInstance; // 프로그램 핸들 -> 주소와 같은 정수값을 윈도우가 배정 시킴
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	HWND hWnd = nullptr; // 윈도우 핸들 -> HINSTANCE에서 배정받은 정수값안의 윈도우
	HDC hDC = nullptr; // 윈도우에 그릴수 있는 권한
};

