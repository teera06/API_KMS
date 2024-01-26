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
	AddActorLocation(Dir*Speed*_DeltaTime);

	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform Trans = GetTransform();
	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}

void AFire::BeginPlay()
{
	{
		UImageRenderer* Renderer = CreateImageRenderer(0);
		Renderer->SetPosition({ 0,0 });
		Renderer->SetScale({ 10, 50 });
	}

	{
		UImageRenderer* Renderer = CreateImageRenderer(0);
		Renderer->SetPosition({ 0,0 });
		Renderer->SetScale({ 50, 10 });
	}

	Destroy(2.0f);
}
