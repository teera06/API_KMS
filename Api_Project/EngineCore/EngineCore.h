#pragma once
#include <EngineBase\EngineDebug.h>
#include <EnginePlatform\EngineWindow.h>
#include <EngineBase\EngineString.h>
#include <map>


class ULevel; // 전방 선언 -> 언리얼 식으로 처리
// 기능 : 엔진과 컨텐츠 의 중간 다리 역할
class EngineCore
{
public:
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	// 하나는 무조건 만들어지고 사라질일이 없을것이므ㅗ.
	// 코어가 윈도우를 가지고 있다.
	EngineWindow MainWindow; // 코어(윈도우)

	static void EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore);
	// 엔진 실행 담당 -> Game_Core 즉 콘텐츠 부분의 코어를 기반으로 실행창 유지

	void CoreInit(HINSTANCE _Init); // 윈도우 창 생성 -> 하나의 프로그램을 배정받고 -> 그 안의 윈도우 배정
	// 프로그램 핸들
	// 윈도우 핸들
	// 창 오픈

	// 가상함수
	virtual void BeginPlay(); // start
	virtual void Tick(float _DeltaTime); // update
	virtual void End();

	// 엔진의 콘텐츠 부분 -> 레벨을 만들어주고 map에서 레벨 관리
	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpper(_Name);

		if (true == AllLevel.contains(UpperName))
		{
			MsgBoxAssert(std::string(_Name) + "이라는 이름의 Level을 또 만들려고 했습니다");
		}

		LevelType* NewLevel = new LevelType(); // 동적할당
		LevelInit(NewLevel);
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel));
	}

	void ChangeLevel(std::string_view _Name); // 현재 레벨 기록

protected:
	// 여러곳에서 사용할수 있기에 방지
	EngineCore();

private:
	bool EngineInit = false;

	std::map<std::string, ULevel*> AllLevel; // Map을 통해 Level 관리
	ULevel* CurLevel = nullptr; // 현재의 Level

	static void EngineTick(); // Tick = Update 
	static void EngineEnd();

	void LevelInit(ULevel* _Level);
};

extern EngineCore* GEngine; // 전역 변수 EngineCore를 가진다.

// 메인을 Core에다가 숨기기 위해 매크로 처리
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