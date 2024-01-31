#pragma once
#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineTime.h>

#include <EnginePlatform\EngineWindow.h>
#include <EnginePlatform\EngineInput.h>
#include <map>


class ULevel;
// 설명 :
class UEngineCore
{
public:
	~UEngineCore();

	// delete Function
	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;

	// 하나는 무조건 만들어지고 사라질일이 없을것이므ㅗ.
	// 코어가 윈도우를 가지고
	UEngineWindow MainWindow;
	EngineTime MainTimer;

	static void EngineStart(HINSTANCE _hInstance, UEngineCore* _UserCore);

	void CoreInit(HINSTANCE _Init);

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

	// Level Create -> EngineCore에서 관리
	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name); // Level 이름 대문자로 통일

		if (true == AllLevel.contains(UpperName)) // 이미 있는 레벨을 생성할려 할 경우 에러
		{
			MsgBoxAssert(std::string(_Name) + "이라는 이름의 Level을 또 만들려고 했습니다");
		}

		LevelType* NewLevel = new LevelType(); // 동적 할당
		LevelInit(NewLevel);
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel));
	}

	void ChangeLevel(std::string_view _Name);

	void SetFrame(int _Frame)
	{
		Frame = _Frame;
		FrameTime = 1 / static_cast<float>(Frame);
	}

protected:
	UEngineCore();

private:
	int Frame = -1;
	float FrameTime = 0.0f;
	float CurFrameTime = 0.0f;

	bool EngineInit = false;
	std::map<std::string, ULevel*> AllLevel; // Map에서 Level 관리
	ULevel* CurLevel = nullptr;

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
	UEngineCore::EngineStart(hInstance, &NewUserCore); \
}