#include "Fire.h"
#include <Windows.h>
#include "ModeEnum.h"

AFire::AFire()
{
}

AFire::~AFire()
{
	//Destroy(0.0f);
}

void AFire::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(Dir*Speed*_DeltaTime);
}

void AFire::BeginPlay()
{
	AActor::BeginPlay();
	UImageRenderer* FireRenderer = CreateImageRenderer(RenderOrder::Base);
	FireRenderer->SetImage("Fire.png");
	FireRenderer->SetTransform({ {0,0}, {100, 100} });
	FireRenderer->SetActive(true, 0.3f);
	//FireRenderer->CreateAnimation("Attack", "Player_Right.png", 26, 32, 0.1f, true); -> บา 

	
	Destroy(1.0f);
}
