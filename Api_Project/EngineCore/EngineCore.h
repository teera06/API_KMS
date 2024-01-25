#pragma once
// Level1
#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineTime.h>

// Level2
#include <EnginePlatform\EngineWindow.h>
#include <EnginePlatform\EngineInput.h>

#include <map>

// 같은 Level의 클래스는 전방 선언식으로 관리하는 듯
class ULevel;

// 설명 : 엔진 실행을 담당 -> 엔진 위 레벨을 관리 MAP
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

	// 하나는 무조건 만들어지고 사라질일이 없을것이므ㅗ.
	// 코어가 윈도우를 가지고
	EngineWindow MainWindow; // 윈도우를 가진다.
	EngineTime MainTimer; // 엔진 시간을 가진다.

	static void EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore); // 시간 체크와 윈도우 창 생성 및 루프 유지

	void CoreInit(HINSTANCE _Init); // 윈도우창 생성

	// 가상함수
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

	// 레벨(stage) 관리 : map
	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpper(_Name);

		if (true == AllLevel.contains(UpperName))
		{
			MsgBoxAssert(std::string(_Name) + "이라는 이름의 Level을 또 만들려고 했습니다");
		}

		LevelType* NewLevel = new LevelType();
		LevelInit(NewLevel);
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel));
	}

	// 레벨(stage) 이동
	void ChangeLevel(std::string_view _Name);

protected:
	// 엔진코어는 누가 함부로 건들면 안된다.
	EngineCore();

private:
	bool EngineInit = false;

	std::map<std::string, ULevel*> AllLevel; // Map을 이용한 레벨 관리
	ULevel* CurLevel = nullptr; // 현재 레벨을 저장

	static void EngineTick(); // 엔진속 Level을 관리 -> 여기서 부터 지정된 레벨을 실행
	static void EngineEnd(); // 엔진 종료의 릭관리 -> 저장된 레벨 메모리들 정리

	void LevelInit(ULevel* _Level);
};

// 전역 변수-> GEngine을 줌으로써 Level3에서 ChangeLevel 사용 가능
extern EngineCore* GEngine; // 언리얼식


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