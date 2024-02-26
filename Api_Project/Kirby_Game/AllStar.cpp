#include "AllStar.h"
#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"

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

		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // 죽는 애니메이션
		//FVector DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
		Monster->SetIsDie(true);
		//Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		Destroy();
	}else if (true == AllStarCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Apengi_Ice* iceMonster = dynamic_cast<Apengi_Ice*>(Ptr);


		if (nullptr == iceMonster)
		{
			MsgBoxAssert("터져야겠지....");
		}

		iceMonster->Destroy();
		Destroy();
	}

	Color8Bit ColorR = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY()-20, Color8Bit::RedA);

	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		Destroy();
	}

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
