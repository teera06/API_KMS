#include "Base.h"
#include <EngineCore\EngineCore.h>
#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
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



	std::vector<UCollision*> Result;
	if (true == BaseCollision->CollisionCheck(ECollisionOrder::Monster, Result))
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
		Monster->AddActorLocation(GetDir() * FVector::Left * 500.0f* _DeltaTime);
		Monster->SetEatState(true);
		Monster->Destroy(0.3f);
		
		Destroy(0.1f);
	}else if(true == BaseCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
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
		Monster->AddActorLocation(GetDir() * FVector::Left * 500.0f * _DeltaTime);
		Monster->SetEatState(true);
		//SetMode(EAMode::Ice);
		SetModeName("Ice_");

		Monster->Destroy(0.3f);

		Destroy(0.1f);
	}
}

void ABase::BeginPlay()
{
	AActor::BeginPlay();
	{
		BaseRenderer = CreateImageRenderer(ERenderOrder::Base); // 이미지 랜더 생성
		BaseRenderer->SetImage("effect_Right.png"); // 이미지 Set
		BaseRenderer->SetActive(true, 0.1f);
		BaseRenderer->SetTransform({ {0,0}, {150, 120} }); // 랜더의 위치 크기 
	}
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
