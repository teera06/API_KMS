#include "Kirby_Player.h"
#include <EnginePlatform\EngineInput.h> // Level1
#include <EngineCore/EngineCore.h>

#include "AllStar.h"
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

	KirbyRenderer = CreateImageRenderer(RenderOrder::kirby); // �̹��� ���� ����
	KirbyRenderer->SetImage("kirby_Right.png"); // �̹��� Set
	KirbyRenderer->SetTransform({ {0,0}, {210, 210} }); // ������ ��ġ ũ�� 

	AniCreate(); // �ִϸ��̼� ���� ����

	GetWorld()->SetCameraPos({ 210,350 }); // ī�޶� ��ġ

	StateAniChange(ActorState::Idle); // ���� �ִϸ��̼�

	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�
}

// Ŀ�� ������ ������Ʈ
void AKirby_Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	StateUpdate(_DeltaTime);
}

void AKirby_Player::AniCreate()
{
	// (������, ����)
	// (1) Base
	// �⺻ ���ִ� ���
	KirbyRenderer->CreateAnimation("Base_Idle_Right", "kirby_Right.png", 0, 1, 0.5f, true); // ������ �� �ֱ�
	KirbyRenderer->CreateAnimation("Base_Idle_Left", "kirby_Left.png", 0, 1, 0.5f, true); // ���� ���ֱ�

	// �⺻ �ȴ� ���
	KirbyRenderer->CreateAnimation("Base_Walk_Right", "kirby_Right.png", 10, 19, 0.1f, true); // �ȱ�
	KirbyRenderer->CreateAnimation("Base_Walk_Left", "kirby_Left.png", 10, 19, 0.1f, true); // �ȱ�

	// �⺻ �ٴ� ���
	KirbyRenderer->CreateAnimation("Base_run_Right", "kirby_Right.png", 20, 27, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_run_Left", "kirby_Left.png", 20, 27, 0.1f, true);

	// �⺻ ���� ���
	KirbyRenderer->CreateAnimation("Base_jump_Right", "kirby_Right.png", 38, 52, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_jump_Left", "kirby_Left.png", 38, 52, 0.1f, true);

	// �⺻ ���� ���
	KirbyRenderer->CreateAnimation("Base_Fly_Right", "kirby_Right.png", 53, 64, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_Fly_Left", "kirby_Left.png", 53, 64, 0.1f, true);

	// �⺻ ���̱� 
	KirbyRenderer->CreateAnimation("Base_HeadDown_Right", "kirby_Right.png", 2, 3, 0.5f, true);
	KirbyRenderer->CreateAnimation("Base_HeadDown_Left", "kirby_Left.png", 2, 3, 0.5f, true);

	// ---�⺻������ ������ ��ǵ�----
	// Heavy ��� Idle
	KirbyRenderer->CreateAnimation("Base_HeavyIdle_Right", "kirby2_Right.png", 19, 20, 0.5f, true);
	KirbyRenderer->CreateAnimation("Base_HeavyIdle_Left", "kirby2_Left.png", 19, 20, 0.5f, true);

	// Heavy��� Move
	KirbyRenderer->CreateAnimation("Base_HeavyMove_Right", "kirby2_Right.png", 23, 33, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_HeavyMove_Left", "kirby2_Left.png", 23, 33, 0.1f, true);
	
	// �⺻ ��� 
	KirbyRenderer->CreateAnimation("Base_Absorption_Right", "kirby2_Right.png", 0, 16, 0.06f, false);
	KirbyRenderer->CreateAnimation("Base_Absorption_Left", "kirby2_Left.png", 0, 16, 0.06f, false);
	
	// ��� Ŀ���忡�� ��� ������ �ִϸ��̼�
	KirbyRenderer->CreateAnimation("AllAttack_Right", "kirby2_Right.png", 42, 53, 0.03f, false);
	KirbyRenderer->CreateAnimation("AllAttack_Left", "kirby2_Left.png", 42, 53, 0.03f, false);

	
}

//----------------------------------------------------------------------------------------------------

void AKirby_Player::DirCheck() // Ŀ�� ���� ������ üũ
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

	if (std::string(_Name) == "AllAttack") // AllAttack�� ��� Ŀ���忡�� ��� �����ϱ⿡
	{// �տ� GetModeName���� AllAttack ���ڿ��� ���⸸ ����
		return std::string(_Name) + DirName;
	}
	return std::string(GetModeName()) + std::string(_Name) + DirName;
}

//-------------------------------------------------------------------------------

void AKirby_Player::StateAniChange(ActorState _State)
{
	// �������¿� ���� ���°� ���� �ʾ�
	// �������� move ������ Idle
	if (State != _State)
	{
		switch (_State)
		{
		case ActorState::Idle:
			if (true == EatState && KirbyMode== AMode::Base) // Eat���� (��������) �� Ŀ�� �⺻ ����϶��� üũ�� �����Ѵ�.
			{
				HeavyIdleStart(); // Heavy�� �⺻ ������ Ŀ�񿡼��� ������ �ִϸ��̼�
			}
			else
			{
				IdleStart();
			}
			break;
		case ActorState::Walk:
			if (true == EatState && KirbyMode == AMode::Base) // ����
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
		case ActorState::Jump:
			JumpStart();
			break;
		case ActorState::Run:
			if (true == EatState && KirbyMode == AMode::Base) // ����
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
		case ActorState::Absorption:
			AbsorptionStart();
			break;
		case ActorState::HeadDown:
			HeadDownStart();
			break;
		case ActorState::All_Attack:
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
	switch (State) // ���� ���º� �����ؾ��ϴ� ����
	{
	case ActorState::CameraFreeMove: // ī�޶� ������ -> �׽�Ʈ��
		CameraFreeMove(_DeltaTime);
		break;
	case ActorState::FreeMove: // ī�޶�, ĳ���� �����Ӱ� �̵� -> �׽�Ʈ��
		FreeMove(_DeltaTime);
		break;
	case ActorState::Idle: // ���ֱ�
		Idle(_DeltaTime);
		break;
	case ActorState::Walk: // �ȱ�
		Walk(_DeltaTime);
		break;
	case ActorState::Jump: // ����
		Jump(_DeltaTime);
		break;
	case ActorState::Run: // �޸���
		Run(_DeltaTime);
		break;
	case ActorState::Absorption: // ���
		ModeInputTick(_DeltaTime);
		break;
	case ActorState::HeadDown: // ���̱�
		HeadDown(_DeltaTime);
		break;
	case ActorState::All_Attack: // ��� �� ���� -> �� ����
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
		StateAniChange(ActorState::Idle);
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
		StateAniChange(ActorState::Idle);
	}
}

void AKirby_Player::Idle(float _DeltaTime)
{
	// ���� �����ʵ� �ȵǰ� �ְ�.
	// ���⼭�� ����
	// ������ �������� ��� ���� �Ű澲�� �˴ϴ�.
	if (true == UEngineInput::IsDown('1'))
	{
		StateAniChange(ActorState::FreeMove);
		return;
	}

	if (true == UEngineInput::IsDown('2'))
	{
		StateAniChange(ActorState::CameraFreeMove);
		return;
	}


	if (
		true == UEngineInput::IsPress(VK_LEFT) ||
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		StateAniChange(ActorState::Walk);
		return;
	}

	if (
		true == UEngineInput::IsDown('S')
		)
	{
		StateAniChange(ActorState::Jump);
		return;
	}

	if (
		true == UEngineInput::IsPress(VK_DOWN)
		)
	{
		StateAniChange(ActorState::HeadDown);
		return;
	}


	if (
		true == UEngineInput::IsDown('X') && false == EatState
		)
	{
		StateAniChange(ActorState::Absorption);
		return;
	}

	if (
		true == UEngineInput::IsDown('A') && true==EatState
		)
	{
		
		StateAniChange(ActorState::All_Attack);
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

	if (true == UEngineInput::IsFree(VK_DOWN))
	{
		StateAniChange(ActorState::Idle);
		return;
	}
}

void AKirby_Player::Walk(float _DeltaTime)
{
	DirCheck();
	GravityCheck = GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime);
	AddActorLocation(GravityCheck);

	if (true == UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		StateAniChange(ActorState::Idle);
		return;
	}

	FVector MovePos = FVector::Zero;
	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_SHIFT))
	{
		StateAniChange(ActorState::Run);
		return;
	}

	FVector CheckPos = GetActorLocation();
	
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= checkposvalue;
		break;
	case EActorDir::Right:
		CheckPos.X += checkposvalue;
		break;
	default:
		break;
	}
	CheckPos.Y -= checkposvalue;

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

	if (UEngineInput::IsFree(VK_SHIFT))
	{
		StateAniChange(ActorState::Walk);
		return;
	}
	else if (UEngineInput::IsPress(VK_SHIFT) && UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		StateAniChange(ActorState::Idle);
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

	FVector CheckPos = GetActorLocation();

	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= checkposvalue;
		break;
	case EActorDir::Right:
		CheckPos.X += checkposvalue;
		break;
	default:
		break;
	}
	CheckPos.Y -= checkposvalue;
	Color8Bit Color = ActorCommon::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::RedA);
	if (Color != Color8Bit(255, 0, 0, 0))
	{
		AddActorLocation(MovePos);
		GetWorld()->AddCameraPos(MovePos);
	}
}

void AKirby_Player::Absorption(float _DeltaTime)
{
	
	DirCheck();
	GravityCheck = GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime);
	AddActorLocation(GravityCheck);

	if (true == UEngineInput::IsFree('X'))
	{
		StateAniChange(ActorState::Idle);
		return;
	}

	if (UEngineInput::IsPress('X') && false == EatState)
	{
		if (KirbyRenderer->IsCurAnimationEnd())
		{
			EatState = true;
		}
	}
}

void AKirby_Player::All_Attack(float _DeltaTime)
{
	DirCheck();
	GravityCheck = GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime);
	AddActorLocation(GravityCheck);
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		EatState = false;

		StateAniChange(ActorState::Idle);
	}
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
	KirbyRenderer->ChangeAnimation(GetAnimationName("Walk"));
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

void AKirby_Player::ModeInputTick(float _DeltaTime) // Ŀ�� �Ӽ� �� �� �͵�
{
	switch (KirbyMode)
	{
	case AMode::Base:
		//SetNamechange("Base_");
		Absorption(_DeltaTime);
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

void AKirby_Player::FireKirby()
{
	
}