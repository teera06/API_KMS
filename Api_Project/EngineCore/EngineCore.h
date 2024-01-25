#pragma once
// Level1
#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineTime.h>

// Level2
#include <EnginePlatform\EngineWindow.h>
#include <EnginePlatform\EngineInput.h>

#include <map>

// ���� Level�� Ŭ������ ���� ��������� �����ϴ� ��
class ULevel;

// ���� : ���� ������ ��� -> ���� �� ������ ���� MAP
class EngineCore
{
public:
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	// -------------------------------------------------------------

	// �ϳ��� ������ ��������� ��������� �������̹Ǥ�.
	// �ھ �����츦 ������
	EngineWindow MainWindow; // �����츦 ������.
	EngineTime MainTimer; // ���� �ð��� ������.

	static void EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore); // �ð� üũ�� ������ â ���� �� ���� ����

	void CoreInit(HINSTANCE _Init); // ������â ����

	// �����Լ�
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

	// ����(stage) ���� : map
	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpper(_Name);

		if (true == AllLevel.contains(UpperName))
		{
			MsgBoxAssert(std::string(_Name) + "�̶�� �̸��� Level�� �� ������� �߽��ϴ�");
		}

		LevelType* NewLevel = new LevelType();
		LevelInit(NewLevel);
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel));
	}

	// ����(stage) �̵�
	void ChangeLevel(std::string_view _Name);

protected:
	// �����ھ�� ���� �Ժη� �ǵ�� �ȵȴ�.
	EngineCore();

private:
	bool EngineInit = false;

	std::map<std::string, ULevel*> AllLevel; // Map�� �̿��� ���� ����
	ULevel* CurLevel = nullptr; // ���� ������ ����

	static void EngineTick(); // ������ Level�� ���� -> ���⼭ ���� ������ ������ ����
	static void EngineEnd(); // ���� ������ ������ -> ����� ���� �޸𸮵� ����

	void LevelInit(ULevel* _Level);
};

// ���� ����-> GEngine�� �����ν� Level3���� ChangeLevel ��� ����
extern EngineCore* GEngine; // �𸮾��


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