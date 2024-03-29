#include "Box.h"

ABox::ABox()
{
}

ABox::~ABox()
{
}

void ABox::BeginPlay()
{
	AActor::BeginPlay();

	scale = 3; // 평소 크기
	// 랜더링
	{
		Renderer = CreateImageRenderer(ERenderOrder::Object); // 이미지 랜더 생성
		Renderer->SetImage("item.png"); // 이미지 Set
		Renderer->SetTransform({ {0,-20}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
		hitRenderer = CreateImageRenderer(ERenderOrder::effect); // 이미지 랜더 생성
		hitRenderer->SetImage("Effects2_Right.png"); // 이미지 Set
		hitRenderer->SetTransform({ {0,-20}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 

		hitRenderer->CreateAnimation("Effect", "Effects2_Right.png", {27,26,25},0.1f, true);
		hitRenderer->ActiveOff();
	}

	// 콜리전
	{
		CollisionTop = CreateCollision(ECollisionOrder::BoxTop);
		CollisionTop->SetTransform({ { 0,-50},{90,20} });
		CollisionTop->SetColType(ECollisionType::Rect);

		CollisionBody = CreateCollision(ECollisionOrder::Box);
		CollisionBody->SetTransform({ { 0,-5},{100,70} });
		CollisionBody->SetColType(ECollisionType::Rect);

		CollisionItem = CreateCollision(ECollisionOrder::Item);
		CollisionItem->SetTransform({ { 0,0},{50,50} });
		CollisionItem->SetColType(ECollisionType::Rect);

		CollisionItem->ActiveOff();
	}

	Renderer->CreateAnimation("Box", "item.png", 2, 2, true);
	Renderer->CreateAnimation("Item", "item.png", 0, 0, true);
	Renderer->ChangeAnimation("Box");
}

void ABox::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	// 콜리전 

	if (true == IsItem && true == IsDelete)
	{
		ItemDrop();
		if (true == hitRenderer->IsCurAnimationEnd())
		{
			hitRenderer->ActiveOff();
		}
	}
	else if (false == IsItem && true == IsDelete)
	{
		Destroy();
	}

	if (true == CollisionItem->IsActive())
	{
		ItemCollisiongather();
	}

	Collisiongather(_DeltaTime);


	GroundUp();
}

void ABox::GroundUp()
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

void ABox::Collisiongather(float _DeltaTime)
{
	GravityVector += GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime); // 중력은 계속 가해진다.

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	std::vector<UCollision*> Result;
	if (ColorR == Color8Bit(255, 0, 0, 0) || true == CollisionBody->CollisionCheck(ECollisionOrder::BoxTop, Result, GravityVector) 
		|| true == CollisionItem->CollisionCheck(ECollisionOrder::BoxTop, Result, GravityVector*10.0f)) // ColMapImage에서 빨간색과 일치하는 경우
	{
		GravityVector = FVector::Zero; // 중력의 힘은 0으로
	}

	AddActorLocation(GravityVector);
}

void ABox::ItemCollisiongather()
{
	std::vector<UCollision*> Result;
	if (true == CollisionItem->CollisionCheck(ECollisionOrder::kirby, Result, GravityVector)) // ColMapImage에서 빨간색과 일치하는 경우
	{
		UEngineSound::SoundPlay("HpEat.wav");
		MainPlayer->SetHp(100);
		Destroy();
	}
}

void ABox::ItemDrop()
{
	hitRenderer->ActiveOn();
	hitRenderer->ChangeAnimation("Effect");
	scale = 2;
	Renderer->ChangeAnimation("Item");
	Renderer->SetTransform({ {0,10}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 

	CollisionTop->ActiveOff();
	CollisionBody->ActiveOff();
	CollisionItem->ActiveOn();
}
