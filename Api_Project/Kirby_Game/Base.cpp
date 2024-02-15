#include "Base.h"
#include <EngineCore\EngineCore.h>
#include "ModeEnum.h"
#include "Monster_Base.h"
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

	BaseCollision->SetPosition({ GetDir().iX() * 100,0 });
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
		Monster->SetEatState(true);
		Monster->Destroy();
		
		Destroy();
	}
}

void ABase::BeginPlay()
{
	AActor::BeginPlay();
	{
		//Renderer->SetImage("Fire.png");
		//Renderer->SetTransform({ {0,0}, {100, 100} });
	}

	{
		BaseCollision = CreateCollision(ECollisionOrder::AllStar);
		BaseCollision->SetScale({ 80,80 });

		BaseCollision->SetColType(ECollisionType::Rect);
	}
	
	Destroy(1.0f);
}
