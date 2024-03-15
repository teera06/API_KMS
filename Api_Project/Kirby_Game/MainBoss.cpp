#include "MainBoss.h"

#include <EngineBase\EngineRandom.h>

#include "Bullet.h"
#include "Ice.h"

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
		Att2Renderer = CreateImageRenderer(ERenderOrder::effect); // 이미지 랜더 생성
		Att2Renderer->SetImage("King_Left.png"); // 이미지 Set
		Att2Renderer->ActiveOff();
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::MainBoss);
		MonsterCollision->SetTransform({ {0,50}, {70, 150} });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	{
		Att1Collision = CreateCollision(ECollisionOrder::MainBossAtt);
		Att1Collision->SetColType(ECollisionType::Rect);
		Att1Collision->ActiveOff();
	}

	{
		Att3Collision = CreateCollision(ECollisionOrder::MainBossAtt);
		Att3Collision->SetTransform({ {0,50}, {350, 350} });
		Att3Collision->SetColType(ECollisionType::CirCle);
		Att3Collision->ActiveOff();
	}


	AniCreate();
	MonsterRenderer->ChangeAnimation("Move_Left");
}

void AMainBoss::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();

	if (Hp <= 0) // 죽으면
	{
		MonsterRenderer->ChangeAnimation("die_Right");

		if (true == MonsterRenderer->IsCurAnimationEnd())
		{
			MonsterCollision->ActiveOff();
			EndingChange = true;
		}
	}
	else 
	{
		if (false == Ishit) // Destroy(0.3f); -> 조건없이 계속 move업데이트 되면서 0.3f도 똑같이 유지 (한번만 실행해야함)
		{
			MoveUpdate(_DeltaTime);
		}
		else {
			hitEvent();
		}
	}
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
			Att1(_DeltaTime);
		}

		if (RandomAtt == 2 )
		{
			Att2(); // 중간 끊김 현상
		}

		if (RandomAtt == 3)
		{
			Att3(_DeltaTime);
			if (false == Att3Sound && skillcooldowntime < 0.0f)
			{
				UEngineSound::SoundPlay("HammerSpin.wav");
				Att3Sound = true;
			}
		}

		if (RandomAtt == 4)
		{
			Att4(_DeltaTime); // 디테일 부족
		}
	}
	else {
		if (true == Att4Ready)
		{
			MonsterCollision->ActiveOn();
				if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
				{
					MonsterRenderer->ChangeAnimation("Att4_Left");
				}
				else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
					MonsterRenderer->ChangeAnimation("Att4_Right");
				}

				if (true == MonsterRenderer->IsCurAnimationEnd())
				{
					RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 4);
					IsIce = false;
					Att4Ready = false;;
				}
		}
		else if (true == Att3Delay)
		{
			Att3Sound = false;
			if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
			{
				MonsterRenderer->ChangeAnimation("Delay3_Left");
			}
			else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
				MonsterRenderer->ChangeAnimation("Delay3_Right");
			}

			if (true == MonsterRenderer->IsCurAnimationEnd())
			{
				RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 4);
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

			if (true == Att2Renderer->IsCurAnimationEnd())
			{
				Att2Renderer->ActiveOff();
				IsBullet = false;
			}

			if (true == MonsterRenderer->IsCurAnimationEnd())
			{
				RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 4);
				Att2Delay = false;;
			}
		}
		else if (true == Att1Ready)
		{
			Att1Collisiongather(_DeltaTime);
			if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
			{
				MonsterRenderer->ChangeAnimation("Att1_Left");
			}
			else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
				MonsterRenderer->ChangeAnimation("Att1_Right");
			}

			if (false == Att1Sound)
			{
				UEngineSound::SoundPlay("Hammer.wav");
				Att1Sound = true;
			}

			if (true == MonsterRenderer->IsCurAnimationEnd())
			{
				Att1Sound = false;
				RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 4);
				Att1Collision->ActiveOff();
				Att1Ready = false;;
			}
		}
		else {
			CalDir(_DeltaTime);
			Collisiongather(_DeltaTime);
			CalResult(_DeltaTime);
		}
	}
}

void AMainBoss::AniCreate()
{
	MonsterRenderer->CreateAnimation("Move_Right", "King_Right.png", 3,7, 0.3f, true);
	MonsterRenderer->CreateAnimation("Move_Left", "King_Left.png",3,7, 0.3f, true);

	MonsterRenderer->CreateAnimation("Att1Ready_Right", "King_Right.png",21,24, 0.2f, false);
	MonsterRenderer->CreateAnimation("Att1Ready_Left", "King_Left.png", 21, 24, 0.2f, false);

	MonsterRenderer->CreateAnimation("Att1_Right", "King_Right.png", { 26,29,30,31,32 }, 0.2f, false);
	MonsterRenderer->CreateAnimation("Att1_Left", "King_Left.png", { 26,29,30,31,32 }, 0.2f, false);


	MonsterRenderer->CreateAnimation("Att2_Right", "King_Right.png", 32, 35, 0.3f, false);
	MonsterRenderer->CreateAnimation("Att2_Left", "King_Left.png", 32, 35, 0.3f, false);

	MonsterRenderer->CreateAnimation("Delay2_Right", "King_Right.png", {35,35,34,33,32}, 0.3f, false);
	MonsterRenderer->CreateAnimation("Delay2_Left", "King_Left.png", { 35,35,34,33,32 }, 0.3f, false);


	MonsterRenderer->CreateAnimation("Att3_Right", "King_Right.png", { 37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53 }, 0.05f, false);
	MonsterRenderer->CreateAnimation("Att3_Left", "King_Left.png", { 37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53 }, 0.05f, false);

	MonsterRenderer->CreateAnimation("Delay3_Right", "King_Right.png", 54, 60,0.5f, false);
	MonsterRenderer->CreateAnimation("Delay3_Left", "King_Left.png", 54, 60,0.5f, false);
	
	Att2Renderer->CreateAnimation("Att2Effect_Left", "King_Left.png", 61, 61, 0.1f, false);
	Att2Renderer->CreateAnimation("Att2Effect_Right", "King_RIght.png", 61, 61, 0.1f, false);

	MonsterRenderer->CreateAnimation("Att4Ready_Right", "King_Right.png", {13,14,14,14,15,15,16}, 0.15f, false);
	MonsterRenderer->CreateAnimation("Att4Ready_Left", "King_Left.png", { 13,14,14,14,15,15,16 }, 0.15f, false);

	MonsterRenderer->CreateAnimation("Att4_Right", "King_Right.png", { 16,17,17,17,18,18,18,20 }, 0.2f, false);
	MonsterRenderer->CreateAnimation("Att4_Left", "King_Left.png", { 16,17,17,17,18,18,18,20}, 0.2f, false);

	MonsterRenderer->CreateAnimation("die_Right", "King_Right.png", { 8,9,10,12,11 }, 0.3f, false);
	MonsterRenderer->CreateAnimation("die_Left", "King_Left.png", { 8,9,10,12,11 }, 0.3f, false);

	MonsterRenderer->CreateAnimation("hit_Right", "King_Right.png", 56,56, 0.3f, false);
	MonsterRenderer->CreateAnimation("hit_Left", "King_Left.png", 56,56, 0.3f, false);
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

void AMainBoss::Att1(float _DeltaTime)
{

	FVector Move = FVector::Zero;

	if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att1Ready_Left");
		Move+=FVector::Left * _DeltaTime * 70.0f;
		WallX = -20;
		Att1Collision->SetTransform({ {-100,80}, {100, 100} });
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att1Ready_Right");
		Move+=FVector::Right * _DeltaTime * 70.0f;
		WallX = 20;
		Att1Collision->SetTransform({ {100,80}, {100, 100} });
	}

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 20, Color8Bit::RedA);

	if (ColorR == Color8Bit(255, 0, 0, 0)) // 벽(Red)랑 충돌인 경우 -> 움직이는 값 0
	{
		Move = FVector::Zero;
	}

	AddActorLocation(Move);

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		//AttCollision->ActiveOff();
		IsAtt = false;
		skillcooldowntime = 4.0f;
		Att1Ready = true;
		Att1Collision->SetActive(true, 0.25f);
	}
	return;
}

void AMainBoss::Att2()
{

	
	if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att2_Left");
		Att2Renderer->SetTransform({ {-105,20} ,{64 * 7,64 * 7} });
		Att2Renderer->ChangeAnimation("Att2Effect_Left");
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att2_Right");
		Att2Renderer->SetTransform({ {105,20} ,{64 * 7,64 * 7} });
		Att2Renderer->ChangeAnimation("Att2Effect_Right");
		
	}
	
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		if (false == IsBullet)
		{
			UEngineSound::SoundPlay("BulletReady.wav");
			IsBullet = true;
			ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>();
			NewBullet->SetActorLocation(this->GetActorLocation());
			if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
			{
				NewBullet->SetDir(FVector::Left);
			}
			else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
				NewBullet->SetDir(FVector::Right);
			}
		}
		Att2Renderer->ActiveOn();
		IsAtt = false;
		skillcooldowntime = 5.5f;
		Att2Delay = true;
	}
	

	return;
}

void AMainBoss::Att3(float _DeltaTime)
{
	MonsterCollision->ActiveOff();
	FVector Move = FVector::Zero;

	if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att3_Left");
		Move+=FVector::Left* _DeltaTime*100.0f;
		WallX = -20;
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att3_Right");
		Move += FVector::Right * _DeltaTime * 100.0f;
		WallX = 20;
	}

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX()+WallX, GetActorLocation().iY()-20, Color8Bit::RedA);
	
	if (ColorR == Color8Bit(255, 0, 0, 0)) // 벽(Red)랑 충돌인 경우 -> 움직이는 값 0
	{
		Move = FVector::Zero;
	}

	AddActorLocation(Move);

	Att3Collision->ActiveOn();
	Att3Collisiongather(_DeltaTime);
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		IsAtt = false;
		skillcooldowntime = 5.5f;
		Att3Delay = true;
		MonsterCollision->ActiveOn();
		Att3Collision->ActiveOff();
	}
	return;
}

void AMainBoss::Att4(float _DeltaTime)
{

	MonsterCollision->ActiveOff();
	FVector Move = FVector::Zero;

	if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att4Ready_Left");
		WallX = -20;
		Move+=(FVector::Left * _DeltaTime * 50.0f)+JumpVector* _DeltaTime;
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att4Ready_Right");
		WallX = 20;
		Move += (FVector::Right * _DeltaTime * 50.0f) + JumpVector* _DeltaTime;
	}

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 20, Color8Bit::RedA);

	if (ColorR == Color8Bit(255, 0, 0, 0)) // 벽(Red)랑 충돌인 경우 -> 움직이는 값 0
	{
		Move = FVector::Zero;
	}

	AddActorLocation(Move);

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		if (false == IsIce)
		{
			UEngineSound::SoundPlay("Ice.wav");
			IsIce = true;
			AIce* NewIce = GetWorld()->SpawnActor<AIce>();
			NewIce->SetOwner(EIceOwner::Boss);
			NewIce->SetActorLocation(this->GetActorLocation());
			if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // 왼쪽 방향
			{
				NewIce->SetDir(FVector::Left);
			}
			else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
				NewIce->SetDir(FVector::Right);
			}
		}
		IsAtt = false;
		skillcooldowntime = 4.0f;
		Att4Ready = true;
	}

	return;
}

void AMainBoss::Att1Collisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == Att1Collision->CollisionCheck(ECollisionOrder::kirby, Result))
	{
		MainPlayer->Sethitstate(true); // 플레이어 충돌 체크
		MainPlayer->SetHitDir(MonsterDirNormal * FVector::Right);
		MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
		MainPlayer->GetKirbyCollision()->ActiveOff();
		MainPlayer->AddHP(GetAtt());
		MainPlayer->HitStart(); // hit 상태 스타트
		Att1Collision->ActiveOff();
	}
}

void AMainBoss::Att3Collisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == Att3Collision->CollisionCheck(ECollisionOrder::kirby, Result))
	{
		MainPlayer->Sethitstate(true); // 플레이어 충돌 체크
		MainPlayer->SetHitDir(MonsterDirNormal * FVector::Right);
		MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
		MainPlayer->GetKirbyCollision()->ActiveOff();
		MainPlayer->AddHP(GetAtt());
		MainPlayer->HitStart(); // hit 상태 스타트
	}
}

void AMainBoss::Collisiongather(float _DeltaTime)
{
	// 콜리전 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result)) // 얼지 않은 상태에서 플레이어와 충돌
	{
		MainPlayer->Sethitstate(true); // 플레이어 충돌 체크
		MainPlayer->SetHitDir(MonsterDirNormal * FVector::Right);
		MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
		MainPlayer->GetKirbyCollision()->ActiveOff();
		MainPlayer->AddHP(GetAtt());
		MainPlayer->HitStart(); // hit 상태 스타트

		//IsDie = true; // 죽음 체크

	}
}

void AMainBoss::CalResult(float _DeltaTime)
{
	AddActorLocation(MovePos);
}

void AMainBoss::hitEvent()
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
	}
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
