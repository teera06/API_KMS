#include "Sir.h"

#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"

ASir::ASir()
{
}

ASir::~ASir()
{
}

void ASir::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	CalDir();
	SkillDir(_DeltaTime);


	Collisiongather(_DeltaTime);


	//SirRenderer->Destroy(0.1f);
}

void ASir::BeginPlay()
{
	AActor::BeginPlay();
	{
		SirRenderer = CreateImageRenderer(ERenderOrder::Ice); // 이미지 랜더 생성
		SirRenderer->SetImage("Sir_Right.png"); // 이미지 Set
		SirRenderer->SetTransform({ {0,0}, {64 * 3, 64 * 3} }); // 랜더의 위치 크기 
	}
	{
		SirCollision = CreateCollision(ECollisionOrder::SirAttack);
		SirCollision->SetScale({ 100,70 });
		SirCollision->SetColType(ECollisionType::CirCle);
		SirCollision->SetActive(true, 0.3f);
	}

	AniCreate();
}

void ASir::AniCreate()
{
	SirRenderer->CreateAnimation("Sir_Right", "Sir_Right.png", 95,98, 0.05f, true);
	SirRenderer->CreateAnimation("Sir_Left", "Sir_Left.png", 95,98, 0.05f, true);
	SirRenderer->ChangeAnimation("Sir_Right");
}

void ASir::CalDir()
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 
}

void ASir::SkillDir(float _DeltaTime)
{
	FVector Move = FVector::Zero;
	FVector CurX = GetActorLocation() * FVector::Right;
	FVector RangeXL = StartPos + (FVector::Left * RangeX);
	FVector RangeXR = StartPos + (FVector::Right * RangeX);
	//StartDir = GetDir();
	if (GetDir().iX() == FVector::Left.iX())
	{
		if (false == skillOn)
		{
			skillOn = true;
			StartDir = FVector::Left;
		}
		SirRenderer->ChangeAnimation("Sir_Right");
	}
	else
	{
		if (false == skillOn)
		{
			skillOn = true;
			StartDir = FVector::Right;
		}
		SirRenderer->ChangeAnimation("Sir_Left");
	}

	if (RangeXR.iX() <= CurX.iX() && GetDir().iX() == FVector::Right.iX()) // 기본 몬스터 이동 방향 좌우 +-100 그 범위 벗어나는 경우 -> 방향 변환
	{
		StartDir = StartDir * FVector::Left;
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 1000.0f); // 해당 범위 벗어나야 아래의 else문을 실행할 수 있기에 다시 범위안으로 옮기고 리턴
		return;
	}
	
	if (RangeXL.iX() >= CurX.iX() && GetDir().iX() == FVector::Left.iX()) // 기본 몬스터 이동 방향 좌우 +-100 그 범위 벗어나는 경우 -> 방향 변환
	{
		StartDir = StartDir * FVector::Left;
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 1000.0f); // 해당 범위 벗어나야 아래의 else문을 실행할 수 있기에 다시 범위안으로 옮기고 리턴
		return;
	}
	
	AddActorLocation(StartDir * 500.0f * _DeltaTime);
}

void ASir::Collisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (Owner == ESirOwner::kirby)
	{
		if (true == SirCollision->CollisionCheck(ECollisionOrder::Monster, Result))
		{
			// 이런식으로 상대를 사용할수 있다.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);


			if (nullptr == Monster)
			{
				MsgBoxAssert("터져야겠지....");
			}

			if (MonsterDirNormal.iX() == -1) // 몬스터가 플레이어를 향하는 방향의 반대 방향으로 힘이 작용
			{
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Left"); // 죽는 애니메이션

			}
			else {
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // 죽는 애니메이션
			}
			FVector DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
			Monster->SetIsDie(true);
			Monster->SetDiePos(DiePos);
			Monster->Destroy(0.3f);
		}
		else if (true == SirCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
		{
			// 이런식으로 상대를 사용할수 있다.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);


			if (nullptr == Monster)
			{
				MsgBoxAssert("터져야겠지....");
			}

			if (MonsterDirNormal.iX() == -1) // 몬스터가 플레이어를 향하는 방향의 반대 방향으로 힘이 작용
			{
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Left"); // 죽는 애니메이션

			}
			else {
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // 죽는 애니메이션
			}
			FVector DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
			Monster->SetIsDie(true);
			Monster->SetDiePos(DiePos);
			Monster->Destroy(0.3f);
		}
		else if (true == SirCollision->CollisionCheck(ECollisionOrder::FireMonster, Result))
		{
			// 이런식으로 상대를 사용할수 있다.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Fire* Monster = dynamic_cast<AMonster_Fire*>(Ptr);


			if (nullptr == Monster)
			{
				MsgBoxAssert("터져야겠지....");
			}

			if (MonsterDirNormal.iX() == -1) // 몬스터가 플레이어를 향하는 방향의 반대 방향으로 힘이 작용
			{
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Left"); // 죽는 애니메이션

			}
			else {
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // 죽는 애니메이션
			}
			FVector DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
			Monster->SetIsDie(true);
			Monster->SetDiePos(DiePos);
			Monster->Destroy(0.3f);
		}else if (true == SirCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
		{
			// 이런식으로 상대를 사용할수 있다.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Sir* Monster = dynamic_cast<AMonster_Sir*>(Ptr);


			if (nullptr == Monster)
			{
				MsgBoxAssert("터져야겠지....");
			}

			if (MonsterDirNormal.iX() == -1) // 몬스터가 플레이어를 향하는 방향의 반대 방향으로 힘이 작용
			{
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Left"); // 죽는 애니메이션

			}
			else {
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // 죽는 애니메이션
			}
			FVector DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
			Monster->SetIsDie(true);
			Monster->SetDiePos(DiePos);
			Monster->Destroy(0.3f);
		}
		
		
		
		if (true == SirCollision->CollisionCheck(ECollisionOrder::kirby, Result))
		{
			MainPlayer->SetSirUse(false);
			Destroy();
				
		}



		// 픽셀 충돌
		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 20, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			MainPlayer->SetSirUse(false);
			Destroy();
			
		}
	}
	else if (Owner == ESirOwner::SirMonster)
	{
		if (true == SirCollision->CollisionCheck(ECollisionOrder::kirby, Result))
		{
			MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
			MainPlayer->Sethitstate(true); // 플레이어 충돌 체크
			MainPlayer->SetHitDir(GetDir());
			MainPlayer->GetKirbyCollision()->ActiveOff();
			MainPlayer->AddHP(-20);
			MainPlayer->HitStart(); // hit 상태 스타트
		}
		else if (true == SirCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
		{
			Destroy();
		}

		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 20, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			Destroy();
		}
	}

}
