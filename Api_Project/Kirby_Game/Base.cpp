#include "Base.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>

ABase::ABase()
{
}

ABase::~ABase()
{
}

void ABase::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void ABase::BeginPlay()
{
	AActor::BeginPlay();
	{
		UImageRenderer* Renderer = CreateImageRenderer(-10);
		Renderer->SetImage("Fire.png");
		SetActorLocation({ 0, 0 });
		Renderer->SetTransform({ {0,0}, {100, 100} });
		Renderer->SetImageCuttingTransform({ {0,0}, {200, 200} });
	}

	Destroy(1.0f);
}
