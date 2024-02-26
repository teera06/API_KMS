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
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	IsIce = true;
}

void Apengi_Ice::BeginPlay()
{
	AActor::BeginPlay();

	scale = 5;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		MonsterRenderer->SetImage("pengi_Right.png"); // 이미지 Set
		MonsterRenderer->SetTransform({ {0,0}, {64*scale, 64*scale} }); // 랜더의 위치 크기 
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::iceMonster);
		MonsterCollision->SetScale({ 70, 70 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	AniCreate();
	MonsterRenderer->ChangeAnimation("Idle_Left");
}

void Apengi_Ice::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (false == IsDie) // Destroy(0.3f); -> 조건없이 계속 move업데이트 되면서 0.3f도 똑같이 유지 (한번만 실행해야함)
	{
		MoveUpdate(_DeltaTime);
	}
	else { // IsDIe가 true이면 MoveUpdate는 연속 실행이 안됨 -> Destroy(0.3f) 작동
		AddActorLocation(DiePos); // 죽으면서 이동
	}
}

void Apengi_Ice::AniCreate()
{
	MonsterRenderer->CreateAnimation("Idle_Right", "Pengi_Right.png", 0, 0, 0.3f, true);  
	MonsterRenderer->CreateAnimation("Idle_Left", "Pengi_Left.png", 0, 0, 0.3f, true); 
	MonsterRenderer->CreateAnimation("Move_Right", "Pengi_Right.png", 1, 3, 0.3f, true); 
	MonsterRenderer->CreateAnimation("Move_Left", "Pengi_Left.png", 1, 3, 0.3f, true); 

	MonsterRenderer->CreateAnimation("die_Right", "Pengi_Left.png", 7, 8, 0.3f, true); // 죽음 
	MonsterRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false); // 얼음
}

void Apengi_Ice::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // 중력 작용

	FVector PlayerPos = MainPlayer->GetActorLocation();  // 플레이어 위치
	FVector MonsterPos = GetActorLocation(); // 몬스터 위치

	FVector MosterXL = MonsterPos + FVector::Left * sight; // 몬스터 왼쪽 플레이어 인식 시야 X축
	FVector MosterXR = MonsterPos + FVector::Right * sight; // 몬스터 오른쪽 플레이어 인식 시야 X축

	FVector PlayerX = PlayerPos * FVector::Right; // 플레이어 위치 X축

	FVector MonsterDir = PlayerPos - MonsterPos; // 플레이어 위치 - 몬스터 위치 = 방향 ex) 몬스터가 플레이어에게 향하는 방향
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // 해당값을 정규화 

	FVector MovePos = FVector::Zero; // 플레이어 추격 시 이동

	if (MosterXL.iX() < PlayerX.iX() && MosterXR.iX() > PlayerX.iX()) // 몬스터 시야에 포착된 경우 X축 기준 왼쪽, 오른쪽
	{
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // 왼쪽 방향
		{
			MonsterRenderer->ChangeAnimation("Move_Left");
			WallX = -20;
		}
		else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // 오른쪽 방향
			MonsterRenderer->ChangeAnimation("Move_Right");
			WallX = 20;
		}
		MoveSpeed = 50.0f;
		MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // 몬스터가 플레이어의 Y축도 인식할 수 있으니 FVector::Right 를 곱해 X축만 추격
	}
	else { // 플레이어가 몬스터 시야 밖인 경우 몬스터 행동강령
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // 왼쪽 방향
		{
			MonsterRenderer->ChangeAnimation("Idle_Left");
			WallX = -20;

		}
		else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // 오른쪽 방향
			MonsterRenderer->ChangeAnimation("Idle_Right");
			WallX = 20;
		}
	}
	// 콜리전 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == false) // 얼지 않은 상태에서 플레이어와 충돌
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);

		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		// 방어코드
		if (nullptr == Player)
		{
			MsgBoxAssert("몬스터베이스 플레이어 인식 못함");
		}

		if (true == GetBaseOnOff()) // 흡수할 때의 몬스터 충돌 -> 몬스터는 플레이어와 충돌할 경우 바로 죽음
		{
			Destroy();
		}
		else {// 일반적인 플레이와의 충돌
			Player->Sethitstate(true); // 플레이어 충돌 체크
			Player->AddHP(-20);
			Player->HitStart(); // hit 상태 스타트
			Player->GetKirbyRender()->SetAlpha(0.5f);
			Player->GetKirbyCollision()->ActiveOff();
			MonsterRenderer->ChangeAnimation("die_Right"); // 죽는 애니메이션
			DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // 죽으면서 이동하는 위치 계산
			IsDie = true; // 죽음 체크
		}
	}
	else if ((true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == true)) { // 얼음 상태로 커비와 충돌 하는 경우
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("터져야겠지....");
		}

		// 얼음 상태 일때 움직임 계산
		if (MonsterDirNormal.iX() == -1) // 몬스터가 플레이어를 향하는 방향의 반대 방향으로 힘이 작용
		{

			IceMove = FVector::Right * IceSpeed * _DeltaTime;

		}
		else {

			IceMove = FVector::Left * IceSpeed * _DeltaTime;
		}
	}

	// 얼음 상태에서 벽에 충돌시 바로 삭제 -> 추후 이펙트 남길지 고민
	Color8Bit ColorR = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		if (true == IsIce)
		{
			IceMove = FVector::Zero;
			Destroy();
		}

		MovePos = FVector::Zero;
	}

	if (true == IsDie) // 죽으면
	{
		Destroy(0.3f); // 0.3f 뒤에 삭제
	}
	else {
		if (false == IsIce) // 죽거나, 얼음상태가 아니면 일반 행동
		{
			AddActorLocation(MovePos);
		}
		else {
			MovePos = FVector::Zero;
			AddActorLocation(IceMove);
		}
	}
}




