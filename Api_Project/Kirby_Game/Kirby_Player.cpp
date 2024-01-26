#include "Kirby_Player.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineTime.h>

#include "Fire.h"
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

	if (true == EngineInput::IsPress(VK_LEFT)) // 왼쪽 걷기
	{
		AddActorLocation(FVector::Left * WalkSpeed * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_LEFT) && true == EngineInput::IsPress(VK_SHIFT)) // 왼쪽 뛰기
	{
		AddActorLocation(FVector::Left * RunSpeed * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_RIGHT)) // 오른쪽 걷기
	{
		AddActorLocation(FVector::Right * WalkSpeed * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_RIGHT) && true == EngineInput::IsPress(VK_SHIFT)) // 오른쪽 뛰기
	{
		AddActorLocation(FVector::Right * RunSpeed * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_UP))
	{
		AddActorLocation(FVector::Up * WalkSpeed * _DeltaTime);
	}


	if (true == EngineInput::IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * WalkSpeed * _DeltaTime);
	}

	


	if (true == EngineInput::IsDown('Q'))
	{
		AFire* NewFire = GetWorld()->SpawnActor<AFire>();
		NewFire->SetActorLocation(GetActorLocation());
		NewFire->SetDir(FVector::Right);
	}

	HDC WindowDC = GEngine->MainWindow.GetWindowDC(); // 윈도우 그리기

	

	FTransform Trans = GetTransform(); // 위치, 크기 값 받아오고

	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom()); // 그 정보에 맞게 그려주기
}
