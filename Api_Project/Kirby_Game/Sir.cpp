#include "Sir.h"

ASir::ASir()
{
}

ASir::~ASir()
{
}

void ASir::Tick(float _DeltaTime)
{
}

void ASir::BeginPlay()
{
	AActor::BeginPlay();
	{
		SirRenderer = CreateImageRenderer(ERenderOrder::Ice); // 이미지 랜더 생성
		SirRenderer->SetImage("Sir_Right.png"); // 이미지 Set
		SirRenderer->SetTransform({ {0,0}, {64 * 3, 64 * 3} }); // 랜더의 위치 크기 
	}
	{
		SirCollision = CreateCollision(ECollisionOrder::SirAttack);
		SirCollision->SetScale({ 100,70 });
		SirCollision->SetColType(ECollisionType::CirCle);
	}

	AniCreate();

	Destroy(0.5f);
}

void ASir::AniCreate()
{
	SirRenderer->CreateAnimation("Sir_Right", "Sir_Right.png", 95,98, 0.05f, true);
	SirRenderer->CreateAnimation("Sir_Left", "Sir_Left.png", 95,98, 0.05f, true);
	SirRenderer->ChangeAnimation("Sir_Right");
}

void ASir::SkillDir()
{
	if (GetDir().iX() == FVector::Left.iX())
	{
		SirRenderer->ChangeAnimation("Ice_Right");
	}
	else
	{
		SirRenderer->ChangeAnimation("Ice_Left");
	}

	SirCollision->SetPosition({ GetDir().iX() * 120,0 });
	SirRenderer->SetPosition({ GetDir().iX() * 125,-5 });
}

void ASir::Collisiongather(float _DeltaTime)
{

}
