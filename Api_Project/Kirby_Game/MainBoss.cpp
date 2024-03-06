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
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		MonsterRenderer->SetImage("Tock_Right.png"); // �̹��� Set
		MonsterRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
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
}

void AMainBoss::CalDir(float _DeltaTime)
{
}

void AMainBoss::GroundUp()
{
}
