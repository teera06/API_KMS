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
		bulletRenderer = CreateImageRenderer(ERenderOrder::Ice); // 이미지 랜더 생성
		bulletRenderer->SetImage("Sir_Right.png"); // 이미지 Set
		bulletRenderer->SetTransform({ {0,0}, {64 * 3, 64 * 3} }); // 랜더의 위치 크기 
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
