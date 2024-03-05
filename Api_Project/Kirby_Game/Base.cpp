#include "Base.h"
#include <EngineCore\EngineCore.h>
#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"
#include "Monster_Mike.h"

#include "Kirby_Player.h"

ABase::ABase()
{
}

ABase::~ABase()
{
}

void ABase::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (GetDir().iX() == FVector::Left.iX())
	{
		BaseRenderer->ChangeAnimation("effect_Left");
	}
	else
	{
		BaseRenderer->ChangeAnimation("effect_Right");
	}

	BaseCollision->SetPosition({ GetDir().iX() * 100,0 });
	BaseRenderer->SetPosition({ GetDir().iX() * 105,-35 });

	Collisiongather(_DeltaTime);

}

void ABase::BeginPlay()
{
	AActor::BeginPlay();
	{
		BaseRenderer = CreateImageRenderer(ERenderOrder::Base); // 이미지 랜더 생성
		BaseRenderer->SetImage("effect_Right.png"); // 이미지 Set
		BaseRenderer->SetActive(true, 0.1f);
		BaseRenderer->SetTransform({ {0,0}, {32*5, 32*4} }); // 랜더의 위치 크기 
	}
	//150//120
	{
		BaseCollision = CreateCollision(ECollisionOrder::AllStar);
		BaseCollision->SetScale({ 70,70 });

		BaseCollision->SetColType(ECollisionType::Rect);
	}

	BaseRenderer->CreateAnimation("effect_Right", "effect_Right.png", 0,5, 0.1f, true);
	BaseRenderer->CreateAnimation("effect_Left", "effect_Left.png", 0,5, 0.1f, true);
	BaseRenderer->ChangeAnimation("effect_Right");
	
	Destroy(0.45f);
}

void ABase::Collisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == BaseCollision->CollisionCheck(ECollisionOrder::Monster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("터져야겠지....");
		}
		Monster->AddActorLocation(GetDir() * FVector::Left * Power * _DeltaTime);
		Monster->SetEatState(true);
		Monster->SetBaseOnOff(true);
		SetModeName("Base_");

		Destroy(0.1f);
	}
	else if (true == BaseCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("터져야겠지....");
		}
		Monster->AddActorLocation(GetDir() * FVector::Left * Power * _DeltaTime);
		Monster->SetEatState(true);
		Monster->SetBaseOnOff(true);

		SetModeName("Ice_");

		Destroy(0.1f);
	}
	else if (true == BaseCollision->CollisionCheck(ECollisionOrder::FireMonster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Fire* Monster = dynamic_cast<AMonster_Fire*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("터져야겠지....");
		}
		Monster->AddActorLocation(GetDir() * FVector::Left * Power * _DeltaTime);
		Monster->SetEatState(true);
		Monster->SetBaseOnOff(true);

		SetModeName("Fire_");

		Destroy(0.1f);
	}
	else if (true == BaseCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Sir* Monster = dynamic_cast<AMonster_Sir*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("터져야겠지....");
		}
		Monster->AddActorLocation(GetDir() * FVector::Left * Power * _DeltaTime);
		Monster->SetEatState(true);
		Monster->SetBaseOnOff(true);

		SetModeName("Sir_");

		Destroy(0.1f);
	}
	else if (true == BaseCollision->CollisionCheck(ECollisionOrder::MikeMonster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Mike* Monster = dynamic_cast<AMonster_Mike*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("터져야겠지....");
		}
		Monster->AddActorLocation(GetDir() * FVector::Left * Power * _DeltaTime);
		Monster->SetEatState(true);
		Monster->SetBaseOnOff(true);
		SetModeName("Mike_");

		Destroy(0.1f);
	}
}
