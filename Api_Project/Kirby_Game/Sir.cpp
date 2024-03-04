#include "Sir.h"

ASir::ASir()
{
}

ASir::~ASir()
{
}

void ASir::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	SkillDir(_DeltaTime);


	//Collisiongather(_DeltaTime);


	//SirRenderer->Destroy(0.1f);
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
	//Destroy(0.5f);
}

void ASir::AniCreate()
{
	SirRenderer->CreateAnimation("Sir_Right", "Sir_Right.png", 95,98, 0.05f, true);
	SirRenderer->CreateAnimation("Sir_Left", "Sir_Left.png", 95,98, 0.05f, true);
	SirRenderer->ChangeAnimation("Sir_Right");
}

void ASir::SkillDir(float _DeltaTime)
{
	FVector Move = FVector::Zero;
	FVector CurX = GetActorLocation() * FVector::Right;
	FVector RangeXL = StartPos + (FVector::Left * RangeX);
	FVector RangeXR = StartPos + (FVector::Right * RangeX);
	//StartDir = GetDir();
	if (GetDir().iX() == FVector::Left.iX())
	{
		SirRenderer->ChangeAnimation("Sir_Right");
	}
	else
	{
		SirRenderer->ChangeAnimation("Sir_Left");
	}

	//if (RangeXL.iX() >= CurX.iX() || RangeXR.iX() <= CurX.iX()) // 기본 몬스터 이동 방향 좌우 +-100 그 범위 벗어나는 경우 -> 방향 변환
	if (RangeXR.iX() <= CurX.iX() && StartDir.iX() == 1) // 기본 몬스터 이동 방향 좌우 +-100 그 범위 벗어나는 경우 -> 방향 변환
	{
		StartDir = StartDir * FVector::Left;
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 800.0f); // 해당 범위 벗어나야 아래의 else문을 실행할 수 있기에 다시 범위안으로 옮기고 리턴
		return;
	}
	
	AddActorLocation(StartDir * 500.0f * _DeltaTime);
	

	//AddActorLocation(GetDir() * 500.0f * _DeltaTime);

	//SirCollision->SetPosition({ GetDir().iX() * 120,0 });
	//SirRenderer->SetPosition({ GetDir().iX() * 125,-5 });
}

void ASir::Collisiongather(float _DeltaTime)
{

}
