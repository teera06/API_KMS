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
		UImageRenderer* Renderer = CreateImageRenderer(9);
		Renderer->SetImage("Fire.png");
		Renderer->SetTransform({ {0,0}, {100, 100} });
	}

	Destroy(1.0f);
}
