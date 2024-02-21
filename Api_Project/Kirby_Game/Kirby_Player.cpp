#include "Kirby_Player.h"
#include <EnginePlatform\EngineInput.h> // Level1
#include <EngineCore/EngineCore.h>

#include "AllStar.h"
#include "Fire.h"
#include "Base.h"
#include "Ice.h"
AKirby_Player* AKirby_Player::MainPlayer = nullptr;

AKirby_Player* AKirby_Player::GetMainPlayer()
{
	return MainPlayer;
}

AKirby_Player::AKirby_Player()
{
}

AKirby_Player::~AKirby_Player()
{
	Destroy(0.0f);
}

void AKirby_Player::CamYMove()
{
	FVector CamMoveY;

	if (CurY.iY() != GetActorLocation().iY())
	{
		if (CurY.iY() > GetActorLocation().iY())
		{
			CamMoveY = (FVector::Down * CurY) - (FVector::Down * GetActorLocation());
			CamMoveY = CamMoveY * FVector::Up;
			GetWorld()->AddCameraPos(CamMoveY * 0.59f);
		}
		else if (CurY.iY() < GetActorLocation().iY()) {
			CamMoveY = (FVector::Down * GetActorLocation()) - (FVector::Down * CurY);
			CamMoveY = CamMoveY * FVector::Down;
			GetWorld()->AddCameraPos(CamMoveY * 0.59f);
		}
		CurY = GetActorLocation();
	}
	
}

void AKirby_Player::BeginPlay() // 실행했을때 준비되어야 할것들 Set
{
	AActor::BeginPlay();

	MainPlayer = this;
	scale = 3;
	KirbyRenderer = CreateImageRenderer(ERenderOrder::kirby); // 이미지 랜더 생성
	KirbyRenderer->SetImage("kirby_Right.png"); // 이미지 Set
	KirbyRenderer->SetTransform({ {0,0}, {64*scale, 64*scale} }); // 랜더의 위치 크기 

	AniCreate(); // 애니메이션 종합 관리

	// 일반적으로는 충돌이라는 시점을 따로둡니다.
	{
		KirbyCollision = CreateCollision(ECollisionOrder::kirby);
		KirbyCollision->SetScale({ 70, 70 });
		KirbyCollision->SetColType(ECollisionType::Rect);
	}


	GetWorld()->SetCameraPos({ GetTransform().GetPosition().iX(),340}); // 카메라 위치
	StateAniChange(EActorState::Idle); // 시작 애니메이션

	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> 이전 코드
}

// 커비 움직임 업데이트
void AKirby_Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	StateUpdate(_DeltaTime);
}

void AKirby_Player::AniCreate()
{
	// (오른쪽, 왼쪽)
	// (1) Base
	// 기본 서있는 모션
	KirbyRenderer->CreateAnimation("Base_Idle_Right", "kirby_Right.png", 0, 1, 0.5f, true); // 오른쪽 서 있기
	KirbyRenderer->CreateAnimation("Base_Idle_Left", "kirby_Left.png", 0, 1, 0.5f, true); // 왼쪽 서있기

	// 기본 걷는 모션
	KirbyRenderer->CreateAnimation("Base_Walk_Right", "kirby_Right.png", 10, 19, 0.1f, true); // 걷기
	KirbyRenderer->CreateAnimation("Base_Walk_Left", "kirby_Left.png", 10, 19, 0.1f, true); // 걷기

	// 기본 뛰는 모션
	KirbyRenderer->CreateAnimation("Base_run_Right", "kirby_Right.png", 20, 27, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_run_Left", "kirby_Left.png", 20, 27, 0.1f, true);

	// 기본 점프 모션
	KirbyRenderer->CreateAnimation("Base_Jump_Right", "kirby_Right.png", 38, 51, 0.09f, true);
	KirbyRenderer->CreateAnimation("Base_Jump_Left", "kirby_Left.png", 38, 51, 0.09f, true);

	// 기본 나는 모션
	KirbyRenderer->CreateAnimation("Base_FlyReady_Right", "kirby_Right.png", 53, 57, 0.08f, false);
	KirbyRenderer->CreateAnimation("Base_FlyReady_Left", "kirby_Left.png", 53, 57, 0.08f, false);
	KirbyRenderer->CreateAnimation("Base_Fly_Right", "kirby_Right.png", 58, 65, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_Fly_Left", "kirby_Left.png", 58, 65, 0.1f, true);

	// 떨어지는 모션
	KirbyRenderer->CreateAnimation("Base_fall_Right", "kirby_Right.png", { 66,67,35,36,37 }, 0.1f, false);
	KirbyRenderer->CreateAnimation("Base_fall_Left", "kirby_Left.png", { 66,67,35,36,37 }, 0.1f, false);
	// 기본 숙이기 
	KirbyRenderer->CreateAnimation("Base_HeadDown_Right", "kirby_Right.png", 2, 3, 0.5f, true);
	KirbyRenderer->CreateAnimation("Base_HeadDown_Left", "kirby_Left.png", 2, 3, 0.5f, true);

	// ---기본에서만 가능한 모션들----
	// Heavy 모드 Idle
	KirbyRenderer->CreateAnimation("Base_HeavyIdle_Right", "kirby2_Right.png", 19, 20, 0.5f, true);
	KirbyRenderer->CreateAnimation("Base_HeavyIdle_Left", "kirby2_Left.png", 19, 20, 0.5f, true);

	// Heavy모드 Move
	KirbyRenderer->CreateAnimation("Base_HeavyMove_Right", "kirby2_Right.png", 23, 33, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_HeavyMove_Left", "kirby2_Left.png", 23, 33, 0.1f, true);

	// Heavy모드 Move
	KirbyRenderer->CreateAnimation("Base_HeavyJump_Right", "kirby2_Right.png", 34, 41, 0.09f, true);
	KirbyRenderer->CreateAnimation("Base_HeavyJump_Left", "kirby2_Left.png", 34, 41, 0.09f, true);
	


	// 기본 흡수 
	KirbyRenderer->CreateAnimation("Base_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
	KirbyRenderer->CreateAnimation("Base_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);
	
	// 모든 커비모드에서 사용 가능한 애니메이션
	KirbyRenderer->CreateAnimation("AllAttack_Right", "kirby2_Right.png", 42, 53, 0.03f, false);
	KirbyRenderer->CreateAnimation("AllAttack_Left", "kirby2_Left.png", 42, 53, 0.03f, false);

	//-- 아이스 커비
	KirbyRenderer->CreateAnimation("Ice_Idle_Right", "Ice_Right.png", 0, 1, 0.5f, true); // 오른쪽 서 있기
	KirbyRenderer->CreateAnimation("Ice_Idle_Left", "Ice_Left.png", 0, 1, 0.5f, true); // 왼쪽 서있기

	// 아이스 걷는 모션
	KirbyRenderer->CreateAnimation("Ice_Walk_Right", "Ice_Right.png", 32, 39, 0.1f, true); // 걷기
	KirbyRenderer->CreateAnimation("Ice_Walk_Left", "Ice_Left.png", 32, 39, 0.1f, true); // 걷기

	// 아이스 뛰는 모션
	KirbyRenderer->CreateAnimation("Ice_run_Right", "Ice_Right.png", 42, 49, 0.1f, true);
	KirbyRenderer->CreateAnimation("Ice_run_Left", "Ice_Left.png", 42, 49, 0.1f, true);

	// 아이스 점프 모션
	KirbyRenderer->CreateAnimation("Ice_Jump_Right", "Ice_Right.png", 80, 90, 0.12f, true);
	KirbyRenderer->CreateAnimation("Ice_Jump_Left", "Ice_Left.png",80, 90, 0.12f, true);

	// 아이스 나는 모션
	KirbyRenderer->CreateAnimation("Ice_FlyReady_Right", "Ice_Right.png", 54, 58, 0.08f, false);
	KirbyRenderer->CreateAnimation("Ice_FlyReady_Left", "Ice_Left.png", 54, 58, 0.08f, false);
	KirbyRenderer->CreateAnimation("Ice_Fly_Right", "Ice_Right.png", 59, 74, 0.08f, true);
	KirbyRenderer->CreateAnimation("Ice_Fly_Left", "Ice_Left.png", 59, 74, 0.08f, true);

	// 아이스 떨어지는 모션
	KirbyRenderer->CreateAnimation("Ice_fall_Right", "Ice_Right.png",75,79, 0.1f, false);
	KirbyRenderer->CreateAnimation("Ice_fall_Left", "Ice_Left.png", 75,79, 0.1f, false);
	// 아이스 숙이기 
	KirbyRenderer->CreateAnimation("Ice_HeadDown_Right", "Ice_Right.png",10, 11, 0.5f, true);
	KirbyRenderer->CreateAnimation("Ice_HeadDown_Left", "Ice_Left.png", 10, 11, 0.5f, true);

	// 아이스 공격
	KirbyRenderer->CreateAnimation("Ice_IceAttack_Right", "Ice_Right.png", 94, 103, 0.08f, true);
	KirbyRenderer->CreateAnimation("Ice_IceAttack_Left", "Ice_Left.png", 94, 103, 0.08f, true);
	// 기본 흡수 -> 기본에서 아이스 중간 이미지 
	KirbyRenderer->CreateAnimation("Ice_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
	KirbyRenderer->CreateAnimation("Ice_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);
}



void AKirby_Player::CalGravityVector(float _DeltaTime)
{
	GravityVector += GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime);
	Color8Bit Color = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (Color == Color8Bit(255, 0, 0, 0))
	{
		GravityVector = FVector::Zero;
	}
}

void AKirby_Player::MoveLastMoveVector(float _DeltaTime, const FVector& _MovePos)
{
	// 제로로 만들어서 초기화 시킨다.
	PlayMove = FVector::Zero;
	
	PlayMove = PlayMove + JumpVector;

	if (false == FlyState)
	{
		PlayMove = PlayMove + GravityVector;
	}
	else {
		GravityVector = FVector::Zero;
	}

	FVector MovePos = _MovePos;
	
	FVector CheckPos = GetActorLocation();
	FVector CarCheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= checkposX;
		CarCheckPos.X -= 3.0f;// 3으로 우선 고정
		break;
	case EActorDir::Right:
		CheckPos.X += checkposX;
		CarCheckPos.X += 3.0f;
		break;
	default:
		break;
	}
	CheckPos.Y -= checkposY;
	CarCheckPos.Y -= checkposY;
	Color8Bit ColorR = ActorCommon::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::RedA);
	Color8Bit ColorG = ActorCommon::ColMapImage->GetColor(CarCheckPos.iX(), CarCheckPos.iY(), Color8Bit::GreenA);
	Color8Bit ColorB = ActorCommon::ColMapImage->GetColor(CarCheckPos.iX(), CarCheckPos.iY(), Color8Bit::BlueA);
	Color8Bit ColorM = ActorCommon::ColMapImage->GetColor(CarCheckPos.iX(), CarCheckPos.iY(), Color8Bit::MagentaA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		MovePos = FVector::Zero;
	}

	AddActorLocation(MovePos + (PlayMove * _DeltaTime));
	if (ColorG != Color8Bit(0, 255, 0, 0) && ColorB != Color8Bit(0, 0, 255, 0) && ColorM != Color8Bit(255, 0, 255, 0))
	{

	
		GetWorld()->AddCameraPos((MovePos * FVector::Right) + CamstopMove);

		CamstopMove = FVector::Zero;

	}
	else {

		CamstopMove += (MovePos * FVector::Right);
	}
}



void AKirby_Player::MoveUpdate(float _DeltaTime, const FVector& _MovePos)
{
	CalGravityVector(_DeltaTime);
	MoveLastMoveVector(_DeltaTime, _MovePos);
}

//----------------------------------------------------------------------------------------------------

void AKirby_Player::DirCheck() // 커비 왼쪽 오른쪽 체크
{
	EActorDir Dir = DirState;
	if (UEngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
	}

	if (Dir != DirState && false==SkillOnOff)
	{
		DirState = Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		KirbyRenderer->ChangeAnimation(Name, true,KirbyRenderer->GetCurAnimationFrame(), KirbyRenderer->GetCurAnimationTime());
	}
}

std::string AKirby_Player::GetAnimationName(std::string_view _Name)
{
	std::string DirName = "";

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}

	CurAnimationName = _Name;

	if (std::string(_Name) == "AllAttack") // AllAttack은 모든 커비모드에서 사용 가능하기에
	{// 앞에 GetModeName없이 AllAttack 문자열과 방향만 리턴
		return std::string(_Name) + DirName;
	}
	return std::string(GetModeName()) + std::string(_Name) + DirName;
}

//-------------------------------------------------------------------------------

void AKirby_Player::StateAniChange(EActorState _State)
{
	// 이전상태와 지금 상태가 같지 않아
	// 이전에는 move 지금은 Idle

	if (std::string(GetModeName()) != "Base_")
	{
		if (std::string(GetModeName()) == "Ice_")
		{
			SetMode(EAMode::Ice);
		}
		else if (std::string(GetModeName()) == "Sword_")
		{
			SetMode(EAMode::Sword);
		}
	}
	

	if (State != _State)
	{
		switch (_State)
		{
		case EActorState::Idle:
			
			switch (KirbyMode)
			{
			case EAMode::Base:
				if (true == EatState && KirbyMode == EAMode::Base) // Eat상태 (먹은상태) 는 커비가 기본 모드일때만 체크후 변경한다.
				{
					HeavyIdleStart(); // Heavy는 기본 형태의 커비에서만 가능한 애니메이션
				}
				else
				{
					IdleStart();
				}
				break;
			case EAMode::Ice:
				IdleStart();
				break;
			case EAMode::Mike:
				break;
			case EAMode::Sword:
				break;
			case EAMode::Hammer:
				break;
			default:
				break;
			}
			break;
		case EActorState::Walk:
			if (true == EatState && KirbyMode == EAMode::Base) // 동일
			{
				checkSpeed = HeavyWalkSpeed;
				HeavyMoveStart();
			}
			else
			{
				checkSpeed = WalkSpeed;
				WalkStart();;
			}
			break;
		case EActorState::Jump:
			if (true == EatState && KirbyMode == EAMode::Base) // 동일
			{
				JumpVector = JumpPowerHeavy;
				HeavyJumpStart();
			}
			else
			{
				JumpVector = JumpPowerBase;
				JumpStart();
			}
			break;
		case EActorState::FlyReady:
			FlyReadyStart();
			break;
		case EActorState::Fly:
			checkSpeed = FlySpeed;
			FlyStart();
			break;
		case EActorState::fall:
			FlyFallStart();
			break;
		case EActorState::Run:
			if (true == EatState && KirbyMode == EAMode::Base) // 동일
			{
				checkSpeed = HeavyRunSpeed;
				HeavyMoveStart();
			}
			else
			{	
				checkSpeed = RunSpeed;
				RunStart();
			}
			break;
		case EActorState::Absorption:
			AbsorptionStart();
			break;
		case EActorState::IceAttack:
			IceAttackStart();
			break;
		case EActorState::HeadDown:
			HeadDownStart();
			break;
		case EActorState::All_Attack:
			AllAttackStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void AKirby_Player::StateUpdate(float _DeltaTime)
{
	switch (State) // 현재 상태별 진행해야하는 형태
	{
	case EActorState::CameraFreeMove: // 카메라 움직임 -> 테스트용
		CameraFreeMove(_DeltaTime);
		break;
	case EActorState::FreeMove: // 카메라, 캐릭터 자유롭게 이동 -> 테스트용
		FreeMove(_DeltaTime);
		break;
	case EActorState::Idle: // 서있기
		Idle(_DeltaTime);
		break;
	case EActorState::Walk: // 걷기
		Walk(_DeltaTime);
		break;
	case EActorState::Jump: // 점프
		Jump(_DeltaTime);
		break;
	case EActorState::Fly: // 날기
		Fly(_DeltaTime);
		break;
	case EActorState::FlyReady: // 날기
		FlyReady(_DeltaTime);
		break;
	case EActorState::fall: // 날기
		Flyfall(_DeltaTime);
		break;
	case EActorState::Run: // 달리기
		Run(_DeltaTime);
		break;
	case EActorState::Absorption: // 흡수
		ModeInputTick(_DeltaTime);
		break;
	case EActorState::IceAttack: // 흡수
		ModeInputTick(_DeltaTime);
		break;
	case EActorState::HeadDown: // 숙이기
		HeadDown(_DeltaTime);
		break;
	case EActorState::All_Attack: // 흡수 후 가능 -> 별 공격
		All_Attack(_DeltaTime);
		break;
	default:
		break;
	}
}


void AKirby_Player::CameraFreeMove(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * camSpeed);
		// AddActorLocation(FVector::Left * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * camSpeed);
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * _DeltaTime * camSpeed);
		// AddActorLocation(FVector::Up * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * _DeltaTime * camSpeed);
		// AddActorLocation(FVector::Down * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsDown('2'))
	{
		StateAniChange(EActorState::Idle);
	}
}

void AKirby_Player::FreeMove(float _DeltaTime)
{
	FVector MovePos;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * WalkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * WalkSpeed;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		MovePos += FVector::Up * _DeltaTime * WalkSpeed;
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		MovePos += FVector::Down * _DeltaTime * WalkSpeed;
	}

	AddActorLocation(MovePos);
	GetWorld()->AddCameraPos(MovePos);

	if (UEngineInput::IsDown('1'))
	{
		StateAniChange(EActorState::Idle);
	}
}

void AKirby_Player::Idle(float _DeltaTime)
{
	// 왼쪽 오른쪽도 안되고 있고.
	// 여기서는 정말
	// 가만히 있을때만 어떻게 할지 신경쓰면 됩니다.
	CurY = GetActorLocation();
	if (true == UEngineInput::IsDown('1'))
	{
		StateAniChange(EActorState::FreeMove);
		return;
	}

	if (true == UEngineInput::IsDown('2'))
	{
		StateAniChange(EActorState::CameraFreeMove);
		return;
	}


	if (
		true == UEngineInput::IsPress(VK_LEFT) ||
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		StateAniChange(EActorState::Walk);
		return;
	}

	if (
		true == UEngineInput::IsDown('S') 
		)
	{

		StateAniChange(EActorState::Jump);
		return;
	}

	if (
		true == UEngineInput::IsPress(VK_DOWN)
		)
	{
		StateAniChange(EActorState::HeadDown);
		return;
	}

	if (
		true == UEngineInput::IsPress('X') && false == EatState
		)
	{
		SkillOnOff = true;
		StateAniChange(EActorState::Absorption);
		ABase* NewBase = GetWorld()->SpawnActor<ABase>();
		NewBase->SetActorLocation(this->GetActorLocation());

		if (DirState == EActorDir::Left)
		{
			NewBase->SetDir(FVector::Left);
		}
		else {
			NewBase->SetDir(FVector::Right);
		}
		return;
	}
	else if(true == UEngineInput::IsPress('X') && KirbyMode==EAMode::Ice ){
		SkillOnOff = true;
		StateAniChange(EActorState::IceAttack);
		AIce* NewIce = GetWorld()->SpawnActor<AIce>();
		NewIce->SetActorLocation(this->GetActorLocation());

		if (DirState == EActorDir::Left)
		{
			NewIce->SetDir(FVector::Left);
		}
		else {
			NewIce->SetDir(FVector::Right);
		}
		return;
	}

	if (
		true == UEngineInput::IsDown('A') && true==EatState
		)
	{
		
		StateAniChange(EActorState::All_Attack);
		AAllStar* NewStar = GetWorld()->SpawnActor<AAllStar>();
		NewStar->SetActorLocation(this->GetActorLocation());

		if (DirState == EActorDir::Left)
		{
			NewStar->SetDir(FVector::Left);
		}
		else {
			NewStar->SetDir(FVector::Right);
		}
		return;
	}

	MoveUpdate(_DeltaTime);
}

void AKirby_Player::Jump(float _DeltaTime)
{
	DirCheck();
	FVector MovePos;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * checkSpeed * _DeltaTime;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * checkSpeed * _DeltaTime;
	}

	if (UEngineInput::IsDown('S'))
	{
		switch (KirbyMode)
		{
		case EAMode::Base:
			if (false == EatState)
			{
				StateAniChange(EActorState::FlyReady);
				return;
			}
			break;
		default:
			StateAniChange(EActorState::FlyReady);
			return;
			break;
		}
	}


	MoveUpdate(_DeltaTime,MovePos);

	CamYMove();
	
	Color8Bit Color = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (Color == Color8Bit(255, 0, 0, 0))
	{

		
		JumpVector = FVector::Zero;
		StateAniChange(EActorState::Idle);
		return;
	}
}

void AKirby_Player::FlyReady(float _DeltaTime)
{
	DirCheck();
	FlyState = true;
	JumpVector = FVector::Zero;
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		StateAniChange(EActorState::Fly);
		return;
	}
}

void AKirby_Player::Fly(float _DeltaTime)
{
	DirCheck();
	if (UEngineInput::IsDown('X'))
	{
		FlyState = false;
		StateAniChange(EActorState::fall);
		return;
	}

	FVector MovePos= FVector::Zero;
	
	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		MovePos += FVector::Up * _DeltaTime * 100.0f;
	}
	else {
		MovePos += FVector::Down * _DeltaTime * 100.0f;
	}

	
	

	MoveUpdate(_DeltaTime, MovePos);
	
	Color8Bit Color1 = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY()-15, Color8Bit::MagentaA);
	if (Color1 == Color8Bit(255, 0, 255, 0) )
	{
		FlyState = false;
		StateAniChange(EActorState::fall);
	    return;
	}

	Color8Bit Color = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (Color == Color8Bit(255, 0, 0, 0))
	{

		FlyState = false;
		StateAniChange(EActorState::fall);
		return;
	}
	
	
}

void AKirby_Player::Flyfall(float _DeltaTime)
{
	
	DirCheck();
	
	FVector MovePos = FVector::Zero;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * checkSpeed;
	}

	MoveUpdate(_DeltaTime, MovePos);

	Color8Bit Color = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (Color == Color8Bit(255, 0, 0, 0))
	{
		JumpVector = FVector::Zero;
		StateAniChange(EActorState::Idle);
		CamYMove();
		return;
	}


}



void AKirby_Player::HeadDown(float _DeltaTime)
{
	DirCheck();

	if (true == UEngineInput::IsFree(VK_DOWN))
	{
		StateAniChange(EActorState::Idle);
		return;
	}


	MoveUpdate(_DeltaTime);
}

void AKirby_Player::Walk(float _DeltaTime)
{
	DirCheck();
	

	if (true == UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		StateAniChange(EActorState::Idle);
		return;
	}

	FVector MovePos = FVector::Zero;
	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime* checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime*checkSpeed;
	}

	if (UEngineInput::IsPress(VK_SHIFT))
	{
		StateAniChange(EActorState::Run);
		return;
	}

	if (true == UEngineInput::IsDown('S'))
	{
		
		StateAniChange(EActorState::Jump);
		return;
	}


	MoveUpdate(_DeltaTime, MovePos);

	CamYMove();
}

void AKirby_Player::Run(float _DeltaTime)
{
	DirCheck();
	

	if (UEngineInput::IsFree(VK_SHIFT))
	{
		StateAniChange(EActorState::Walk);
		return;
	}
	else if (UEngineInput::IsPress(VK_SHIFT) && UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		StateAniChange(EActorState::Idle);
		return;
	}

	FVector MovePos = FVector::Zero;
	if (UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsPress(VK_SHIFT))
	{
		MovePos += FVector::Left * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT) && UEngineInput::IsPress(VK_SHIFT))
	{
		MovePos += FVector::Right * _DeltaTime * checkSpeed;
	}

	MoveUpdate(_DeltaTime, MovePos);

	CamYMove();
}

void AKirby_Player::Absorption(float _DeltaTime)
{
	
	DirCheck();
	
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		SkillOnOff = false;
		StateAniChange(EActorState::Idle);
		return;
	}


	
	MoveUpdate(_DeltaTime);
}

void AKirby_Player::All_Attack(float _DeltaTime)
{
	DirCheck();
	
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		EatState = false;
		SetModeName("Base_");
		SetMode(EAMode::Base);
		StateAniChange(EActorState::Idle);
		return;
	}

	MoveUpdate(_DeltaTime);
}

void AKirby_Player::IdleStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Idle"));
}

void AKirby_Player::HeavyIdleStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("HeavyIdle"));
}

void AKirby_Player::WalkStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Walk"));
}

void AKirby_Player::HeavyMoveStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("HeavyMove"));
	
}

void AKirby_Player::JumpStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Jump"));
}

void AKirby_Player::HeavyJumpStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("HeavyJump"));
}

void AKirby_Player::FlyReadyStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("FlyReady"));
}

void AKirby_Player::FlyStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Fly"));
}

void AKirby_Player::FlyFallStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("fall"));
}

void AKirby_Player::RunStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Run"));
	
}

void AKirby_Player::AbsorptionStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Absorption"));
}

void AKirby_Player::IceAttackStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("IceAttack"));
}

void AKirby_Player::HeadDownStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("HeadDown"));
}

void AKirby_Player::AllAttackStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("AllAttack"));
}

//------------------------------------------------------------------------------

void AKirby_Player::ModeInputTick(float _DeltaTime) // 커비 속성 별 할 것들
{
	switch (KirbyMode)
	{
	case EAMode::Base:
		//SetNamechange("Base_");
		Absorption(_DeltaTime);
		break;
	case EAMode::Ice:
		IceKirby(_DeltaTime);
		break;
	case EAMode::Mike:
		break;
	case EAMode::Sword:
		break;
	case EAMode::Hammer:
		break;
	default:
		break;
	}
}

void AKirby_Player::FireKirby()
{
	
}

void AKirby_Player::IceKirby(float _DeltaTime)
{
	DirCheck();

	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		SkillOnOff = false;
		StateAniChange(EActorState::Idle);
		return;
	}



	MoveUpdate(_DeltaTime);
}


