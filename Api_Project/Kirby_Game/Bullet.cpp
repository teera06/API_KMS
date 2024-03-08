#include "Bullet.h"

ABullet::ABullet()
{
}

ABullet::~ABullet()
{
}

void ABullet::BeginPlay()
{

	AActor::BeginPlay();
	{
		bulletRenderer = CreateImageRenderer(ERenderOrder::Bullet); // 이미지 랜더 생성
		bulletRenderer->SetImage("King_Right.png"); // 이미지 Set
		bulletRenderer->SetTransform({ {0,14}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
		bulletRenderer -> SetActive(true, 0.2f);
	}
	{
		bulletCollision = CreateCollision(ECollisionOrder::MainBossAtt);
		bulletCollision->SetTransform({ {0,20},{100,100} });
		bulletCollision->SetColType(ECollisionType::CirCle);
		bulletCollision->SetActive(true, 0.1f);
	}

	AniCreate();
}

void ABullet::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
	SkillDir(_DeltaTime);
	Collisiongather(_DeltaTime);
}

void ABullet::AniCreate()
{
	bulletRenderer->CreateAnimation("Bullet_Right", "king_Right.png", 61, 66, 0.05f, false);
	bulletRenderer->CreateAnimation("Bullet_Left", "King_Left.png", 61, 66, 0.05f, false);
	bulletRenderer->CreateAnimation("hit_Right", "king_Right.png", 67, 72, 0.1f, false);
	bulletRenderer->CreateAnimation("hit_Left", "king_Left.png", 67, 72, 0.1f, false);
}

void ABullet::SkillDir(float _DeltaTime)
{

	if (true == hit)
	{
		bulletRenderer->SetTransform({ {0,14}, {64 * 12, 64 * 12} }); // 랜더의 위치 크기 
		if (GetDir().iX() == FVector::Left.iX()) // 왼쪽 방향
		{
			bulletRenderer->ChangeAnimation("hit_Left");
		}
		else // 오른쪽 방향
		{
			bulletRenderer->ChangeAnimation("hit_Right");
		}
		AddActorLocation(FVector::Zero);

		if (true == bulletRenderer->IsCurAnimationEnd())
		{
			Destroy();
		}
		return;
	}
	
	if (GetDir().iX() == FVector::Left.iX()) // 왼쪽 방향
	{
		bulletRenderer->ChangeAnimation("Bullet_Left");
		AddActorLocation(GetDir() * Speed * _DeltaTime);
	}
	else // 오른쪽 방향
	{
		bulletRenderer->ChangeAnimation("Bullet_Right");
		AddActorLocation(GetDir() * Speed * _DeltaTime);
	}
}

void ABullet::Collisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == bulletCollision->CollisionCheck(ECollisionOrder::kirby, Result))
	{
		MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
		MainPlayer->Sethitstate(true); // 플레이어 충돌 체크
		MainPlayer->SetHitDir(GetDir());
		MainPlayer->GetKirbyCollision()->ActiveOff();
		MainPlayer->AddHP(-20);
		hit = true;
		bulletCollision->ActiveOff();
		MainPlayer->hothitStart();
		
	}
	
	// 픽셀 충돌
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 20, Color8Bit::RedA);

	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		hit = true;
		bulletCollision->ActiveOff();
	}
}
