#include "pengi_Ice.h"
#include "ModeEnum.h"

Apengi_Ice::Apengi_Ice()
{
}

Apengi_Ice::~Apengi_Ice()
{
}

void Apengi_Ice::IceState()
{
	scale = 2;
	PengiRenderer->ChangeAnimation("MonsterIce");
	PengiRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	IsIce = true;
}

void Apengi_Ice::BeginPlay()
{
	AActor::BeginPlay();

	scale = 5;
	{
		PengiRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		PengiRenderer->SetImage("pengi_Right.png"); // 이미지 Set
		PengiRenderer->SetTransform({ {0,0}, {64*scale, 64*scale} }); // 랜더의 위치 크기 
	}

	{
		PengiCollision = CreateCollision(ECollisionOrder::iceMonster);
		PengiCollision->SetScale({ 70, 70 });
		PengiCollision->SetColType(ECollisionType::Rect);
	}

	AniCreate();
	PengiRenderer->ChangeAnimation("Pengi_Right");
}

void Apengi_Ice::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // 중력 작용

	FVector PlayerPos = Player->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector MosterXL = MonsterPos + FVector::Left * sight; // 몬스터 왼쪽 플레이어 인식 시야 X축
	FVector MosterXR = MonsterPos + FVector::Right * sight; // 몬스터 오른쪽 플레이어 인식 시야 X축

	FVector PlayerX = PlayerPos * FVector::Right; // 플레이어 위치 X축

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 

	FVector MovePos = FVector::Zero;


	if (MosterXL.iX() < PlayerX.iX() && MosterXR.iX() > PlayerX.iX()) // 몬스터 시야에 포착된 경우 X축 기준 왼쪽, 오른쪽
	{
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // 왼쪽 방향
		{
			PengiRenderer->ChangeAnimation("Pengi_Left");
			checkX = -30;
		}
		else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // 오른쪽 방향
			PengiRenderer->ChangeAnimation("Pengi_Right");
			checkX = 30;
		}
		MoveSpeed = 50.0f;
		MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // 몬스터가 플레이어의 Y축도 인식할 수 있으니 FVector::Right 를 곱해 X축만 추격
	}
	else { // 플레이어가 몬스터 시야 밖인 경우 몬스터 행동강령
		BaseMove(_DeltaTime);
	}


	// 콜리전 
	std::vector<UCollision*> Result;
	if (true == PengiCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == false)
	{
		PengiRenderer->SetAlpha(0.5f);
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
	else if ((true == PengiCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == true)) {
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("터져야겠지....");
		}

		if (MonsterDirNormal.iX() == -1)
		{

			IceMove = FVector::Right * IceSpeed * _DeltaTime;

		}
		else {

			IceMove = FVector::Left * IceSpeed * _DeltaTime;
		}
	}


	Color8Bit ColorR = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + checkX, GetActorLocation().iY() - 30, Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		if (true == IsIce)
		{
			IceMove = FVector::Zero;
			Destroy();
		}
		else {
			MovePos = FVector::Zero;
		}

	}

	if (IsIce == false)
	{
		AddActorLocation(MovePos);
	}
	else {
		AddActorLocation(IceMove);
	}
}

void Apengi_Ice::AniCreate()
{
	PengiRenderer->CreateAnimation("Idel_Right", "Pengi_Right.png", 0, 0, 0.3f, true); // 걷기
	PengiRenderer->CreateAnimation("Idel_Left", "Pengi_Left.png", 0, 0, 0.3f, true); // 걷기
	// 기본 걷는 모션
	PengiRenderer->CreateAnimation("Pengi_Right", "Pengi_Right.png", 1, 3, 0.3f, true); // 걷기
	PengiRenderer->CreateAnimation("Pengi_Left", "Pengi_Left.png", 1, 3, 0.3f, true); // 걷기
	PengiRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false);
}

void Apengi_Ice::BaseMove(float _DeltaTime)
{
	FVector Move = FVector::Zero;

	--Value;
	if (0 >= Value)
	{
		DirMonster.X *= -1;
		Value = TurnValue;
	}
	else
	{
		if (DirMonster.iX() == -1 && IsIce == false)
		{
			PengiRenderer->ChangeAnimation("Pengi_Left");
			checkX = -30;
		}
		else if (DirMonster.iX() == 1 && IsIce == false) {
			PengiRenderer->ChangeAnimation("Pengi_Right");
			checkX = 30;
		}
		Color8Bit ColorR = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + checkX, GetActorLocation().iY() - 30, Color8Bit::RedA);
		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			if (true == IsIce)
			{
				IceMove = FVector::Zero;
				Destroy();
			}
			else {
				DirMonster.X *= -1;
			}
		}
		else {
			MoveSpeed = 30.0f;
			Move += DirMonster * _DeltaTime * MoveSpeed;
		}

		if (true == IsIce)
		{
			Move = FVector::Zero;
		}
		AddActorLocation(Move);
	}
}
