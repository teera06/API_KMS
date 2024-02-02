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
	UImageRenderer* FireRenderer = CreateImageRenderer(8);
	FireRenderer->SetImage("Fire.png");
	SetActorLocation({ 0, 0 });
	FireRenderer->SetTransform({ {0,0}, {150, 150} });
	FireRenderer->SetImageCuttingTransform({ {0,0}, {100, 100} });
	//FireRenderer->CreateAnimation("Attack", "Player_Right.png", 26, 32, 0.1f, true); -> บา 

	
	Destroy(1.0f);
}
