#include "IceBox.h"

AIceBox::AIceBox()
{
}

AIceBox::~AIceBox()
{
}

void AIceBox::BeginPlay()
{
	AActor::BeginPlay();

	scale = 5; // 평소 크기
	// 랜더링
	{
		Renderer = CreateImageRenderer(ERenderOrder::Object); // 이미지 랜더 생성
		Renderer->SetImage("item.png"); // 이미지 Set
		Renderer->SetTransform({ {0,-40}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	// 콜리전
	{
		Collision = CreateCollision(ECollisionOrder::IceBox);
		Collision->SetTransform({ { 0,-35},{140,140} });
		Collision->SetColType(ECollisionType::Rect);
	}

	Renderer->CreateAnimation("IceBox", "item.png", 1, 1, true);
	Renderer->ChangeAnimation("IceBox");
}

void AIceBox::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	// 콜리전 
	
	GravityVector += GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime); // 중력은 계속 가해진다.

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	std::vector<UCollision*> Result;
	if (ColorR == Color8Bit(255, 0, 0, 0) || true == Collision->CollisionCheck(ECollisionOrder::IceBox, Result)) // ColMapImage에서 빨간색과 일치하는 경우
	{
		GravityVector = FVector::Zero; // 중력의 힘은 0으로
	}

	AddActorLocation(GravityVector);

	
	GroundUp();
}

void AIceBox::GroundUp()
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


