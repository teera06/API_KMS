#include "EngineWindow.h"
#include <EngineBase\EngineDebug.h>

bool EngineWindow::WindowLive = true;
HINSTANCE EngineWindow::hInstance;

// 윈도우 창 변화에 따른 실행값
LRESULT CALLBACK EngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		WindowLive = false;
		// PostQuitMessage(123213);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // 기본 유지값
	}
	return 0;
}

void EngineWindow::Init(HINSTANCE _hInst)
{
	hInstance = _hInst;
}


EngineWindow::EngineWindow()
{
}

EngineWindow::~EngineWindow()
{
}

// 윈도우창 생성 및 열기
void EngineWindow::Open(std::string_view _Title /*= "Title"*/)
{
	// 간혹가다가 앞쪽이이나 뒤쪽에 W가 붙거나 A가 붙어있는 함수들을 보게 될겁니다.
	// A가 붙어있으면 멀티바이트 함수
	// W가 붙어있으면 와이드 바이트 함수
	WNDCLASSEXA wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; // 프로그래머와 윈도우의 콜백 서로에게 연락
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "DefaultWindow";
	wcex.hIconSm = nullptr;

	RegisterClassExA(&wcex);

	// const std::string& = 내부에 뭘들고 있다고 생각하라고 했나요?
	// std::vector<char> 들고 있다고 생각하라고 했다.
	// _Title[0] = char&를 리턴해준 것과 같다.
	// _Title.c_str(); => 자연스럽게 내부에서 
	// const char* Test = &_Title[0]
	// return Test;

	// ??? 프로그램의 ??? 윈도우 지정
	hWnd = CreateWindowA("DefaultWindow", _Title.data(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		MsgBoxAssert("윈도우 생성에 실패했습니다.");
		return;
	}

	hDC = GetDC(hWnd); // ??? 윈도우의 그리기 기능 값을 받음

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

// 윈도우 창 유지
unsigned __int64 EngineWindow::WindowMessageLoop(void(*_Update)(), void(*_End)()) //
{
	MSG msg = {};

	while (WindowLive) // 윈도우창이 유지 될때
	{
		// 기본 메시지 루프입니다:
		// 10개가 들어있을 
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// 메세지 루프의 데드타임이라는 곳에서 실행됩니다.
		if (nullptr != _Update)
		{
			_Update();
		}
	}

	if (nullptr != _End)
	{
		_End();
	}

	return msg.wParam;
}


