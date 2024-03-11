#include "Hammer.h"

AHammer::AHammer()
{
}

AHammer::~AHammer()
{
}

void AHammer::BeginPlay()
{
	AActor::BeginPlay();

	scale = 5; // 평소 크기
	// 랜더링
	{
		Renderer = CreateImageRenderer(ERenderOrder::Object); // 이미지 랜더 생성
		Renderer->SetImage("Hammer.png"); // 이미지 Set
		Renderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	// 콜리전
	{
		Collision = CreateCollision(ECollisionOrder::Hammer);
		Collision->SetTransform({ { -10,20},{100,100} });
		Collision->SetColType(ECollisionType::Rect);
	}
}

void AHammer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY()+80, _DeltaTime)); // 중력 작용
	Collisiongather();
	GroundUp();
}

void AHammer::GroundUp()
{
	while (true)
	{
		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 1, Color8Bit::RedA);
		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			AddActorLocation(FVector::Up * 2);
		}
		else
		{
			break;
		}
	}
}

void AHammer::Collisiongather()
{
	// 콜리전 
	std::vector<UCollision*> Result;
	if (true == Collision->CollisionCheck(ECollisionOrder::kirby, Result)) // 얼지 않은 상태에서 플레이어와 충돌
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);

		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		// 방어코드
		if (nullptr == Player)
		{
			MsgBoxAssert("몬스터베이스 플레이어 인식 못함");
		}

		if (true == GetBaseOnOff()) // 흡수할 때의 몬스터 충돌 -> 몬스터는 플레이어와 충돌할 경우 바로 죽음
		{
			Destroy();
		}
	}
}
