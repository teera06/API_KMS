#include "Ice.h"

#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"

AIce::AIce()
{
}

AIce::~AIce()
{
}

void AIce::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (GetDir().iX() != FVector::Zero.iX())
	{
		SkillDir();


		Collisiongather(_DeltaTime);
	}
	IceRenderer->Destroy(0.1f);
}

void AIce::BeginPlay()
{
	AActor::BeginPlay();
	{
		IceRenderer = CreateImageRenderer(ERenderOrder::Ice); // 이미지 랜더 생성
		IceRenderer->SetImage("Ice_Right.png"); // 이미지 Set
		IceRenderer->SetTransform({ {0,0}, {128*3, 128*2} }); // 랜더의 위치 크기 
		IceRenderer->SetActive(true, 0.2f);
	}
	{
		IceCollision = CreateCollision(ECollisionOrder::IceAttack);
		IceCollision->SetScale({ 100,70 });
		IceCollision->SetColType(ECollisionType::Rect);
		IceCollision->SetActive(true, 0.2f);
	}

	AniCreate();
	IceRenderer->ChangeAnimation("Ice_Right");
	Destroy(0.5f);
}

void AIce::AniCreate()
{
	IceRenderer->CreateAnimation("Ice_Right", "Ice_Right.png", { 104,105,106,107,109,110,111 }, 0.05f, true);
	IceRenderer->CreateAnimation("Ice_Left", "Ice_Left.png", { 104,105,106,107,109,110,111 }, 0.05f, true);
}

void AIce::SkillDir()
{
	if (GetDir().iX() == FVector::Left.iX())
	{
		IceRenderer->ChangeAnimation("Ice_Right");
	}
	else
	{
		IceRenderer->ChangeAnimation("Ice_Left");
	}

	if (Owner == EIceOwner::Boss)
	{
		IceCollision->SetPosition({ GetDir().iX() * 210,80 });
		IceRenderer->SetPosition({ GetDir().iX() * 200,80 });
		IceRenderer->SetScale({128 * 5, 128 * 3} ); // 랜더의 위치 크기 
		IceCollision->SetScale({ 300,200 });
	}
	else {
		IceCollision->SetPosition({ GetDir().iX() * 120,0 });
		IceRenderer->SetPosition({ GetDir().iX() * 125,-5 });
		IceRenderer->SetScale({128 * 3, 128 * 2}); // 랜더의 위치 크기 
		IceCollision->SetScale({ 100,70 });
	}
}

void AIce::Collisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (Owner == EIceOwner::kirby)
	{
		if (true == IceCollision->CollisionCheck(ECollisionOrder::Monster, Result))
		{
			// 이런식으로 상대를 사용할수 있다.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);

			if (nullptr == Monster)
			{
				MsgBoxAssert("터져야겠지....");
			}
			IceCollision->Destroy();
			Monster->IceState();
		}
		else if (true == IceCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
		{
			// 이런식으로 상대를 사용할수 있다.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);

			if (nullptr == Monster)
			{
				MsgBoxAssert("터져야겠지....");
			}
			IceCollision->Destroy();
			Monster->IceState();
		}
		else if (true == IceCollision->CollisionCheck(ECollisionOrder::FireMonster, Result))
		{
			// 이런식으로 상대를 사용할수 있다.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Fire* Monster = dynamic_cast<AMonster_Fire*>(Ptr);

			if (nullptr == Monster)
			{
				MsgBoxAssert("터져야겠지....");
			}
			IceCollision->Destroy();
			Monster->IceState();
		}
		else if (true == IceCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
		{
			// 이런식으로 상대를 사용할수 있다.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Sir* Monster = dynamic_cast<AMonster_Sir*>(Ptr);

			if (nullptr == Monster)
			{
				MsgBoxAssert("터져야겠지....");
			}
			IceCollision->Destroy();
			Monster->IceState();
		}
	}
	else if (Owner == EIceOwner::iceMonster)
	{
		if (true == IceCollision->CollisionCheck(ECollisionOrder::kirby, Result))
		{

			MainPlayer->Sethitstate(true); // 플레이어 충돌 체크
			MainPlayer->SetHitDir(GetDir());
			MainPlayer->GetKirbyCollision()->ActiveOff();
			MainPlayer->AddHP(GetAtt());
			MainPlayer->IcehitStart(); // hit 상태 스타트

			IceCollision->Destroy();
		}
	}
	else if (Owner == EIceOwner::Boss)
	{
		if (true == IceCollision->CollisionCheck(ECollisionOrder::kirby, Result))
		{

			MainPlayer->Sethitstate(true); // 플레이어 충돌 체크
			MainPlayer->SetHitDir(GetDir());
			MainPlayer->GetKirbyCollision()->ActiveOff();
			MainPlayer->AddHP(GetAtt());
			MainPlayer->IcehitStart(); // hit 상태 스타트

			IceCollision->Destroy();
		}
	}
}
