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


	if (GetDir().iX() != FVector::Zero.iX())
	{
		CalDir();
		SkillDir(_DeltaTime);


		Collisiongather(_DeltaTime);
	}
	

}

void ASir::BeginPlay()
{
	AActor::BeginPlay();
	{
		SirRenderer = CreateImageRenderer(ERenderOrder::Sir); // 이미지 랜더 생성
		SirRenderer->SetImage("Sir_Right.png"); // 이미지 Set
		SirRenderer->SetTransform({ {0,0}, {64 * 3, 64 * 3} }); // 랜더의 위치 크기 
		//SirRenderer->SetActive(true, 0.1f);
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
}

void ASir::CalDir()
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터를 향해 날리는 방향

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 
}

void ASir::SkillDir(float _DeltaTime)
{
	FVector Move = FVector::Zero;
	FVector CurX = GetActorLocation() * FVector::Right;
	FVector RangeXL = StartPos + (FVector::Left * RangeX); // 부메랑의 던지 방향의 이동 범위 계산 (왼쪽으로 던질 경우)
	FVector RangeXR = StartPos + (FVector::Right * RangeX); // (오른쪽으로 던질 경우)

	if (GetDir().iX() == FVector::Left.iX()) // 왼쪽 방향
	{
		if (false == skillOn) // 스킬을 사용하지 않은 경우에만 
		{
			skillOn = true;
			StartDir = FVector::Left; // 부메랑 이동 방향
		}
		LRCheck = true; // 부메랑은 왼쪽에서 오른쪽으로 이동 -> True=Right
		DelX = FVector::Right*MainPlayer->GetActorLocation(); // 플레이어의 X축 위치를 저장
		SirRenderer->ChangeAnimation("Sir_Right");
	}
	else // 오른쪽 방향
	{
		if (false == skillOn)
		{
			skillOn = true;
			StartDir = FVector::Right;
		}
		LRCheck = false; // 부메랑은 오른쪽에서 왼쪽으로 이동 -> false=Left
		DelX = FVector::Right * MainPlayer->GetActorLocation();
		SirRenderer->ChangeAnimation("Sir_Left");
	}

	if (RangeXR.iX() <= CurX.iX() && GetDir().iX() == FVector::Right.iX())  // 오른쪽으로 던질때 
	{
		StartDir = StartDir * FVector::Left; // 돌아오는 방향은 왼쪽
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 1000.0f); 
		return;
	}
	
	if (RangeXL.iX() >= CurX.iX() && GetDir().iX() == FVector::Left.iX()) // 왼쪽으로 던질때 
	{
		StartDir = StartDir * FVector::Left; // 돌아오는 방향은 반대 방향인 오른쪽
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 1000.0f); 
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
			StartDir = StartDir * FVector::Left;
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
			StartDir = StartDir * FVector::Left;
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
			StartDir = StartDir * FVector::Left;
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
			StartDir = StartDir * FVector::Left;
		}
		
		
		
		// 부메랑을 받지 못하고 범위가 크게 벗어날때
		FVector XL = DelX + FVector::Left * 500.0f; // 몬스터 왼쪽 플레이어 인식 시야 X축
		FVector XR = DelX + FVector::Right * 500.0f; // 몬스터 오른쪽 플레이어 인식 시야 X축

		if (true==LRCheck && XR.iX()<GetActorLocation().iX()) // 돌아오는 방향은 오른쪽 -> 부메랑이 오른쪽 방향으로 설정한 범위보다 커질때 동작
		{
			MainPlayer->SetSirUse(false); 
			Destroy();
		}
		else if (false==LRCheck &&  XL.iX()>GetActorLocation().iX()) // 돌아오는 방향은 왼쪽 -> 부메랑이 왼쪽 방향으로 설정한 범위보다 작을 때 동작
		{
			MainPlayer->SetSirUse(false);
			Destroy();
		}
		
		// 커비가 받아낼때
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
			StartDir = StartDir * FVector::Left;
		}
		else if (true == SirCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
		{
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Sir* Monster = dynamic_cast<AMonster_Sir*>(Ptr);

			Monster->SetSirUse(false);
			Destroy();
		}

		// 픽셀 충돌
		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 20, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			StartDir = StartDir * FVector::Left;
		}
	}

}
