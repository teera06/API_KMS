#include "MainBoss.h"

AMainBoss::AMainBoss()
{
}

AMainBoss::~AMainBoss()
{
}

void AMainBoss::BeginPlay()
{
	AActor::BeginPlay();


	scale = 6;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("King_Left.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::MainBoss);
		MonsterCollision->SetTransform({ {0,-20}, {120, 120} });
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
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // 중력 작용

	skillcooldowntime -= _DeltaTime;
	
	
	CalDir(_DeltaTime);
	CalResult(_DeltaTime);
	
}

void AMainBoss::AniCreate()
{
	MonsterRenderer->CreateAnimation("Move_Right", "King_Right.png", 3,7, 0.3f, true);
	MonsterRenderer->CreateAnimation("Move_Left", "King_Left.png", 3,7, 0.3f, true);
	//MonsterRenderer->CreateAnimation("Att_Right", "King_Right.png", 21, 31, 0.5f, false);
	//MonsterRenderer->CreateAnimation("Att_Left", "King_Left.png", 21, 31, 0.5f, false);
	//MonsterRenderer->CreateAnimation("Att2_Right", "King_Right.png", { 32,33,34,35,34,33,32 }, 0.5f, false);
	//MonsterRenderer->CreateAnimation("Att2_Left", "King_Left.png", { 32,33,34,35,34,33,32 }, 0.5f, false);
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
		MonsterRenderer->ChangeAnimation("Att_Left");
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att_Right");
	}
	//AttCollisiongather(_DeltaTime);
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		//RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 2);
		//AttCollision->ActiveOff();
		IsAtt = false;
		skillcooldowntime = 4.0f;
	}

	return;
}

void AMainBoss::Att2()
{
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
