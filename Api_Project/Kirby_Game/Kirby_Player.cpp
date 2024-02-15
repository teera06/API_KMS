#include "Kirby_Player.h"
#include <EnginePlatform\EngineInput.h> // Level1
#include <EngineCore/EngineCore.h>

#include "AllStar.h"
#include "Fire.h"
#include "Base.h"

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

void AKirby_Player::BeginPlay() // ���������� �غ�Ǿ�� �Ұ͵� Set
{
	AActor::BeginPlay();

	MainPlayer = this;

	KirbyRenderer = CreateImageRenderer(ERenderOrder::kirby); // �̹��� ���� ����
	KirbyRenderer->SetImage("kirby_Right.png"); // �̹��� Set
	KirbyRenderer->SetTransform({ {0,0}, {210, 210} }); // ������ ��ġ ũ�� 

	AniCreate(); // �ִϸ��̼� ���� ����

	// �Ϲ������δ� �浹�̶�� ������ ���εӴϴ�.
	{
		KirbyCollision = CreateCollision(ECollisionOrder::kirby);
		KirbyCollision->SetScale({ 70, 70 });
		KirbyCollision->SetColType(ECollisionType::Rect);
	}


	GetWorld()->SetCameraPos({ GetTransform().GetPosition().iX(),350}); // ī�޶� ��ġ
	StateAniChange(EActorState::Idle); // ���� �ִϸ��̼�

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
	KirbyRenderer->CreateAnimation("Base_Jump_Right", "kirby_Right.png", 38, 51, 0.09f, true);
	KirbyRenderer->CreateAnimation("Base_Jump_Left", "kirby_Left.png", 38, 51, 0.09f, true);

	// �⺻ ���� ���
	KirbyRenderer->CreateAnimation("Base_FlyReady_Right", "kirby_Right.png", 53, 57, 0.1f, false);
	KirbyRenderer->CreateAnimation("Base_FlyReady_Left", "kirby_Left.png", 53, 57, 0.1f, false);
	KirbyRenderer->CreateAnimation("Base_Fly_Right", "kirby_Right.png", 58, 65, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_Fly_Left", "kirby_Left.png", 58, 65, 0.1f, true);

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
	// ���η� ���� �ʱ�ȭ ��Ų��.
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
		CheckPos.X -= checkposvalue;
		CarCheckPos.X -= 3;
		break;
	case EActorDir::Right:
		CheckPos.X += checkposvalue;
		CarCheckPos.X += 3;
		break;
	default:
		break;
	}
	CheckPos.Y -= checkposvalue;
	CarCheckPos.Y -= checkposvalue;
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
	//MoveLastMoveVector(_DeltaTime);
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

void AKirby_Player::StateAniChange(EActorState _State)
{
	// �������¿� ���� ���°� ���� �ʾ�
	// �������� move ������ Idle
	if (State != _State)
	{
		switch (_State)
		{
		case EActorState::Idle:
			

			if (true == EatState && KirbyMode== EAMode::Base) // Eat���� (��������) �� Ŀ�� �⺻ ����϶��� üũ�� �����Ѵ�.
			{
				HeavyIdleStart(); // Heavy�� �⺻ ������ Ŀ�񿡼��� ������ �ִϸ��̼�
			}
			else
			{
				IdleStart();
			}
			break;
		case EActorState::Walk:
			if (true == EatState && KirbyMode == EAMode::Base) // ����
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
			JumpStart();
			break;
		case EActorState::FlyRead:
			FlyReadyStart();
			break;
		case EActorState::Fly:
			FlyStart();
			break;
		case EActorState::Run:
			if (true == EatState && KirbyMode == EAMode::Base) // ����
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
	switch (State) // ���� ���º� �����ؾ��ϴ� ����
	{
	case EActorState::CameraFreeMove: // ī�޶� ������ -> �׽�Ʈ��
		CameraFreeMove(_DeltaTime);
		break;
	case EActorState::FreeMove: // ī�޶�, ĳ���� �����Ӱ� �̵� -> �׽�Ʈ��
		FreeMove(_DeltaTime);
		break;
	case EActorState::Idle: // ���ֱ�
		Idle(_DeltaTime);
		break;
	case EActorState::Walk: // �ȱ�
		Walk(_DeltaTime);
		break;
	case EActorState::Jump: // ����
		Jump(_DeltaTime);
		break;
	case EActorState::Fly: // ����
		Fly(_DeltaTime);
		break;
	case EActorState::Run: // �޸���
		Run(_DeltaTime);
		break;
	case EActorState::Absorption: // ���
		ModeInputTick(_DeltaTime);
		break;
	case EActorState::HeadDown: // ���̱�
		HeadDown(_DeltaTime);
		break;
	case EActorState::All_Attack: // ��� �� ���� -> �� ����
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
	// ���� �����ʵ� �ȵǰ� �ְ�.
	// ���⼭�� ����
	// ������ �������� ��� ���� �Ű澲�� �˴ϴ�.

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
		CurY = GetTransform().GetPosition();

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
		MovePos+=FVector::Left*checkSpeed* _DeltaTime;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right*checkSpeed* _DeltaTime;
	}

	if (UEngineInput::IsDown('S'))
	{
		FlyState = true;
		JumpVector = FVector::Zero;
		StateAniChange(EActorState::Fly);
		return;
	}


	MoveUpdate(_DeltaTime,MovePos);

	
	Color8Bit Color = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (Color == Color8Bit(255, 0, 0, 0))
	{
		JumpVector = FVector::Zero;
		StateAniChange(EActorState::Idle);
		return;
	}
}

void AKirby_Player::Fly(float _DeltaTime)
{
	DirCheck();
	
	if (UEngineInput::IsFree('S'))
	{
		FlyState = false;
		StateAniChange(EActorState::Idle);
		return;
	}

	FVector MovePos= FVector::Zero;
	
	if (UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsPress('S'))
	{
		MovePos += FVector::Left * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT) && UEngineInput::IsPress('S'))
	{
		MovePos += FVector::Right * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_UP) && UEngineInput::IsPress('S'))
	{
		MovePos += FVector::Up * _DeltaTime * 100.0f;
	}

	if (UEngineInput::IsPress(VK_DOWN) && UEngineInput::IsPress('S'))
	{
		MovePos += FVector::Down * _DeltaTime * 100.0f;
	}
	

	MoveUpdate(_DeltaTime, MovePos);
	//AddActorLocation(MovePos);
	//GetWorld()->AddCameraPos(MovePos * FVector::Right);

	

	Color8Bit Color1 = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY()-15, Color8Bit::MagentaA);
	if (Color1 == Color8Bit(255, 0, 255, 0) )
	{

		FlyState = false;

		StateAniChange(EActorState::Idle);
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
}

void AKirby_Player::Absorption(float _DeltaTime)
{
	
	DirCheck();
	
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		
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
	JumpVector = JumpPower;
	KirbyRenderer->ChangeAnimation(GetAnimationName("Jump"));
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
	case EAMode::Base:
		//SetNamechange("Base_");
		Absorption(_DeltaTime);
		break;
	case EAMode::Fire:
		FireKirby();
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


