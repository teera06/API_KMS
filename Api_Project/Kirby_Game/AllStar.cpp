#include "AllStar.h"
#include "ModeEnum.h"

AAllStar::AAllStar()
{
}

AAllStar::~AAllStar()
{
}

void AAllStar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(Dir * Speed * _DeltaTime);
}

void AAllStar::BeginPlay()
{
	AActor::BeginPlay();
	AllStarRenderer = CreateImageRenderer(RenderOrder::Base);
	AllStarRenderer->SetImage("kirby2_Right.png");
	AllStarRenderer->SetTransform({ {0,0}, {200, 200} });
	AllStarRenderer->SetActive(true, 0.2f);
	
	AllStarRenderer->CreateAnimation("AllAttack_Right", "kirby2_Right.png", 54, 57, 0.1f, true);
	
	AllStarRenderer->ChangeAnimation("AllAttack_Right");

	Destroy(1.0f);
}
