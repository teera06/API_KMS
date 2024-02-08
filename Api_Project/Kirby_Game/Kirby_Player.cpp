#include "Kirby_Player.h"
#include <EnginePlatform\EngineInput.h> // Level1

#include "Fire.h"
#include "Base.h"

AKirby_Player::AKirby_Player()
{
}

AKirby_Player::~AKirby_Player()
{
	Destroy(0.0f);
}

void AKirby_Player::BeginPlay() // ���������� �غ�Ǿ�� �Ұ͵� Set
{
	AActor::BeginPlay();

	// �÷��̾� 100, 100 => Actor
	// ��ü? 100, 100 - 50 => Renderer
	// ��ü? 100, 100 + 50 => Renderer

	//{
		//BodyRenderer = CreateImageRenderer(0);
		//BodyRenderer->SetPosition({ 0, 30 });
		//BodyRenderer->SetScale({ 8, 80 });
	//}

	KirbyRenderer = CreateImageRenderer(RenderOrder::kirby); // �̹��� ���� ����
	KirbyRenderer->SetImage("kirby_Right.png"); // �̹��� Set
	KirbyRenderer->SetTransform({ {0,0}, {210, 210} }); // ������ ��ġ ũ�� 

	AniCreate();

	GetWorld()->SetCameraPos({ 210,350 });

	KirbyRenderer->ChangeAnimation(std::string(GetAniNamechange()) + "Idle_Right");
	StateChange(ActorState::Idle);

	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�
}

// Ŀ�� ������ ������Ʈ
void AKirby_Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//ModeInputTick(); // Ŀ�� ��庰 �Է�Ű
	StateUpdate(_DeltaTime);
}

void AKirby_Player::AniCreate()
{
	// �⺻ ���ִ� �ִϸ��̼� (������, ����)
	KirbyRenderer->CreateAnimation("Base_Idle_Right", "kirby_Right.png", 0, 1, 0.5f, true); // ������ �� �ֱ�
	KirbyRenderer->CreateAnimation("Base_Idle_Left", "kirby_Left.png", 0, 1, 0.5f, true); // ���� ���ֱ�

	// �⺻ �ȴ� ��� (������, ����)
	KirbyRenderer->CreateAnimation("Base_Walk_Right", "kirby_Right.png", 10, 19, 0.1f, true); // �ȱ�
	KirbyRenderer->CreateAnimation("Base_Walk_Left", "kirby_Left.png", 10, 19, 0.1f, true); // �ȱ�

	// �⺻ �ٴ� ���
	KirbyRenderer->CreateAnimation("Base_run_Right", "kirby_Right.png", 20, 27, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_run_Left", "kirby_Left.png", 20, 27, 0.1f, true);

	KirbyRenderer->CreateAnimation("Base_jump_Right", "kirby_Right.png", 38, 52, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_jump_Left", "kirby_Left.png", 38, 52, 0.1f, true);

	KirbyRenderer->CreateAnimation("Base_jump2_Right", "kirby_Right.png", 53, 64, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_jump2_Left", "kirby_Left.png", 53, 64, 0.1f, true);

	// �⺻ ���̽� ����
	KirbyRenderer->CreateAnimation("Base_Absorption_Right", "kirby2_Right.png", 0, 18, 0.08f, true);
	KirbyRenderer->CreateAnimation("Base_Absorption_Left", "kirby2_Left.png", 0, 18, 0.08f, true);

	// ���̱� 
	KirbyRenderer->CreateAnimation("Base_HeadDown_Right", "kirby_Right.png", 2, 3, 0.5f, true);
	KirbyRenderer->CreateAnimation("Base_HeadDown_Left", "kirby_Left.png", 2, 3, 0.5f, true);

	KirbyRenderer->CreateAnimation("Base_HeavyIdle_Right", "kirby2_Right.png", 19, 20, 0.5f, true);
	KirbyRenderer->CreateAnimation("Base_HeavyIdle_Left", "kirby2_Left.png", 19, 20, 0.5f, true);

	KirbyRenderer->CreateAnimation("Base_HeavyMove_Right", "kirby2_Right.png", 23, 33, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_HeavyMove_Left", "kirby2_Left.png", 23, 33, 0.1f, true);
}

//----------------------------------------------------------------------------------------------------

void AKirby_Player::DirCheck() // Ŀ�� ���� ������ üũ
{
	EActorDir Dir = DirState;
	if (EngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
	}
	if (EngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
	}

	if (Dir != DirState)
	{
		DirState = Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		KirbyRenderer->ChangeAnimation(Name);
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

	return std::string(GetAniNamechange()) + std::string(_Name) + DirName;
}

//-------------------------------------------------------------------------------

void AKirby_Player::StateChange(ActorState _State)
{
	// �������¿� ���� ���°� ���� �ʾ�
	// �������� move ������ Idle
	if (State != _State)
	{
		switch (_State)
		{
		case ActorState::Idle:
			if (false == EatState)
			{
				IdleStart();
			}
			else
			{
				HeavyIdleStart();
			}
			break;
		case ActorState::Walk:
			if (false == EatState)
			{
				checkSpeed = WalkSpeed;
				WalkStart();;
			}
			else
			{
				checkSpeed = HeavySpeed;
				HeavyMoveStart();
			}
			break;
		case ActorState::Jump:
			JumpStart();
			break;
		case ActorState::Run:
			if (false == EatState)
			{
				RunStart();
			}
			break;
		case ActorState::Absorption:
			AbsorptionStart();
			break;
		case ActorState::HeadDown:
			HeadDownStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void AKirby_Player::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ActorState::CameraFreeMove:
		CameraFreeMove(_DeltaTime);
		break;
	case ActorState::FreeMove:
		FreeMove(_DeltaTime);
		break;
	case ActorState::Idle:
		Idle(_DeltaTime);
		break;
	case ActorState::Walk:
		Walk(_DeltaTime);
		break;
	case ActorState::Jump:
		Jump(_DeltaTime);
		break;
	case ActorState::Run:
		Run(_DeltaTime);
		break;
	case ActorState::Absorption:
		ModeInputTick(_DeltaTime);
		break;
	case ActorState::HeadDown:
		HeadDown(_DeltaTime);
		break;
	default:
		break;
	}
}


void AKirby_Player::CameraFreeMove(float _DeltaTime)
{
	if (EngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * camSpeed);
		// AddActorLocation(FVector::Left * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * camSpeed);
	}

	if (EngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * _DeltaTime * camSpeed);
		// AddActorLocation(FVector::Up * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * _DeltaTime * camSpeed);
		// AddActorLocation(FVector::Down * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsDown('2'))
	{
		StateChange(ActorState::Idle);
	}
}

void AKirby_Player::FreeMove(float _DeltaTime)
{
	FVector MovePos;

	if (EngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * WalkSpeed;
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * WalkSpeed;
	}

	if (EngineInput::IsPress(VK_UP))
	{
		MovePos += FVector::Up * _DeltaTime * WalkSpeed;
	}

	if (EngineInput::IsPress(VK_DOWN))
	{
		MovePos += FVector::Down * _DeltaTime * WalkSpeed;
	}

	AddActorLocation(MovePos);
	GetWorld()->AddCameraPos(MovePos);

	if (EngineInput::IsDown('1'))
	{
		StateChange(ActorState::Idle);
	}
}

void AKirby_Player::Idle(float _DeltaTime)
{
	// ���� �����ʵ� �ȵǰ� �ְ�.
	// ���⼭�� ����
	// ������ �������� ��� ���� �Ű澲�� �˴ϴ�.
	if (true == EngineInput::IsDown('1'))
	{
		StateChange(ActorState::FreeMove);
		return;
	}

	if (true == EngineInput::IsDown('2'))
	{
		StateChange(ActorState::CameraFreeMove);
		return;
	}


	if (
		true == EngineInput::IsPress(VK_LEFT) ||
		true == EngineInput::IsPress(VK_RIGHT)
		)
	{
		StateChange(ActorState::Walk);
		return;
	}

	if (
		true == EngineInput::IsDown('S')
		)
	{
		StateChange(ActorState::Jump);
		return;
	}

	if (
		true == EngineInput::IsPress(VK_DOWN)
		)
	{
		StateChange(ActorState::HeadDown);
		return;
	}


	if (
		true == EngineInput::IsPress('X')
		)
	{
		StateChange(ActorState::Absorption);
		return;
	}



	GravityCheck=GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime);
	AddActorLocation(GravityCheck);
}

void AKirby_Player::Jump(float _DeltaTime)
{
}



void AKirby_Player::HeadDown(float _DeltaTime)
{
	DirCheck();
	GravityCheck = GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime);
	AddActorLocation(GravityCheck);

	if (true == EngineInput::IsFree(VK_DOWN))
	{
		StateChange(ActorState::Idle);
		return;
	}
}

void AKirby_Player::Walk(float _DeltaTime)
{
	DirCheck();
	GravityCheck = GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime);
	AddActorLocation(GravityCheck);

	if (true == EngineInput::IsFree(VK_LEFT) && EngineInput::IsFree(VK_RIGHT))
	{
		StateChange(ActorState::Idle);
		return;
	}

	FVector MovePos = FVector::Zero;
	if (EngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * checkSpeed;
	}
	
	if(EngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * checkSpeed;
	}

	if (EngineInput::IsPress(VK_SHIFT))
	{
		StateChange(ActorState::Run);
		return;
	}

	FVector CheckPos = GetActorLocation();
	
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 30;
		break;
	case EActorDir::Right:
		CheckPos.X += 30;
		break;
	default:
		break;
	}
	CheckPos.Y -= 30;

	Color8Bit Color = ActorCommon::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::RedA);
	if (Color != Color8Bit(255, 0, 0, 0))
	{
		AddActorLocation(MovePos);
		GetWorld()->AddCameraPos(MovePos);
	}
}

void AKirby_Player::Run(float _DeltaTime)
{
	DirCheck();
	GravityCheck = GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime);
	AddActorLocation(GravityCheck);

	if (EngineInput::IsFree(VK_SHIFT))
	{
		StateChange(ActorState::Walk);
		return;
	}
	else if (EngineInput::IsFree(VK_SHIFT) && EngineInput::IsFree(VK_LEFT) && EngineInput::IsFree(VK_RIGHT))
	{
		StateChange(ActorState::Idle);
		return;
	}

	FVector MovePos = FVector::Zero;
	if (EngineInput::IsPress(VK_LEFT) && EngineInput::IsPress(VK_SHIFT))
	{
		MovePos += FVector::Left * _DeltaTime * RunSpeed;
	}

	if (EngineInput::IsPress(VK_RIGHT) && EngineInput::IsPress(VK_SHIFT))
	{
		MovePos += FVector::Right * _DeltaTime * RunSpeed;
	}

	FVector CheckPos = GetActorLocation();

	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 30;
		break;
	case EActorDir::Right:
		CheckPos.X += 30;
		break;
	default:
		break;
	}
	CheckPos.Y -= 30;
	Color8Bit Color = ActorCommon::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::RedA);
	if (Color != Color8Bit(255, 0, 0, 0))
	{
		AddActorLocation(MovePos);
		GetWorld()->AddCameraPos(MovePos);
	}
}

void AKirby_Player::Absorption(float _DeltaTime)
{
	
	StateChange(ActorState::Absorption);
	return;
}

void AKirby_Player::IdleStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("Idle"));
	DirCheck();
}

void AKirby_Player::HeavyIdleStart()
{

	KirbyRenderer->ChangeAnimation(GetAnimationName("HeavyIdle"));
	DirCheck();
}

void AKirby_Player::WalkStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("Walk"));
	DirCheck();
}

void AKirby_Player::HeavyMoveStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("HeavyMove"));
	DirCheck();
}

void AKirby_Player::JumpStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("Walk"));
	DirCheck();
}

void AKirby_Player::RunStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("Run"));
	DirCheck();
}

void AKirby_Player::AbsorptionStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("Absorption"));
	DirCheck();
}



void AKirby_Player::HeadDownStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("HeadDown"));
	DirCheck();
}

//------------------------------------------------------------------------------

void AKirby_Player::ModeInputTick(float _DeltaTime) // Ŀ�� �Ӽ� �� �� �͵�
{
	switch (KirbyMode)
	{
	case AMode::Base:
		//SetNamechange("Base_");
		BaseKirby(_DeltaTime);
		break;
	case AMode::Fire:
		FireKirby();
		break;
	case AMode::Mike:
		break;
	case AMode::Sword:
		break;
	case AMode::Hammer:
		break;
	default:
		break;
	}
}

void AKirby_Player::BaseKirby(float _DeltaTime)
{
	DirCheck();
	GravityCheck = GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime);
	AddActorLocation(GravityCheck);

	if (true == EngineInput::IsFree('X'))
	{
		StateChange(ActorState::Idle);
		return;
	}


	if (EngineInput::IsPress('X'))
	{
		Absorption(_DeltaTime);
		EatState = true;
	}

	

	
	
}

void AKirby_Player::FireKirby()
{
	
}