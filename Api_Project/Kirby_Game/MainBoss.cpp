#include "MainBoss.h"

AMainBoss::AMainBoss()
{
}

AMainBoss::~AMainBoss()
{
}

void AMainBoss::BeginPlay()
{
	AActor::BeginPlay();


	scale = 6;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("Tock_Right.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::MainBoss);
		MonsterCollision->SetTransform({ {0,-20}, {120, 120} });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}
}

void AMainBoss::Tick(float _DeltaTime)
{
}

void AMainBoss::MoveUpdate(float _DeltaTime)
{
}

void AMainBoss::AniCreate()
{
	MonsterRenderer->CreateAnimation("Move_Right", "King_Right.png", 3, 7, 0.3f, true);
	MonsterRenderer->CreateAnimation("Move_Left", "King_Left.png", 3,7, 0.3f, true);
	MonsterRenderer->CreateAnimation("Att_Right", "King_Right.png", 21, 31, 0.5f, false);
	MonsterRenderer->CreateAnimation("Att_Left", "King_Left.png", 21, 31, 0.5f, false);
	MonsterRenderer->CreateAnimation("Att2_Right", "King_Right.png", { 32,33,34,35,34,33,32 }, 0.5f, false);
	MonsterRenderer->CreateAnimation("Att2_Left", "King_Left.png", { 32,33,34,35,34,33,32 }, 0.5f, false);
}

void AMainBoss::CalDir(float _DeltaTime)
{
}

void AMainBoss::GroundUp()
{
}
