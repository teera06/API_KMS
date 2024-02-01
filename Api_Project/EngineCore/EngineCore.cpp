#include "EngineCore.h"
#include <Windows.h>
#include "Level.h"
#include "EnginePlatform\EngineInput.h"


UEngineCore* GEngine = nullptr;

UEngineCore::UEngineCore()
	: MainWindow()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::CoreTick()
{
	float DeltaTime = MainTimer.TimeCheck(); // 코어가 한 업데이트를 돌때까지의 일정한 수를 센다.
	double dDeltaTime = MainTimer.GetDeltaTime(); // 1초에 100번 -> 0.01초에 1번


	// 100프레임으로 실행되는 컴퓨터가 있다면
	// 0.01이 나와야 한다.
	// float Time;
	// Time += 0.01f;
	// 
	// 우리는 50프레임으로 제한하고 싶다.
	// 0.02가 나와야 한다.
	// FrameTime = 1 / 50.0; =>
	// FrameTime = 0.02;
	// CurFrameTime += 0.01;
	// 0.01             0.02
	// CurFrameTime <= FrameTime
	// CurFrameTime += 0.01;
	// 0.0203000        0.02
	// CurFrameTime <= FrameTime
	// 돌아야한다.
	// 0.0003000
	// CurFrameTime -= FrameTime;

	// 프로그래머가 프레임을 고정(set) 했을때 고정한 프레임에 따른 고정 DeltaTime 제공
	if (1 <= Frame) // 프레임이 0이 될수 없으니 1보다는 커야함
	{
		//               5.0f
		CurFrameTime += DeltaTime;

		//  0.00001        0.016666675
		if (CurFrameTime <= FrameTime)
		{
			return;
		}

		//  0.0167         0.016666675
		CurFrameTime -= FrameTime;
		DeltaTime = FrameTime;
	} 

	EngineInput::KeyCheckTick(DeltaTime); // 키의 상태에 따른 키 체크

	if (nullptr == CurLevel) // 레벨이 지정되지 않았을때의 에러
	{
		MsgBoxAssert("엔진을 시작할 레벨이 지정되지 않았습니다 치명적인 오류입니다");
	}

	// 레벨이 먼저 틱을 돌리고
	CurLevel->Tick(DeltaTime);
	// 액터와 부가적인 오브젝트들의 틱도 돌리고 => 행동하고
	CurLevel->LevelTick(DeltaTime);
	// 랜더러들의 랜더를 통해서 화면에 그림도 그린다 => 그리고
	MainWindow.ScreenClear(); // 윈도우 창 클리어
	CurLevel->LevelRender(DeltaTime);
	MainWindow.ScreenUpdate();
	// 정리한다.(죽어야할 오브젝트들은 다 파괴한다)
	CurLevel->LevelRelease(DeltaTime);


	//HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	//Rectangle(WindowDC, -200, -200, 3000, 3000);
}

void UEngineCore::EngineTick()
{

	// 렉이라는 현상은 프레임사이에 한번에 많은 시간을 소모하는 함수를 호출하면
	// 델타타임이 증가하는 현상을 말한다.
	// EX) for문 1000만번 돌리는데 5초가 걸렸다.
	//    5.0
	//    => 한번에 5.0초 동안 가야할 양을 한프레임만에 이동해버리니까 순간이동하듯이 보이게 된다.

	GEngine->CoreTick();

}

void UEngineCore::EngineEnd()
{
	// std::map<std::string, ULevel*>::iterator StartI

	for (std::pair<const std::string, ULevel*>& _Pair : GEngine->AllLevel)
	{
		if (nullptr == _Pair.second)
		{
			continue;
		}

		delete _Pair.second;
		_Pair.second = nullptr;
	}

	GEngine->AllLevel.clear();
}

void UEngineCore::EngineStart(HINSTANCE _hInstance)
{
	GEngine = this; // Game_Core
	MainTimer.TimeCheckStart(); // 
	CoreInit(_hInstance); // Window OPen
	BeginPlay(); // 엔진 플레이
	UEngineWindow::WindowMessageLoop(EngineTick, EngineEnd); // 게임 실행
}

void UEngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (true == EngineInit)
	{
		return;
	}

	UEngineWindow::Init(_HINSTANCE);
	MainWindow.Open();

	this->AllLevel;

	EngineInit = true;
}

void UEngineCore::BeginPlay()
{

}

void UEngineCore::Tick(float _DeltaTime)
{

}

void UEngineCore::End()
{

}

void UEngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name); // 대문자로 통일 변환

	if (false == AllLevel.contains(UpperName)) // AllLevel에 해당 Level이 없는 경우 에러
	{
		MsgBoxAssert(std::string(_Name) + "라는 존재하지 않는 레벨로 체인지 하려고 했습니다");
	}

	// 눈에 보여야할 레벨이죠?
	CurLevel = AllLevel[UpperName]; // 현재 Level을 바꾼다.
}

void UEngineCore::LevelInit(ULevel* _Level)
{
	_Level->BeginPlay();
}