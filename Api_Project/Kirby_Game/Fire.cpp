#include "Fire.h"
#include <Windows.h>

AFire::AFire()
{
}

AFire::~AFire()
{
}

void AFire::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(Dir*Speed*_DeltaTime);
}

void AFire::BeginPlay()
{
	AActor::BeginPlay();
	{
		UImageRenderer* Renderer = CreateImageRenderer(-10);
		Renderer->SetImageToScale("kirby.bmp");
	}
	
	Destroy(2.0f);
}
