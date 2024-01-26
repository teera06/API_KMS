#pragma once
#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineTime.h>

#include <EnginePlatform\EngineWindow.h>
#include <EnginePlatform\EngineInput.h>
#include <map>

// ���� ���� -> �𸮾��
class ULevel;
// ���� :
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
	// �ھ �����츦 ������
	EngineWindow MainWindow; // ������ â
	EngineTime MainTimer; // �ð�üũ

	// (�ֿ� �κ�)���� ���� ->  �ð� üũ -> ������â ���� -> ���� ���� -> ������ ���� ������â ����
	static void EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore);
	void CoreInit(HINSTANCE _Init);
	//-------------------------------------------------------------------

	// �����Լ�
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

	// Map�� ���� ���� ����
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

	// ���� Level ��ġ ����
	void ChangeLevel(std::string_view _Name);

	// ������ ����
	void SetFrame(int _Frame)
	{
		Frame = _Frame;
		FrameTime = 1 / static_cast<float>(Frame);
	}

protected:
	// ���� �ھ ���������� ����ϴ� ���� ����
	EngineCore();

private:
	// ������ ���� �ɹ� ����
	int Frame = -1;
	float FrameTime = 0.0f;
	float CurFrameTime = 0.0f;


	bool EngineInit = false;
	std::map<std::string, ULevel*> AllLevel; // ���� Map
	ULevel* CurLevel = nullptr; // ���� ����

	// ���� ������Ʈ
	static void EngineTick(); 
	void CoreTick();  // Level ƽ ����(������ ����, �������� ����, ������, (Actor)�� ����) 
	// --------------------------------

	static void EngineEnd(); // (Level) ������

	void LevelInit(ULevel* _Level);
};

extern EngineCore* GEngine;


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