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
		Renderer->SetTransform({ {0,0}, {100, 100} });
		Renderer->SetImageCuttingTransform({ {100,0}, {100, 100} }); // {X,Y}-> �׸� ����  {X,Y} -> ����ŭ �׷���
	}

	Destroy(1.0f);
}
