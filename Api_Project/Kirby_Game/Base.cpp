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
		Renderer->SetImageToScale("Fire.png");
		Renderer->SetImageCuttingTransform({ {0,100}, {150, 100} });
	}

	Destroy(1.0f);
}
