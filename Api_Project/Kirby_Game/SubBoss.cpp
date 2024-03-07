#include "SubBoss.h"

#include <EngineBase\EngineRandom.h>
#include <EngineCore/EngineCore.h> // GetWorld 사용 -> Level 정보 이용

#include "Monster_Mike.h"

ASubBoss* ASubBoss::MainSubBoss = nullptr;

ASubBoss* ASubBoss::GetMainSubBoss()
{
	return MainSubBoss;
}

ASubBoss::ASubBoss()
{
}

ASubBoss::~ASubBoss()
{
}

void ASubBoss::BeginPlay()
{
	AActor::BeginPlay();

	MainSubBoss = this; // 다른 클래스가 사용하기 위해 본인을 넣는다.
	scale = 6;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("Tock_Right.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	{
		AttRenderer = CreateImageRenderer(ERenderOrder::Sound); // 이미지 랜더 생성
		AttRenderer->SetImage("Tock_Right.png"); // 이미지 Set
		AttRenderer->SetTransform({ {0,0}, {64 * 12, 64 * 12} }); // 랜더의 위치 크기 

		AttRenderer->ActiveOff();
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::SubBoss);
		MonsterCollision->SetTransform({ {0,-20}, {120, 120} });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	{
		AttCollision = CreateCollision(ECollisionOrder::SubBossAtt);
		AttCollision->SetTransform({ {0,-100}, {800, 500} });
		AttCollision->SetColType(ECollisionType::Rect);
		AttCollision->ActiveOff();
	}

	AniCreate();
	MonsterRenderer->ChangeAnimation("Move_Left");
}

void ASubBoss::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();

	if (Hp == 0) // 죽으면
	{
		MonsterRenderer->ChangeAnimation("die_Right");

		if (true == MonsterRenderer->IsCurAnimationEnd())
		{
			Destroy(); // 0.3f 뒤에 삭제
		}
	}
	else {
		if (false == Ishit) // Destroy(0.3f); -> 조건없이 계속 move업데이트 되면서 0.3f도 똑같이 유지 (한번만 실행해야함)
		{
			MoveUpdate(_DeltaTime);
		}
		else { 
			hitEvent();
		}
	}
}

void ASubBoss::CalDir(float _DeltaTime)
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 

	MovePos = FVector::Zero; // 플레이어 추격 시 이동

	if (MonsterDirNormal.iX() == -1 or MonsterDirNormal.iX() == 0) // 왼쪽 방향
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

void ASubBoss::Att1(float _DeltaTime)
{
	AttRenderer->ActiveOn();
	AttCollision->ActiveOn();
	AttRenderer->ChangeAnimation("AttEffect");

	if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att_Left");
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att_Right");
	}
	AttCollisiongather(_DeltaTime);
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 2);
		AttCollision->ActiveOff();
		IsAtt = false;
		skillcooldowntime = 4.0f;
	}

	return;
}

void ASubBoss::Att2()
{
	if (MonsterDirNormal.iX() == -1) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att2_Left");
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att2_Right");
	}
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 2);
		if (MonsterDirNormal.iX() == -1) // 왼쪽 방향
		{
			GetWorld()->SpawnActor<AMonster_Mike>()->SetActorLocation({ GetActorLocation().iX()-100,200 });
		}
		else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
			GetWorld()->SpawnActor<AMonster_Mike>()->SetActorLocation({ GetActorLocation().iX()+100,200 });
		}
		IsAtt = false;
		skillcooldowntime = 4.0f;
	}
	return;
}

void ASubBoss::AttCollisiongather(float _DeltaTime)
{
	// 콜리전 
	std::vector<UCollision*> Result;
	if (true == AttCollision->CollisionCheck(ECollisionOrder::kirby, Result)) // 얼지 않은 상태에서 플레이어와 충돌
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		// 방어코드
		if (nullptr == Player)
		{
			MsgBoxAssert("몬스터베이스 플레이어 인식 못함");
		}

	
		Player->Sethitstate(true); // 플레이어 충돌 체크
		Player->SetHitDir(MonsterDirNormal * FVector::Right);
		Player->GetKirbyRender()->SetAlpha(0.5f);
		Player->GetKirbyCollision()->ActiveOff();
		Player->AddHP(-20);
		Player->HitStart(); // hit 상태 스타트
			
		//IsDie = true; // 죽음 체크
		
	}
}

void ASubBoss::Collisiongather(float _DeltaTime)
{
	// 콜리전 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result)) // 얼지 않은 상태에서 플레이어와 충돌
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		// 방어코드
		if (nullptr == Player)
		{
			MsgBoxAssert("몬스터베이스 플레이어 인식 못함");
		}


		Player->Sethitstate(true); // 플레이어 충돌 체크
		Player->SetHitDir(MonsterDirNormal * FVector::Right);
		Player->GetKirbyRender()->SetAlpha(0.5f);
		Player->GetKirbyCollision()->ActiveOff();
		Player->AddHP(-20);
		Player->HitStart(); // hit 상태 스타트

		//IsDie = true; // 죽음 체크

	}
}

void ASubBoss::CalResult(float _DeltaTime)
{
	AddActorLocation(MovePos);
}

void ASubBoss::hitEvent()
{
	if (MonsterDirNormal.iX() == -1) // 몬스터가 플레이어를 향하는 방향의 반대 방향으로 힘이 작용
	{
		MonsterRenderer->ChangeAnimation("hit_Left"); // 죽는 애니메이션
	}
	else {
		MonsterRenderer->ChangeAnimation("hit_Right"); // 죽는 애니메이션
	}

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		Ishit = false; 
		MonsterRenderer->SetAlpha(1.0f);
	}
}

void ASubBoss::GroundUp()
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

void ASubBoss::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // 중력 작용

	skillcooldowntime -= _DeltaTime;
	if (skillcooldowntime < 0.0f)
	{

		MovePos = FVector::Zero;

		if (RandomAtt == 1)
		{
			Att1(_DeltaTime);
		}
		
		if (RandomAtt == 2 or RandomAtt == 0)
		{
			Att2();
		}
	}
	else {
		AttRenderer->ActiveOff();
		CalDir(_DeltaTime);
		Collisiongather(_DeltaTime);
		CalResult(_DeltaTime);
	}
}

void ASubBoss::AniCreate()
{
	MonsterRenderer->CreateAnimation("Move_Right", "Tock_Right.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Move_Left", "Tock_Left.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Att_Right", "Tock_Right.png", 4, 6, 0.5f, false);
	MonsterRenderer->CreateAnimation("Att_Left", "Tock_Left.png", 4, 6, 0.5f, false);
	MonsterRenderer->CreateAnimation("Att2_Right", "Tock_Right.png", {4, 5, 10}, 0.5f, false);
	MonsterRenderer->CreateAnimation("Att2_Left", "Tock_Left.png", {4,5,10}, 0.5f, false);

	AttRenderer->CreateAnimation("AttEffect", "Tock_Right.png", { 16,17,18,19,20,14 },0.1f, true);

	MonsterRenderer->CreateAnimation("hit_Right", "Tock_Right.png", {10,1}, 0.5f, true); // 히트
	MonsterRenderer->CreateAnimation("hit_Left", "Tock_Left.png", {10,1}, 0.5f, true); // 히트 
	MonsterRenderer->CreateAnimation("die_Right", "Tock_Left.png", {11,13,12}, 0.5f, true); // 죽음 
	MonsterRenderer->CreateAnimation("die_Left", "Tock_Right.png",{11, 13, 12}, 0.5f, true); // 죽음 
}
