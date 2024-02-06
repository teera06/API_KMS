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

void AKirby_Player::GravityCheck(float _DeltaTime) // �߷� üũ
{
	//Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY());
	//if (Color != Color8Bit(255, 0, 255, 0))
	//{
		//AddActorLocation(FVector::Down * _DeltaTime * Gravity);
	//}
}

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



void AKirby_Player::ModeInputTick() // Ŀ�� �Ӽ� �� �� �͵�
{
	switch (KirbyMode)
	{
	case AMode::Base:
		//SetNamechange("Base_");
		BaseKirby();
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

	return std::string(GetNamechange()) +std::string(_Name) + DirName;
}

void AKirby_Player::BaseKirby()
{
	if (true == EngineInput::IsDown('X'))
	{
		AttMotion = true;
		if (RLpoint == VK_LEFT)
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "Attack_Left");
			//NewBase->SetActorLocation(GetActorLocation() - LRCheck);
			//NewBase->SetDir(FVector::Left);
		}
		else {
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "Attack_Right");
			//NewBase->SetActorLocation(GetActorLocation() + LRCheck);
			//NewBase->SetDir(FVector::Right);
		}
	}
	else if (true == EngineInput::IsUp('X'))
	{
		AttMotion = false;
		if (RLpoint == VK_LEFT)
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "Idle_Left");
			//NewBase->SetActorLocation(GetActorLocation() - LRCheck);
			//NewBase->SetDir(FVector::Left);
		}
		else {
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "Idle_Right");
			//NewBase->SetActorLocation(GetActorLocation() + LRCheck);
			//NewBase->SetDir(FVector::Right);
		}
	}

	//if (true == EngineInput::IsUp('A'))
	//{
		//KirbyRenderer->ChangeAnimation("Idle");
	//}

	//if (true == EngineInput::IsDown('X')) // ��� ü����
	//{
		//SetMode(AMode::Fire);
	//}
}

void AKirby_Player::FireKirby()
{
	if (true == EngineInput::IsDown('A'))
	{
		AFire* NewFire = GetWorld()->SpawnActor<AFire>();
		NewFire->SetActorLocation(GetActorLocation());

		if (RLpoint == VK_LEFT)
		{
			NewFire->SetDir(FVector::Left);
		}
		else {
			NewFire->SetDir(FVector::Right);
		}
	}
	if (true == EngineInput::IsDown('X'))
	{
		SetMode(AMode::Base);
	}
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
	KirbyRenderer->SetImageCuttingTransform({ {0,0}, {128, 128} });

	// �⺻ ���ִ� �ִϸ��̼� (������, ����)
	KirbyRenderer->CreateAnimation("Base_Idle_Right", "kirby_Right.png", 0, 1, 0.5f, true); // ������ �� �ֱ�
	KirbyRenderer->CreateAnimation("Base_Idle_Left", "kirby_Left.png", 0, 1, 0.5f, true); // ���� ���ֱ�
	
	// �⺻ �ȴ� ��� (������, ����)
	KirbyRenderer->CreateAnimation("Base_Walk_Right", "kirby_Right.png", 10, 19, 0.1f, true); // �ȱ�
	KirbyRenderer->CreateAnimation("Base_Walk_Left", "kirby_Left.png",10, 19, 0.1f, true); // �ȱ�

	// �⺻ �ٴ� ���
	KirbyRenderer->CreateAnimation("Base_run_Right", "kirby_Right.png", 20, 27, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_run_Left", "kirby_Left.png", 20, 27, 0.1f, true);
	
	KirbyRenderer->CreateAnimation("Base_jump_Right", "kirby_Right.png", 38, 52, 0.1f, true); 
	KirbyRenderer->CreateAnimation("Base_jump_Left", "kirby_Left.png",38, 52, 0.1f, true); 

	KirbyRenderer->CreateAnimation("Base_jump2_Right", "kirby_Right.png", 53, 64, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_jump2_Left", "kirby_Left.png", 53, 64, 0.1f, true);
	
	// �⺻ ���̽� ����
	KirbyRenderer->CreateAnimation("Base_Attack_Right", "kirby2_Right.png", 0, 18, 0.08f, true);
	KirbyRenderer->CreateAnimation("Base_Attack_Left", "kirby2_Left.png", 0, 18, 0.08f, true);
	
	
	KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "Idle_Right");
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

void AKirby_Player::StateChange(ActorState _State)
{
	// �������¿� ���� ���°� ���� �ʾ�
	// �������� move ������ Idle
	if (State != _State)
	{
		switch (_State)
		{
		case ActorState::Idle:
			IdleStart();
			break;
		case ActorState::Walk:
			WalkStart();
			break;
		case ActorState::Jump:
			JumpStart();
			break;
		case ActorState::Run:
			RunStart();
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
	default:
		break;
	}
}

void AKirby_Player::CameraFreeMove(float _DeltaTime)
{
	if (EngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Left * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Up * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * _DeltaTime * 500.0f);
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
		true == EngineInput::IsDown(VK_SPACE)
		)
	{
		StateChange(ActorState::Jump);
		return;
	}

	GravityCheck(_DeltaTime);
}

void AKirby_Player::Jump(float _DeltaTime)
{
}

void AKirby_Player::Walk(float _DeltaTime)
{
	//DirCheck();
	GravityCheck(_DeltaTime);

	if (true == EngineInput::IsFree(VK_LEFT) && EngineInput::IsFree(VK_RIGHT))
	{
		StateChange(ActorState::Idle);
		return;
	}

	FVector MovePos = FVector::Zero;
	if (EngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * WalkSpeed;
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * WalkSpeed;
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
	AddActorLocation(MovePos);
	CheckPos.Y -= 30;

	//Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	//if (Color != Color8Bit(255, 0, 255, 0))
	//{
		//AddActorLocation(MovePos);
		//GetWorld()->AddCameraPos(MovePos);
	//}
}

void AKirby_Player::Run(float _DeltaTime)
{
	//DirCheck();
	GravityCheck(_DeltaTime);

	if (EngineInput::IsFree(VK_SHIFT))
	{
		StateChange(ActorState::Walk);
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
	AddActorLocation(MovePos);
}

void AKirby_Player::IdleStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("Idle"));
	DirCheck();
}

void AKirby_Player::WalkStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("Walk"));
	DirCheck();
}

void AKirby_Player::JumpStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("Move"));
	DirCheck();
}

void AKirby_Player::RunStart()
{
	KirbyRenderer->ChangeAnimation(GetAnimationName("Run"));
	DirCheck();
}
