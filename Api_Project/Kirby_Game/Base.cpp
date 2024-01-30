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
	
}

void ABase::BeginPlay()
{
	{
		UImageRenderer* Renderer = CreateImageRenderer(-10);
		Renderer->SetImageToScale("kirby.bmp");
	}

	Destroy(2.0f);
}
