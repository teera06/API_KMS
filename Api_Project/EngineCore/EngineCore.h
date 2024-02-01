#pragma once
#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineTime.h>

#include <EnginePlatform\EngineWindow.h>
#include <EnginePlatform\EngineInput.h>
#include <map>


class ULevel;
// ���� :
class UEngineCore
{
public:
	~UEngineCore();

	// delete Function
	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;

	// �ϳ��� ������ ��������� ��������� �������̹Ǥ�.
	// �ھ �����츦 ������
	UEngineWindow MainWindow; // ������â 
	EngineTime MainTimer; // �ð�

	void EngineStart(HINSTANCE _hInstance); // ���� ����

	void CoreInit(HINSTANCE _Init); // ������â ����

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

	// (Level)���� ����
	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (true == AllLevel.contains(UpperName)) // Map�� �̹� ���� �̸��� ������ �ִ� ��� ����
		{
			MsgBoxAssert(std::string(_Name) + "�̶�� �̸��� Level�� �� ������� �߽��ϴ�");
		}

		LevelType* NewLevel = new LevelType(); // ���� �Ҵ�
		LevelInit(NewLevel); // Level BeginePlay
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel)); // Map���� ����
	}

	void ChangeLevel(std::string_view _Name); // Level ü����

	void SetFrame(int _Frame) // ������ ����
	{
		Frame = _Frame;
		FrameTime = 1 / static_cast<float>(Frame);
	}

protected:
	// ���� �ھ ���������� �����Ͽ� ����ϸ� �ȵȴ�.
	UEngineCore();

private:
	// ������ ���� �ɹ� ����
	int Frame = -1;
	float FrameTime = 0.0f;
	float CurFrameTime = 0.0f;

	bool EngineInit = false;
	std::map<std::string, ULevel*> AllLevel; // Map���� Level ���� 
	ULevel* CurLevel = nullptr; // ���� ����

	static void EngineTick();
	void CoreTick();
	static void EngineEnd();

	void LevelInit(ULevel* _Level);
};

extern UEngineCore* GEngine;


#define ENGINESTART(USERCORE) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
    LeakCheck; \
	USERCORE NewUserCore = USERCORE(); \
	NewUserCore.EngineStart(hInstance); \
}