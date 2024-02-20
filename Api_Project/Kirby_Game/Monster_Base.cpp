#include "Monster_Base.h"
#include "ModeEnum.h"

AMonster_Base::AMonster_Base()
{
}

AMonster_Base::~AMonster_Base()
{
}

void AMonster_Base::IceState()
{
	scale = 2;
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64*scale, 64*scale} }); // 랜더의 위치 크기 
	ice = true;
}

void AMonster_Base::BeginPlay()
{
	AActor::BeginPlay();

	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("Monster_Right.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,1}, {64* scale, 64* scale} }); // 랜더의 위치 크기 
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
	
	FVector MovePos = FVector::Zero;
	int check = 0;
	
	MovePos += MonsterDirNormal * _DeltaTime * 40.0f * FVector::Right;

	if (MonsterDirNormal.iX() == -1 && ice==false)
	{
		MonsterRenderer->ChangeAnimation("Monster_Left");
		check = -20;
	}
	else if(MonsterDirNormal.iX() == 1 && ice == false){
		MonsterRenderer->ChangeAnimation("Monster_Right");
		check = 20;
	}

	Color8Bit ColorR = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX()+check, GetActorLocation().iY() - 30, Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		MovePos = FVector::Zero;
	}

	if (ice == false)
	{
		AddActorLocation(MovePos);
	}


	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && ice == false)
	{
		MonsterRenderer->SetAlpha(0.5f);
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("터져야겠지....");
		}
		Destroy();
	}
	else if((true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && ice == true)){
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("터져야겠지....");
		}

		if (MonsterDirNormal.iX() == -1)
		{
			AddActorLocation(FVector::Right*1000.f * _DeltaTime);
		}
		else {
			AddActorLocation(FVector::Left * 1000.f * _DeltaTime);
		}
	}
}

void AMonster_Base::AniCreate()
{
	// 기본 걷는 모션
	MonsterRenderer->CreateAnimation("Monster_Right", "Monster_Right.png", 1, 3, 0.3f, true); // 걷기
	MonsterRenderer->CreateAnimation("Monster_Left", "Monster_Left.png", 1, 3, 0.3f, true); // 걷기
	MonsterRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false);
}
