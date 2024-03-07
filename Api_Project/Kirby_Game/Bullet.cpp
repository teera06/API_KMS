#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::BeginPlay()
{

	AActor::BeginPlay();
	{
		bulletRenderer = CreateImageRenderer(ERenderOrder::Ice); // �̹��� ���� ����
		bulletRenderer->SetImage("Sir_Right.png"); // �̹��� Set
		bulletRenderer->SetTransform({ {0,0}, {64 * 3, 64 * 3} }); // ������ ��ġ ũ�� 
	}
	{
		bulletCollision = CreateCollision(ECollisionOrder::SirAttack);
		bulletCollision->SetScale({ 100,70 });
		bulletCollision->SetColType(ECollisionType::CirCle);
		bulletCollision->SetActive(true, 0.3f);
	}

	AniCreate();
}

void Bullet::Tick(float _DeltaTime)
{
}

void Bullet::AniCreate()
{

}

void Bullet::SkillDir(float _DeltaTime)
{

}

void Bullet::Collisiongather(float _DeltaTime)
{

}
