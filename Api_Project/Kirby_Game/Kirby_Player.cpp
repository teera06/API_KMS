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

void AKirby_Player::GravityCheck(float _DeltaTime)
{
	//Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY());
	//if (Color != Color8Bit(255, 0, 255, 0))
	//{
		//AddActorLocation(FVector::Down * _DeltaTime * Gravity);
	//}
}

// �Է� ���� ������
void AKirby_Player::InputTick(float _DeltaTime)
{

	Leftwalk(_DeltaTime); // ���� �ȱ�
	Rightwalk(_DeltaTime); // ������ �ȱ�
	RLrun(_DeltaTime); // ������, ���� �ٱ�

	if (true == EngineInput::IsDown('S') && RLpoint==VK_LEFT)
	{
		KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "jump_Left");
		if (true == EngineInput::IsDown('S') && RLpoint == VK_LEFT)
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "jump2_Left");
		}
		
	}
	
	if (true == EngineInput::IsDown('S') && RLpoint == VK_RIGHT)
	{
		KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "jump_Right");
		if (true == EngineInput::IsDown('S') && RLpoint == VK_RIGHT)
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "jump2_Right");
		}
	}

	//if (true == EngineInput::IsPress(VK_DOWN)
	
	
}


void AKirby_Player::ModeInputTick()
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

void AKirby_Player::Leftwalk(float _DeltaTime)
{
	if (true == EngineInput::IsPress(VK_LEFT) && false==AttMotion) // ���� �ȱ�
	{

		if (true == EngineInput::IsDown(VK_LEFT)) // ���� �ȱ� �ִϸ��̼� ����
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) +"walk_Left");
		}

		AddActorLocation(FVector::Left * WalkSpeed * _DeltaTime); // �̵�
		RLpoint = VK_LEFT; // ���� Ű �� ����
	}
	else if (true == EngineInput::IsUp(VK_LEFT) && RLpoint == VK_LEFT) { // ������ Ű�� ���������� Ȯ�ε� RLpoint�� ���� �����̾��� ���⿡ �´� �ִϸ��̼����� ��ü
		KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) +"Idle_Left");
	}
}

void AKirby_Player::Rightwalk(float _DeltaTime)
{
	if (true == EngineInput::IsPress(VK_RIGHT) && false==AttMotion) // ������ �ȱ�
	{
		if (true == EngineInput::IsDown(VK_RIGHT)) 
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) +"walk_Right");
		}
		AddActorLocation(FVector::Right * WalkSpeed * _DeltaTime);
		RLpoint = VK_RIGHT; 
	}
	else if (true == EngineInput::IsUp(VK_RIGHT) && RLpoint == VK_RIGHT) {
		KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) +"Idle_Right");
	}
}

void AKirby_Player::RLrun(float _DeltaTime)
{
	if (true == EngineInput::IsPress(VK_SHIFT) && true == EngineInput::IsPress(VK_LEFT)) // ���� �ٱ�
	{
		if (true == EngineInput::IsDown(VK_SHIFT))
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "run_Left");
			lRunanicheck = true;
		}
		

		// run_Left �ִϸ��̼��� ������������ �޸��� �ӵ��� �̵� �̷��� if���� ����? : ShiftŰ + �̵�Ű�� �ϸ� �ȴ� ��ǿ��� �ӵ��� ������ -> �ݵ�� run�ִϸ��̼��� ��ġ�� �̵��ӵ��� �޶�������
		if (true == lRunanicheck)
		{
			AddActorLocation(FVector::Left * RunSpeed * _DeltaTime);
		}
		
	}
	else if (true == EngineInput::IsPress(VK_SHIFT) && true == EngineInput::IsPress(VK_RIGHT)) // ������ �ٱ�
	{

		if (true == EngineInput::IsDown(VK_SHIFT))
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) +"run_Right");
			rRunanicheck = true;
		}
	

		if (true == rRunanicheck) // �޸��� �ִϸ��̼��� �����ϰ� ���� �̵�
		{
			AddActorLocation(FVector::Right * RunSpeed * _DeltaTime);
		}
		
		
	}
	else
	{
		rRunanicheck = false;
		lRunanicheck = false;
		//KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "walk_Right");
		
	}
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
	KirbyRenderer->CreateAnimation("Base_walk_Right", "kirby_Right.png", 10, 19, 0.1f, true); // �ȱ�
	KirbyRenderer->CreateAnimation("Base_walk_Left", "kirby_Left.png",10, 19, 0.1f, true); // �ȱ�

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
	//InputTick(_DeltaTime); // Ŀ�� �⺻ �Է�Ű
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
		case ActorState::Move:
			MoveStart();
			break;
		case ActorState::Jump:
			JumpStart();
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
	case ActorState::Move:
		Move(_DeltaTime);
		break;
	case ActorState::Jump:
		Jump(_DeltaTime);
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
		StateChange(ActorState::Move);
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

void AKirby_Player::Move(float _DeltaTime)
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

	FVector CheckPos = GetActorLocation();
	//switch (DirState)
	//{
	//case EActorDir::Left:
		//CheckPos.X -= 30;
		//break;
	//case EActorDir::Right:
		//CheckPos.X += 30;
		//break;
	//default:
		//break;
	//}
	//CheckPos.Y -= 30;
	//Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	//if (Color != Color8Bit(255, 0, 255, 0))
	//{
		//AddActorLocation(MovePos);
		//GetWorld()->AddCameraPos(MovePos);
	//}
}

void AKirby_Player::IdleStart()
{
}

void AKirby_Player::MoveStart()
{
}

void AKirby_Player::JumpStart()
{
}
