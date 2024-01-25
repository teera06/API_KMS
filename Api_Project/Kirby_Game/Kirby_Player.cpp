#include "Kirby_Player.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>

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
	HDC WindowDC = GEngine->MainWindow.GetWindowDC();

	if (true == EngineInput::IsDown('A'))
	{
		AddActorLocation(FVector::Left);
	}

	if (true == EngineInput::IsDown('D'))
	{
		AddActorLocation(FVector::Right);
	}

	FTransform Trans = GetTransform();

	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}
