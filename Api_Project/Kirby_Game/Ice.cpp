#include "Ice.h"

#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Kirby_Player.h"

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
		IceRenderer->ChangeAnimation("Ice_Left");
	}
	else
	{
		IceRenderer->ChangeAnimation("Ice_Right");
	}

	IceCollision->SetPosition({ GetDir().iX() * 100,0 });
	IceRenderer->SetPosition({ GetDir().iX() * 105,-35 });


	std::vector<UCollision*> Result;
	if (true == IceCollision->CollisionCheck(ECollisionOrder::Monster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		int a = 0;
		AActor* Ptr = Collision->GetOwner();
		AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("터져야겠지....");
		}
		Monster->AddActorLocation(GetDir() * FVector::Left * 500.0f * _DeltaTime);
		Monster->SetEatState(true);
		Monster->Destroy(0.3f);

		Destroy(0.1f);
	}
	else if (true == IceCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		int a = 0;
		AActor* Ptr = Collision->GetOwner();
		Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("터져야겠지....");
		}
		//Monster->AddActorLocation(GetDir() * FVector::Left * 500.0f * _DeltaTime);
		//Monster->SetEatState(true);
		//SetModeName("Ice_");

		Monster->Destroy(0.3f);

		Destroy(0.1f);
	}
}

void AIce::BeginPlay()
{
	AActor::BeginPlay();
	{
		IceRenderer = CreateImageRenderer(ERenderOrder::Ice); // 이미지 랜더 생성
		IceRenderer->SetImage("effect_Right.png"); // 이미지 Set
		IceRenderer->SetActive(true, 0.1f);
		IceRenderer->SetTransform({ {0,0}, {150, 120} }); // 랜더의 위치 크기 
	}
	{
		IceCollision = CreateCollision(ECollisionOrder::AllStar);
		IceCollision->SetScale({ 70,70 });

		IceCollision->SetColType(ECollisionType::Rect);
	}

	IceRenderer->CreateAnimation("Ice_Right", "Ice_Right.png", {104,105,106,107,109,110,111}, 0.1f, true);
	IceRenderer->CreateAnimation("Ice_Left", "Ice_Left.png", { 104,105,106,107,109,110,111 }, 0.1f, true);
	IceRenderer->ChangeAnimation("Ice_Right");

	Destroy(0.45f);
}
