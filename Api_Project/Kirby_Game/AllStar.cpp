#include "AllStar.h"
#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"
#include "Monster_Mike.h"
#include "SubBoss.h"
#include "Box.h"


AAllStar::AAllStar()
{
}

AAllStar::~AAllStar()
{
}

void AAllStar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetDir() * Speed * _DeltaTime);

	CalDir();
	Collisiongather(_DeltaTime);
}

void AAllStar::BeginPlay()
{
	AActor::BeginPlay();
	{
		AllStarRenderer = CreateImageRenderer(ERenderOrder::Base);
		AllStarRenderer->SetImage("kirby2_Right.png");
		AllStarRenderer->SetTransform({ {0,0}, {200, 200} });
		AllStarRenderer->SetActive(true, 0.1f);

		AllStarRenderer->CreateAnimation("AllAttack_Right", "kirby2_Right.png", 54, 57, 0.1f, true);

		AllStarRenderer->ChangeAnimation("AllAttack_Right");
	}

	
	{
		AllStarCollision= CreateCollision(ECollisionOrder::AllStar);
		AllStarCollision->SetScale({ 80, 80 });
		AllStarCollision->SetColType(ECollisionType::Rect);
	}

	Destroy(1.0f);
}

void AAllStar::Collisiongather(float _DeltaTime)
{
	// 사각형 충돌
	std::vector<UCollision*> Result;
	if (true == AllStarCollision->CollisionCheck(ECollisionOrder::Monster, Result))
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
		Destroy();
	}
	else if (true == AllStarCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
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
		Destroy();
	}
	else if (true == AllStarCollision->CollisionCheck(ECollisionOrder::FireMonster, Result))
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
		Destroy();
	}
	else if (true == AllStarCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
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
		Destroy();
	}
	else if (true == AllStarCollision->CollisionCheck(ECollisionOrder::MikeMonster, Result) 
		|| true == AllStarCollision->CollisionCheck(ECollisionOrder::SubBoss, Result)
		|| true == AllStarCollision->CollisionCheck(ECollisionOrder::IceBox, Result)
		|| true == AllStarCollision->CollisionCheck(ECollisionOrder::MainBoss, Result)
		)
	{
		Destroy();
	}
	else if (true == AllStarCollision->CollisionCheck(ECollisionOrder::Box, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		ABox* item = dynamic_cast<ABox*>(Ptr);

		if (nullptr == item)
		{
			MsgBoxAssert("터져야겠지....");
		}

		item->SetIsDelete(true);
		Destroy();
	}



	// 픽셀 충돌
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 20, Color8Bit::RedA);

	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		Destroy();
	}
}

void AAllStar::CalDir()
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 
}
