#include "pengi_Ice.h"
#include "ModeEnum.h"
#include "Monster_Base.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"
#include "Ice.h"

#include <EngineCore/EngineCore.h> // GetWorld 사용 -> Level 정보 이용
Apengi_Ice::Apengi_Ice()
{
}

Apengi_Ice::~Apengi_Ice()
{
}

void Apengi_Ice::IceState()
{
	scale = 2;
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	IsIce = true;
}

void Apengi_Ice::BeginPlay()
{
	AActor::BeginPlay();

	scale = 5;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("pengi_Right.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,0}, {64*scale, 64*scale} }); // 랜더의 위치 크기 

		MonsterDieRenderer = CreateImageRenderer(ERenderOrder::effect); // 이미지 랜더 생성
		MonsterDieRenderer->SetImage("Effects2_Left.png"); // 이미지 Set
		MonsterDieRenderer->SetTransform({ {0,1}, {64 * 2, 64 * 2} }); // 랜더의 위치 크기 
		MonsterDieRenderer->ActiveOff();
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::iceMonster);
		MonsterCollision->SetScale({ 60, 60 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	AniCreate();
	SoundCreate();
	MonsterRenderer->ChangeAnimation("Idle_Left");
}

void Apengi_Ice::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();
	if (false == IsDie) // Destroy(0.3f); -> 조건없이 계속 move업데이트 되면서 0.3f도 똑같이 유지 (한번만 실행해야함)
	{
		MoveUpdate(_DeltaTime);
	}
	else { // IsDIe가 true이면 MoveUpdate는 연속 실행이 안됨 -> Destroy(0.3f) 작동
		HitDietime -= _DeltaTime;
		if (HitDietime < 0 && false==IsIce)
		{
			SHitDie.On();
		}
		else if (HitDietime < 0 && true == IsIce)
		{
			SIceDie.On();
		}

		if (false == Iseffect && false==IsIce)
		{
			Iseffect = true;
			MonsterDieRenderer->SetActive(true, 0.15f);
			MonsterDieRenderer->ChangeAnimation("effect");
		}
		AddActorLocation(DiePos); // 죽으면서 이동
	}
}

void Apengi_Ice::AniCreate()
{
	MonsterDieRenderer->CreateAnimation("effect", "Effects2_Left.png", 21, 24, 0.1f, false); // 걷기

	MonsterRenderer->CreateAnimation("Idle_Right", "Pengi_Right.png", 0, 0, 0.3f, true);  
	MonsterRenderer->CreateAnimation("Idle_Left", "Pengi_Left.png", 0, 0, 0.3f, true); 
	MonsterRenderer->CreateAnimation("Move_Right", "Pengi_Right.png", 1, 3, 0.3f, true); 
	MonsterRenderer->CreateAnimation("Move_Left", "Pengi_Left.png", 1, 3, 0.3f, true); 
	MonsterRenderer->CreateAnimation("Att_Right", "Pengi_Right.png", 4, 6, 0.15f, false);
	MonsterRenderer->CreateAnimation("Att_Left", "Pengi_Left.png",4, 6, 0.15f, false);

	MonsterRenderer->CreateAnimation("die_Right", "Pengi_Left.png", 7, 8, 0.3f, true); // 죽음 
	MonsterRenderer->CreateAnimation("die_Left", "Pengi_Right.png", 7, 8, 0.3f, true); // 죽음 
	MonsterRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false); // 얼음
	MonsterRenderer->CreateAnimation("Effect", "Effects2_RIght.png", 29, 30, 0.1f, true); // 죽는 애니메이션
}

void Apengi_Ice::SoundCreate()
{
	{
		SHitDie = UEngineSound::SoundPlay("MonsterDie.wav");
		SHitDie.SetVolume(0.6f);
		SHitDie.Off();
	}

	{
		SIceDie = UEngineSound::SoundPlay("MonsterIceDie.wav");
		SIceDie.SetVolume(0.6f);
		SIceDie.Off();
	}

	{
		SIceAtt = UEngineSound::SoundPlay("Ice.wav");
		SIceAtt.SetVolume(0.6f);
		SIceAtt.Off();
	}
}

void Apengi_Ice::IceToMonster(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::Monster, Result)) // 얼지 않은 상태에서 플레이어와 충돌
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);

		// 방어코드

		if (nullptr == Monster)
		{
			MsgBoxAssert("몬스터베이스 플레이어 인식 못함");
		}

		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // 죽는 애니메이션
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
	}
	else if (true == MonsterCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);

		// 방어코드

		if (nullptr == Monster)
		{
			MsgBoxAssert("몬스터베이스 플레이어 인식 못함");
		}

		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // 죽는 애니메이션
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
	}
	else if (true == MonsterCollision->CollisionCheck(ECollisionOrder::FireMonster, Result))
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Fire* Monster = dynamic_cast<AMonster_Fire*>(Ptr);

		// 방어코드

		if (nullptr == Monster)
		{
			MsgBoxAssert("몬스터베이스 플레이어 인식 못함");
		}

		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // 죽는 애니메이션
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
	}
	else if (true == MonsterCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Sir* Monster = dynamic_cast<AMonster_Sir*>(Ptr);

		// 방어코드

		if (nullptr == Monster)
		{
			MsgBoxAssert("몬스터베이스 플레이어 인식 못함");
		}

		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // 죽는 애니메이션
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		MonsterRenderer->ChangeAnimation("Effect");
		IsDie = true;
	}
}

void Apengi_Ice::Collisiongather(float _DeltaTime)
{
	// 콜리전 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == false) // 얼지 않은 상태에서 플레이어와 충돌
	{
		
		if (true == BaseOn) // 흡수할 때의 몬스터 충돌 -> 몬스터는 플레이어와 충돌할 경우 바로 죽음
		{
			Destroy();
		}
		else {// 일반적인 플레이와의 충돌
			MainPlayer->Sethitstate(true); // 플레이어 충돌 체크
			MainPlayer->SetHitDir(MonsterDirNormal*FVector::Right);
			MainPlayer->AddHP(GetAtt());
			MainPlayer->HitStart(); // hit 상태 스타트
			MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
			MainPlayer->GetKirbyCollision()->ActiveOff();

			if (MonsterDirNormal.iX() == -1) // 몬스터가 플레이어를 향하는 방향의 반대 방향으로 힘이 작용
			{
				MonsterRenderer->ChangeAnimation("die_Left"); // 죽는 애니메이션

			}
			else {
				MonsterRenderer->ChangeAnimation("die_Right"); // 죽는 애니메이션
			}
			DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
			IsDie = true; // 죽음 체크
		}
	}
	else if ((true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == true)) { // 얼음 상태로 커비와 충돌 하는 경우
		// 얼음 상태 일때 움직임 계산
		if (MonsterDirNormal.iX() == -1) // 몬스터가 플레이어를 향하는 방향의 반대 방향으로 힘이 작용
		{
			WallX = 20;
			IceMove = FVector::Right * IceSpeed * _DeltaTime;

		}
		else {
			WallX = -20;
			IceMove = FVector::Left * IceSpeed * _DeltaTime;
		}
	}
}

void Apengi_Ice::CalResult(float _DeltaTime)
{
	if (true == IsIce)
	{
		IceToMonster(_DeltaTime);
	}
	// 얼음 상태에서 벽에 충돌시 바로 삭제 -> 추후 이펙트 남길지 고민
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		if (true == IsIce)
		{
			IceMove = FVector::Zero;
			MonsterRenderer->ChangeAnimation("Effect");
			IsDie = true;
		}

		MovePos = FVector::Zero;

	}

	if (true == IsDie) // 죽으면
	{
		Destroy(0.3f); // 0.3f 뒤에 삭제
	}
	else {
		if (false == IsIce) // 죽거나, 얼음상태가 아니면 일반 행동
		{
			std::vector<UCollision*> Result;
			if (true == MonsterCollision->CollisionCheck(ECollisionOrder::IceBox, Result, MovePos * FVector::Right))
			{
				return;
			}
			AddActorLocation(MovePos);
		}
		else {
			MovePos = FVector::Zero;
			AddActorLocation(IceMove);
		}
	}
}

void Apengi_Ice::CalDir(float _DeltaTime)
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector MosterXL = MonsterPos + FVector::Left * sight; // 몬스터 왼쪽 플레이어 인식 시야 X축
	FVector MosterXR = MonsterPos + FVector::Right * sight; // 몬스터 오른쪽 플레이어 인식 시야 X축

	FVector AttXL = MonsterPos + FVector::Left * AttRange; // 몬스터 왼쪽 플레이어 공격 범위
	FVector AttXR = MonsterPos + FVector::Right * AttRange; // 몬스터 오른쪽 플레이어 공격 범위

	FVector PlayerX = PlayerPos * FVector::Right; // 플레이어 위치 X축

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 

	MovePos = FVector::Zero; // 플레이어 추격 시 이동

	if (MosterXL.iX() < PlayerX.iX() && MosterXR.iX() > PlayerX.iX()) // 몬스터 시야에 포착된 경우 X축 기준 왼쪽, 오른쪽
	{
		if (MonsterDirNormal.iX() == -1  && IsIce == false) // 왼쪽 방향
		{
			MonsterRenderer->ChangeAnimation("Move_Left");
			WallX = -20;
		}
		else if ((MonsterDirNormal.iX() == 1 || MonsterDirNormal.iX() == 0) && IsIce == false) { // 오른쪽 방향
			MonsterRenderer->ChangeAnimation("Move_Right");
			WallX = 20;
		}
		MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // 몬스터가 플레이어의 Y축도 인식할 수 있으니 FVector::Right 를 곱해 X축만 추격
	}
	else { // 플레이어가 몬스터 시야 밖인 경우 몬스터 행동강령
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // 왼쪽 방향
		{
			MonsterRenderer->ChangeAnimation("Idle_Left");
			WallX = -20;
		}
		else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // 오른쪽 방향
			MonsterRenderer->ChangeAnimation("Idle_Right");
			WallX = 20;
		}
	}

	// 플레이어를 향해 공격
	if (AttXL.iX() < PlayerX.iX() && AttXR.iX() > PlayerX.iX() && MainPlayer->GetActorLocation().iY()>=GetActorLocation().iY()-30) // 몬스터 시야에 포착된 경우 X축 기준 왼쪽, 오른쪽
	{
		IsAtt = true;
	}
}

void Apengi_Ice::IceAtt()
{

	if (false == IceAttcheck)
	{
		IceAttcheck = true;
		AIce* NewIce = GetWorld()->SpawnActor<AIce>();
		NewIce->SetActorLocation(this->GetActorLocation());
		NewIce->SetOwner(EIceOwner::iceMonster);
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // 왼쪽 방향
		{
			MonsterRenderer->ChangeAnimation("Att_Left");
			NewIce->SetDir(FVector::Left);
		}
		else if ((MonsterDirNormal.iX() == 1 || MonsterDirNormal.iX() == 0) && IsIce == false) { // 오른쪽 방향
			MonsterRenderer->ChangeAnimation("Att_Right");
			NewIce->SetDir(FVector::Right);
		}
	}

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		IsAtt = false;
		skillcooldowntime = 6.0f;
	}
}

void Apengi_Ice::GroundUp()
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

void Apengi_Ice::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // 중력 작용

	skillcooldowntime -= _DeltaTime;
	if (true == IsAtt && skillcooldowntime<0.0f && false == BaseOn && false==IsIce)
	{
		MovePos = FVector::Zero;
		SIceAtt.On();
		IceAtt();
	}
	else {
		SIceAtt.Replay();
		SIceAtt.Off();
		IceAttcheck = false;
		CalDir(_DeltaTime);
		Collisiongather(_DeltaTime);
		CalResult(_DeltaTime);
	}
}




