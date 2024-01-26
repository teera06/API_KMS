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

	if (true == EngineInput::IsPress(VK_LEFT)) // ���� �ȱ�
	{
		AddActorLocation(FVector::Left * WalkSpeed * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_LEFT) && true == EngineInput::IsPress(VK_SHIFT)) // ���� �ٱ�
	{
		AddActorLocation(FVector::Left * RunSpeed * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_RIGHT)) // ������ �ȱ�
	{
		AddActorLocation(FVector::Right * WalkSpeed * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_RIGHT) && true == EngineInput::IsPress(VK_SHIFT)) // ������ �ٱ�
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

	HDC WindowDC = GEngine->MainWindow.GetWindowDC(); // ������ �׸���

	

	FTransform Trans = GetTransform(); // ��ġ, ũ�� �� �޾ƿ���

	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom()); // �� ������ �°� �׷��ֱ�
}
