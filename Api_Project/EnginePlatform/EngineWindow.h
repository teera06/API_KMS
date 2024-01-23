#pragma once
// ���� ���� -> ���� �ǵ��� ����
#include <Windows.h>
#include <string>
// ���� : ���� -> ������â ����
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
	// const string& -> ������� ���� ���� -> 
	// string -> vector<char> �� ���� -> vector �ȿ����� ���� �Ҵ��� �߻�
	// �׷��⿡ ����ȭ ����� string_view ��� -> ���� ����ó�� ��� -> �����Ҵ� ���� �߻� ����

	static void Init(HINSTANCE _hInst); // Set -> HINSTANCE
	static unsigned __int64 WindowMessageLoop(); // ������ ���� -> ȭ��â�� ���°��� ���������ش�.

protected:

private:
	static bool WindowLive;
	static HINSTANCE hInstance; // ���α׷� �ڵ� -> �ּҿ� ���� �������� �����찡 ���� ��Ŵ
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	HWND hWnd = nullptr; // ������ �ڵ� -> HINSTANCE���� �������� ���������� ������
	HDC hDC = nullptr; // �����쿡 �׸��� �ִ� ����
};

