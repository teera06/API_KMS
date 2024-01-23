#pragma once
// ���� ���� -> ���� ���� ����
#include <EnginePlatform\EngineWindow.h> // �������� ���� ���� ��� ����

// ���� : ������ �������� �߰��ٸ� ����
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

	// �ϳ��� ������ ��������� ��������� �������̹Ǥ�.
	EngineWindow MainWindow; // ���� �ھ�� ������â ����

	void CoreInit(HINSTANCE _Init);

	// �����Լ� -> �������̺� ���·� 
	virtual void EngineStart();
	virtual void EngineUpdate();
	virtual void EngineEnd();

protected:

private:
	bool EngineInit = false;

};

// wWinMain�� �����鿡�Ժ��� ����� ���� #define ó��
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

// ������ �����ϸ鼭 Game_Core�� ������ ����
// Game_Core�� ����� ��ĳ������ ����
// �θ��� EngineCore���� Game_Core�� �Ѱ���
// EngineCore�� ���� Game_Core�� �������� ������â ����