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
		Renderer->SetImageToScale("test.png");
		Renderer->SetPosition(test*Dir);
		Renderer->SetScale({ 70, 70 });
	}

	Destroy(2.0f);
}
