#include "Monster_Sir.h"

#include "ModeEnum.h"

#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"

#include "Sir.h"


AMonster_Sir::AMonster_Sir()
{
}

AMonster_Sir::~AMonster_Sir()
{
}

void AMonster_Sir::IceState()
{
	scale = 2;
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	IsIce = true;
}

void AMonster_Sir::BeginPlay()
{

	AActor::BeginPlay();

	scale = 3; // 평소 크기
	// 랜더링
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("SirMonster_Right.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	// 콜리전
	{
		MonsterCollision = CreateCollision(ECollisionOrder::SirMonster);
		MonsterCollision->SetScale({ 60, 60 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	// 애니메이션 만들기
	AniCreate();

	MonsterRenderer->ChangeAnimation("Move_Left");
}

void AMonster_Sir::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();
	if (false == checkLocation) // 첫 업데이트와, 벽에 충돌시에만 실행
	{
		// 이동 범위 지정
		CurLocation = GetActorLocation() * FVector::Right;
		RangeXL = CurLocation + (FVector::Left * RangeX);
		RangeXR = CurLocation + (FVector::Right * RangeX);
	}

	if (false == IsDie) // Destroy(0.3f); -> 조건없이 계속 move업데이트 되면서 0.3f도 똑같이 유지 (한번만 실행해야함)
	{
		checkLocation = true;
		MoveUpdate(_DeltaTime);
	}
	else { // IsDIe가 true이면 MoveUpdate는 연속 실행이 안됨 -> Destroy(0.3f) 작동
		AddActorLocation(DiePos); // 죽으면서 이동
	}
}

void AMonster_Sir::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // 중력 작용
	skillcooldowntime -= _DeltaTime;
	if (true == IsAtt && skillcooldowntime < 0.0f && false == GetBaseOnOff() && false == IsIce)
	{
		SirAtt();
		SirUse = true;
	}
	else {

		if (true == SirUse)
		{
			return;
		}
		CalDir();
		Collisiongather(_DeltaTime);
		CalResult(_DeltaTime);
	}
}

void AMonster_Sir::BaseMove(float _DeltaTime)
{
	FVector Move = FVector::Zero;
	FVector CurX = GetActorLocation() * FVector::Right;

	if (RangeXL.iX() >= CurX.iX() || RangeXR.iX() <= CurX.iX()) // 기본 몬스터 이동 방향 좌우 +-100 그 범위 벗어나는 경우 -> 방향 변환
	{
		if (false == IsAtt)
		{
			IsAtt= true;
			return;
		}
		StartDir.X *= -1;
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 100.0f); // 해당 범위 벗어나야 아래의 else문을 실행할 수 있기에 다시 범위안으로 옮기고 리턴
		return;
	}
	else
	{
		if (StartDir.iX() == -1 && IsIce == false) // 왼쪽 방향에 얼지 않은 상태
		{
			MonsterRenderer->ChangeAnimation("Move_Left");
			WallX = -20;
		}
		else if (StartDir.iX() == 1 && IsIce == false) { // 오른쪽 방향에 얼지 않은 상태
			MonsterRenderer->ChangeAnimation("Move_Right");
			WallX = 20;
		}

		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0)) // 벽 픽셀 충돌
		{
			if (true == IsIce) // 얼음 상태일 경우
			{
				IceMove = FVector::Zero; // 움직임 0
				Destroy(); // 죽음
			}
			else { // 아닌 경우는 방향 전환
				StartDir.X *= -1;
				checkLocation = false; // 몬스터가 벽에 닿으면 방향전환과 동시에 다시 위치 지정
			}
		}
		else { // 충돌하지 않은 경우
			Move += StartDir * _DeltaTime * MoveSpeed;
		}

		if (true == IsIce) // 얼음 상태일 경우 기존 얼지 않은 상태의 움직임을 해서는 안된다.
		{
			Move = FVector::Zero;
		}

		AddActorLocation(Move); // 최종 움직임 계산
	}
}

void AMonster_Sir::AniCreate()
{
	// 기본 걷는 모션

	MonsterRenderer->CreateAnimation("Move_Right", "SirMonster_Right.png", 4, 8, 0.1f, true); // 걷기
	MonsterRenderer->CreateAnimation("Move_Left", "SirMonster_Left.png", 4, 8, 0.1f, true); // 걷기

	MonsterRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false); // 얼음
	MonsterRenderer->CreateAnimation("die_Right", "SirMonster_Right.png", 4, 4, 0.2f, false); // 죽는 애니메이션
	MonsterRenderer->CreateAnimation("die_Left", "SIrMonster_Left.png", 4, 4, 0.2f, false); // 죽는 애니메이션
	
	MonsterRenderer->CreateAnimation("Att_Right", "SirMonster_Right.png", 9, 13, 0.2f, false); // 죽는 애니메이션
	MonsterRenderer->CreateAnimation("Att_Left", "SIrMonster_Left.png", 9, 13, 0.2f, false); // 죽는 애니메이션

	MonsterRenderer->CreateAnimation("Effect", "Effects.png", 29, 30, 0.1f, true); // 죽는 애니메이션
}

void AMonster_Sir::SirAtt()
{
	ASir* NewSir = GetWorld()->SpawnActor<ASir>();
	NewSir->SetOwner(ESirOwner::SirMonster);

	if (MonsterDirNormal.iX() == -1 ) // 왼쪽 방향
	{
		MonsterRenderer->ChangeAnimation("Att_Left");
		NewSir->SetDir(FVector::Left);
	}
	else if (MonsterDirNormal.iX() == 1) { // 오른쪽 방향
		MonsterRenderer->ChangeAnimation("Att_Right");
		NewSir->SetDir(FVector::Right);
	}

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		NewSir->SetStartPos(this->GetActorLocation() * FVector::Right);
		NewSir->SetActorLocation(this->GetActorLocation());
		IsAtt = false;
		skillcooldowntime = 6.0f;
	}
}

void AMonster_Sir::IceToMonster(float _DeltaTime)
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
		//MonsterRenderer->SetAlpha(0.5f+nf);
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
}

void AMonster_Sir::Collisiongather(float _DeltaTime)
{
	// 콜리전 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == false) // 얼지 않은 상태에서 플레이어와 충돌
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);

		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		// 방어코드
		if (nullptr == Player)
		{
			MsgBoxAssert("몬스터베이스 플레이어 인식 못함");
		}

		if (true == GetBaseOnOff()) // 흡수할 때의 몬스터 충돌 -> 몬스터는 플레이어와 충돌할 경우 바로 죽음
		{
			Destroy();
		}
		else {// 일반적인 플레이와의 충돌
			Player->Sethitstate(true); // 플레이어 충돌 체크
			Player->SetHitDir(MonsterDirNormal * FVector::Right);
			Player->GetKirbyRender()->SetAlpha(0.5f);
			Player->GetKirbyCollision()->ActiveOff();
			Player->AddHP(-20);
			Player->HitStart(); // hit 상태 스타트
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

void AMonster_Sir::CalDir()
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 
}

void AMonster_Sir::CalResult(float _DeltaTime)
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
	}

	if (true == IsDie) // 죽으면
	{
		Destroy(0.3f); // 0.3f 뒤에 삭제
	}
	else {
		if (false == IsIce) // 죽거나, 얼음상태가 아니면 일반 행동
		{
			BaseMove(_DeltaTime);
		}
		else {
			AddActorLocation(IceMove);
		}
	}
}

void AMonster_Sir::GroundUp()
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
