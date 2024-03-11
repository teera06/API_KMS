#include "IceBox.h"
#include "ActorCommon.h"

AIceBox::AIceBox()
{
}

AIceBox::~AIceBox()
{
}

void AIceBox::BeginPlay()
{
	AActor::BeginPlay();

	//scale = 5; // 평소 크기
	// 랜더링
	{
		Renderer = CreateImageRenderer(ERenderOrder::Object); // 이미지 랜더 생성
		Renderer->SetImage("Hammer.png"); // 이미지 Set
		//Renderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	// 콜리전
	{
		Collision = CreateCollision(ECollisionOrder::Object);
		Collision->SetTransform({ { -10,20},{100,100} });
		Collision->SetColType(ECollisionType::Rect);
	}
}

void AIceBox::Tick(float _DeltaTime)
{

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


