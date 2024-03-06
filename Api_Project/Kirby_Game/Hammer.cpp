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
		Renderer = CreateImageRenderer(ERenderOrder::Hammer); // 이미지 랜더 생성
		Renderer->SetImage("Hammer.png"); // 이미지 Set
		Renderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	// 콜리전
	{
		Collision = CreateCollision(ECollisionOrder::Hammer);
		Collision->SetScale({ 60, 60 });
		Collision->SetColType(ECollisionType::Rect);
	}
}

void AHammer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY()+50, _DeltaTime)); // 중력 작용
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
