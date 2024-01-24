#pragma once
#include <Windows.h>
#include <string>
// ���� :
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
	// Ŭ������ ��ü ��ΰ� �����ϴ� ������ �� -> Ŭ���� ���� ���� ������ ���� ����
	static bool WindowLive; 
	static HINSTANCE hInstance; // ���α׷� �ڵ� 
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	// ���α׷��Ӿ� �װ� �Լ������͸� �־��ָ� �����쿡 �������� �������� �װ� ���� ��� �������ٲ�. (CALLBack)
	// �����찡 ��ȭ�� ���� ��� ����

	HWND hWnd = nullptr; // ������ �ڵ�
	HDC hDC = nullptr; // ������ �׸��� ���
};

