#include "Monster_Mike.h"

Monster_Mike::Monster_Mike()
{
}

Monster_Mike::~Monster_Mike()
{
}

void Monster_Mike::IceState()
{
	scale = 2;
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	IsIce = true;
}

void Monster_Mike::BeginPlay()
{
	AActor::BeginPlay();

	scale = 3; // 평소 크기
	// 랜더링
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("Dee_Right.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	// 콜리전
	{
		MonsterCollision = CreateCollision(ECollisionOrder::Monster);
		MonsterCollision->SetScale({ 60, 60 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	// 애니메이션 만들기
	AniCreate();

	MonsterRenderer->ChangeAnimation("Move_Left");

}

void Monster_Mike::Tick(float _DeltaTime)
{
}

void Monster_Mike::MoveUpdate(float _DeltaTime)
{
}

void Monster_Mike::BaseMove(float _DeltaTime)
{
}

void Monster_Mike::AniCreate()
{
}

void Monster_Mike::IceToMonster(float _DeltaTime)
{
}

void Monster_Mike::Collisiongather(float _DeltaTime)
{
}

void Monster_Mike::CalDir()
{
}

void Monster_Mike::CalResult(float _DeltaTime)
{
}

void Monster_Mike::GroundUp()
{
}
