#include "Kirby_Player.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineTime.h>

Kirby_Player::Kirby_Player()
{
}

Kirby_Player::~Kirby_Player()
{
}

void Kirby_Player::BeginPlay()
{
	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

void Kirby_Player::Tick(float _DeltaTime)
{

	if (true == EngineInput::IsPress(VK_LEFT))
	{
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_RIGHT))
	{
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_UP))
	{
		AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	}


	if (true == EngineInput::IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}
	HDC WindowDC = GEngine->MainWindow.GetWindowDC(); // 윈도우 그리기

	

	FTransform Trans = GetTransform(); // 위치, 크기 값 받아오고

	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom()); // 그 정보에 맞게 그려주기
}
