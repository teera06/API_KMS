#include "SubBoss.h"

ASubBoss::ASubBoss()
{
}

ASubBoss::~ASubBoss()
{
}

void ASubBoss::BeginPlay()
{
	AActor::BeginPlay();

	scale = 6;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("Tock_Right.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	{
		AttRenderer = CreateImageRenderer(ERenderOrder::Sound); // 이미지 랜더 생성
		AttRenderer->SetImage("Tock_Right.png"); // 이미지 Set
		AttRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 

		AttRenderer->ActiveOff();
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::SubBoss);
		MonsterCollision->SetTransform({ {0,-20}, {120, 120} });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	{
		AttCollision = CreateCollision(ECollisionOrder::SubBossAtt);
		AttCollision->SetTransform({ {0,-20}, {500, 120} });
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
	if (false == IsDie) // Destroy(0.3f); -> 조건없이 계속 move업데이트 되면서 0.3f도 똑같이 유지 (한번만 실행해야함)
	{
		MoveUpdate(_DeltaTime);
	}
	else { // IsDIe가 true이면 MoveUpdate는 연속 실행이 안됨 -> Destroy(0.3f) 작동
		//AddActorLocation(DiePos); // 죽으면서 이동
	}
}

void ASubBoss::CalDir(float _DeltaTime)
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector AttXL = MonsterPos + FVector::Left * AttRange; // 몬스터 왼쪽 플레이어 인식 시야 X축
	FVector AttXR = MonsterPos + FVector::Right * AttRange; // 몬스터 오른쪽 플레이어 인식 시야 X축

	FVector PlayerX = PlayerPos * FVector::Right; // 플레이어 위치 X축

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 

	MovePos = FVector::Zero; // 플레이어 추격 시 이동

	if (MonsterDirNormal.iX() == -1) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Move_Left");
		WallX = -20;
	}
	else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Move_Right");
		WallX = 20;
	}
	MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // 몬스터가 플레이어의 Y축도 인식할 수 있으니 FVector::Right 를 곱해 X축만 추격

	// 플레이어를 향해 공격
	if (AttXL.iX() < PlayerX.iX() && AttXR.iX() > PlayerX.iX() && MainPlayer->GetActorLocation().iY() >= GetActorLocation().iY() - 30) // 몬스터 시야에 포착된 경우 X축 기준 왼쪽, 오른쪽
	{
		IsAtt = true;
	}
}

void ASubBoss::Att()
{
	AttRenderer->ActiveOn();
	AttCollision->ActiveOn();
	AttRenderer->ChangeAnimation("AttEffect");

	if (MonsterDirNormal.iX() == -1 && IsIce == false) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att_Left");
	}
	else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att_Right");
	}
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		IsAtt = false;
		skillcooldowntime = 6.0f;
	}
}

void ASubBoss::Collisiongather(float _DeltaTime)
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

void ASubBoss::CalResult(float _DeltaTime)
{
	
	if (true == IsDie) // 죽으면
	{
		Destroy(0.3f); // 0.3f 뒤에 삭제
	}
	else {
		
		AddActorLocation(MovePos);
		
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
	if (true == IsAtt && skillcooldowntime < 0.0f)
	{
		MovePos = FVector::Zero;
		Att();
	}
	else {
		AttRenderer->ActiveOff();
		CalDir(_DeltaTime);
		Collisiongather(_DeltaTime);
		AttCollision->ActiveOff();
		CalResult(_DeltaTime);
	}
}

void ASubBoss::AniCreate()
{
	MonsterRenderer->CreateAnimation("Move_Right", "Tock_Right.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Move_Left", "Tock_Left.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Att_Right", "Tock_Right.png", 4, 6, 0.5f, false);
	MonsterRenderer->CreateAnimation("Att_Left", "Tock_Left.png", 4, 6, 0.5f, false);

	AttRenderer->CreateAnimation("AttEffect", "Tock_Right.png", { 16,17,18,19,20,14 },0.1f, true);


	MonsterRenderer->CreateAnimation("die_Right", "Tock_Left.png", 11, 13, 0.3f, true); // 죽음 
	MonsterRenderer->CreateAnimation("die_Left", "Tock_Right.png",11, 13, 0.3f, true); // 죽음 
	
	//MonsterRenderer->CreateAnimation("Effect", "Effects.png", 29, 30, 0.1f, true); // 죽는 애니메이션
}
