#include "Bullet.h"

ABullet::ABullet()
{
}

ABullet::~ABullet()
{
}

void ABullet::BeginPlay()
{

	AActor::BeginPlay();
	{
		bulletRenderer = CreateImageRenderer(ERenderOrder::Bullet); // �̹��� ���� ����
		bulletRenderer->SetImage("King_Right.png"); // �̹��� Set
		bulletRenderer->SetTransform({ {0,0}, {64 * 3, 64 * 3} }); // ������ ��ġ ũ�� 
	}
	{
		bulletCollision = CreateCollision(ECollisionOrder::MainBossAtt);
		bulletCollision->SetScale({ 100,70 });
		bulletCollision->SetColType(ECollisionType::CirCle);
		bulletCollision->SetActive(true, 0.3f);
	}

	AniCreate();
}

void ABullet::Tick(float _DeltaTime)
{
}

void ABullet::AniCreate()
{
	bulletRenderer->CreateAnimation("Move_Right", "king_Right.png", 7, 9, 0.3f, true);
	bulletRenderer->CreateAnimation("Move_Left", "King_Left.png", 7, 9, 0.3f, true);
}

void ABullet::SkillDir(float _DeltaTime)
{

}

void ABullet::Collisiongather(float _DeltaTime)
{

}
