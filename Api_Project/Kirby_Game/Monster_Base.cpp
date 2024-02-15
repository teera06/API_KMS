#include "Monster_Base.h"
#include "ModeEnum.h"

AMonster_Base::AMonster_Base()
{
}

AMonster_Base::~AMonster_Base()
{
}

void AMonster_Base::BeginPlay()
{
	AActor::BeginPlay();

	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("Monster_Right.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,0}, {330, 330} }); // 랜더의 위치 크기 
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::Monster);
		MonsterCollision->SetScale({ 70, 70 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	AniCreate();

	MonsterRenderer->ChangeAnimation("Monster_Left");
}

void AMonster_Base::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime));

	FVector PlayerPos = Player->GetActorLocation();
	FVector MonsterPos = GetActorLocation();

	FVector MonsterDir = PlayerPos - MonsterPos;
	FVector MonsterDirNormal = MonsterDir.Normalize2DReturn();

	if (MonsterDirNormal.iX() == -1)
	{
		MonsterRenderer->ChangeAnimation("Monster_Left");
		AddActorLocation(MonsterDirNormal * _DeltaTime * 10.0f);
	}
	else {
		MonsterRenderer->ChangeAnimation("Monster_Right");
		AddActorLocation(MonsterDirNormal * _DeltaTime * 10.0f);
	}


	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		int a = 0;
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("터져야겠지....");
		}

		Destroy();
	}
}

void AMonster_Base::AniCreate()
{
	// 기본 걷는 모션
	MonsterRenderer->CreateAnimation("Monster_Right", "Monster_Right.png", 0, 4, 0.2f, true); // 걷기
	MonsterRenderer->CreateAnimation("Monster_Left", "Monster_Left.png", 0, 4, 0.2f, true); // 걷기
}
