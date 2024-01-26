#include "Fire.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>

AFire::AFire()
{
}

AFire::~AFire()
{
}

void AFire::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);

	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform Trans = GetTransform();
	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}

void AFire::BeginPlay()
{
	// SetActorLocation({ 100, 100 });
	SetActorScale({ 50, 50 });
	Destroy(2.0f);
}
