#include "Ice.h"

#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"

AIce::AIce()
{
}

AIce::~AIce()
{
}

void AIce::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (GetDir().iX() == FVector::Left.iX())
	{
		IceRenderer->ChangeAnimation("Ice_Right");
	}
	else
	{
		IceRenderer->ChangeAnimation("Ice_Left");
	}

	IceCollision->SetPosition({ GetDir().iX() * 120,0 });
	IceRenderer->SetPosition({ GetDir().iX() * 125,-5 });


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
			IceCollision->Destroy(0.1f);
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
			IceCollision->Destroy(0.1f);
			Monster->IceState();
		}
	}
	else if (Owner == EIceOwner::iceMonster)
	{
		if (true == IceCollision->CollisionCheck(ECollisionOrder::kirby, Result))
		{
			// 이런식으로 상대를 사용할수 있다.
			UCollision* Collision = Result[0];
			
			MainPlayer->AddHP(-20);
			IceCollision->Destroy(0.1f);
		}
	}
	

	IceRenderer->Destroy(0.1f);
}

void AIce::BeginPlay()
{
	AActor::BeginPlay();
	{
		IceRenderer = CreateImageRenderer(ERenderOrder::Ice); // 이미지 랜더 생성
		IceRenderer->SetImage("Ice_Right.png"); // 이미지 Set
		IceRenderer->SetActive(true, 0.45f);
		IceRenderer->SetTransform({ {0,0}, {128*3, 128*2} }); // 랜더의 위치 크기 
	}
	{
		IceCollision = CreateCollision(ECollisionOrder::IceAttack);
		IceCollision->SetScale({ 100,70 });
		IceCollision->SetColType(ECollisionType::Rect);
	}

	IceRenderer->CreateAnimation("Ice_Right", "Ice_Right.png", {104,105,106,107,109,110,111}, 0.05f, true);
	IceRenderer->CreateAnimation("Ice_Left", "Ice_Left.png", { 104,105,106,107,109,110,111 }, 0.05f, true);
	IceRenderer->ChangeAnimation("Ice_Right");

	Destroy(1.0f);
}
