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
	UImageRenderer* Renderer = CreateImageRenderer(-11);
	Renderer->SetImage("Fire.png");
	SetActorLocation({ 0, 0 });
	Renderer->SetTransform({ {0,0}, {100, 100} });
	Renderer->SetImageCuttingTransform({ {0,0}, {200, 200} });
	
	Destroy(2.0f);
}
