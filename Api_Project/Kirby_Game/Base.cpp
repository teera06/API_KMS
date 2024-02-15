#include "Base.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include "ModeEnum.h"

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
		//Renderer->SetImage("Fire.png");
		//Renderer->SetTransform({ {0,0}, {100, 100} });
	}

	{
		BaseCollision = CreateCollision(ECollisionOrder::AllStar);
		BaseCollision->SetTransform({ { 100,0 }, { 80,80 } });
		BaseCollision->SetColType(ECollisionType::Rect);
	}

	Destroy(1.0f);
}
