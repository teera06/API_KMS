#include "MainBoss.h"

#include <EngineBase\EngineRandom.h>


#include "Bullet.h"

AMainBoss::AMainBoss()
{
}

AMainBoss::~AMainBoss()
{
}

AMainBoss* AMainBoss::GetMainBoss()
{
	return MainBoss;
}

AMainBoss* AMainBoss::MainBoss = nullptr;

void AMainBoss::BeginPlay()
{
	AActor::BeginPlay();

	MainBoss = this;

	scale = 6;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("King_Left.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::MainBoss);
		MonsterCollision->SetTransform({ {0,-20}, {10, 10} });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	AniCreate();
	MonsterRenderer->ChangeAnimation("Move_Left");
}

void AMainBoss::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();

	MoveUpdate(_DeltaTime);
}

void AMainBoss::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY()+90, _DeltaTime)); // 중력 작용

	skillcooldowntime -= _DeltaTime;

	if (skillcooldowntime < 0.0f)
	{

		MovePos = FVector::Zero;

		if (RandomAtt == 0 || RandomAtt == 1)
		{
			Att1();
		}

		if (RandomAtt == 2 || RandomAtt == 3 || RandomAtt == 4)
		{
			Att2();
		}

		if (RandomAtt == 5 )
		{
			Att3();
		}
	}
	else {

		if (true == Att3Delay)
		{
			if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
			{
				MonsterRenderer->ChangeAnimation("Delay3_Left");
			}
			else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
				MonsterRenderer->ChangeAnimation("Delay3_Right");
			}

			if (true == MonsterRenderer->IsCurAnimationEnd())
			{
				Att3Delay = false;;
			}
		}else if (true == Att2Delay)
		{
			if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
			{
				MonsterRenderer->ChangeAnimation("Delay2_Left");
			}
			else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
				MonsterRenderer->ChangeAnimation("Delay2_Right");
			}

			if (true == MonsterRenderer->IsCurAnimationEnd())
			{
				Att2Delay = false;;
			}
		}
		else {
			CalDir(_DeltaTime);
			CalResult(_DeltaTime);
		}
	}
}

void AMainBoss::AniCreate()
{
	MonsterRenderer->CreateAnimation("Move_Right", "King_Right.png", 3, 7, 0.3f, true);
	MonsterRenderer->CreateAnimation("Move_Left", "King_Left.png", 3, 7, 0.3f, true);
	MonsterRenderer->CreateAnimation("Att1_Right", "King_Right.png", { 26,29,30,31,32 }, 0.2f, false);
	MonsterRenderer->CreateAnimation("Att1_Left", "King_Left.png", { 26,29,30,31,32 }, 0.2f, false);
	MonsterRenderer->CreateAnimation("Att2_Right", "King_Right.png", 32, 35, 0.3f, false);
	MonsterRenderer->CreateAnimation("Att2_Left", "King_Left.png", 32, 35, 0.3f, false);

	MonsterRenderer->CreateAnimation("Delay2_Right", "King_Right.png", {35,34,33,32}, 0.3f, false);
	MonsterRenderer->CreateAnimation("Delay2_Left", "King_Left.png", { 35,34,33,32 }, 0.3f, false);


	MonsterRenderer->CreateAnimation("Att3_Right", "King_Right.png", { 37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53 }, 0.05f, false);
	MonsterRenderer->CreateAnimation("Att3_Left", "King_Left.png", { 37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53 }, 0.05f, false);

	MonsterRenderer->CreateAnimation("Delay3_Right", "King_Right.png", 54, 60,0.5f, false);
	MonsterRenderer->CreateAnimation("Delay3_Left", "King_Left.png", 54, 60,0.5f, false);
}

void AMainBoss::CalDir(float _DeltaTime)
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 

	MovePos = FVector::Zero; // 플레이어 추격 시 이동

	if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Move_Left");
		WallX = -20;
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Move_Right");
		WallX = 20;
	}
	MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // 몬스터가 플레이어의 Y축도 인식할 수 있으니 FVector::Right 를 곱해 X축만 추격
}

void AMainBoss::Att1()
{
	//AttRenderer->ActiveOn();
	//AttCollision->ActiveOn();
	//AttRenderer->ChangeAnimation("AttEffect");

	if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att1_Left");
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att1_Right");
	}
	//AttCollisiongather(_DeltaTime);
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 5);
		//AttCollision->ActiveOff();
		IsAtt = false;
		skillcooldowntime = 4.0f;
	}

	return;
}

void AMainBoss::Att2()
{
	ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
	
	if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att2_Left");
		NewBullet->SetDir(FVector::Left);
	}
	else if (MonsterDirNormal.iX() == 1 || MonsterDirNormal.iX() == 0) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att2_Right");
		NewBullet->SetDir(FVector::Right);
	}
	//AttCollisiongather(_DeltaTime);
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		NewBullet->SetActorLocation(this->GetActorLocation());
		RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 5);
		//AttCollision->ActiveOff();
		IsAtt = false;
		skillcooldowntime = 4.0f;
		Att2Delay = true;
	}

	return;
}

void AMainBoss::Att3()
{
	if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att3_Left");
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att3_Right");
	}
	//AttCollisiongather(_DeltaTime);
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 5);
		IsAtt = false;
		skillcooldowntime = 4.0f;
		Att3Delay = true;
		//AttCollision->ActiveOff();
	}
	return;
}

void AMainBoss::CalResult(float _DeltaTime)
{
	AddActorLocation(MovePos);
}

void AMainBoss::GroundUp()
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
