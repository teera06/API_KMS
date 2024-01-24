#pragma once
#include <EngineBase\EngineDebug.h>
#include <EnginePlatform\EngineWindow.h>
#include <EngineBase\EngineString.h>
#include <map>


class ULevel; // ���� ���� -> �𸮾� ������ ó��
// ��� : ������ ������ �� �߰� �ٸ� ����
class EngineCore
{
public:
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	// �ϳ��� ������ ��������� ��������� �������̹Ǥ�.
	// �ھ �����츦 ������ �ִ�.
	EngineWindow MainWindow; // �ھ�(������)

	static void EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore);
	// ���� ���� ��� -> Game_Core �� ������ �κ��� �ھ ������� ����â ����

	void CoreInit(HINSTANCE _Init); // ������ â ���� -> �ϳ��� ���α׷��� �����ް� -> �� ���� ������ ����
	// ���α׷� �ڵ�
	// ������ �ڵ�
	// â ����

	// �����Լ�
	virtual void BeginPlay(); // start
	virtual void Tick(float _DeltaTime); // update
	virtual void End();

	// ������ ������ �κ� -> ������ ������ְ� map���� ���� ����
	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpper(_Name);

		if (true == AllLevel.contains(UpperName))
		{
			MsgBoxAssert(std::string(_Name) + "�̶�� �̸��� Level�� �� ������� �߽��ϴ�");
		}

		LevelType* NewLevel = new LevelType(); // �����Ҵ�
		LevelInit(NewLevel);
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel));
	}

	void ChangeLevel(std::string_view _Name); // ���� ���� ���

protected:
	// ���������� ����Ҽ� �ֱ⿡ ����
	EngineCore();

private:
	bool EngineInit = false;

	std::map<std::string, ULevel*> AllLevel; // Map�� ���� Level ����
	ULevel* CurLevel = nullptr; // ������ Level

	static void EngineTick(); // Tick = Update 
	static void EngineEnd();

	void LevelInit(ULevel* _Level);
};

extern EngineCore* GEngine; // ���� ���� EngineCore�� ������.

// ������ Core���ٰ� ����� ���� ��ũ�� ó��
#define ENGINESTART(USERCORE) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
    LeakCheck; \
	USERCORE NewUserCore = USERCORE(); \
	EngineCore::EngineStart(hInstance, &NewUserCore); \
}