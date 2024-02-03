#include "Kirby_Player.h"
#include <EnginePlatform\EngineInput.h> // Level1

#include "Fire.h"
#include "Base.h"

AKirby_Player::AKirby_Player()
{
}

AKirby_Player::~AKirby_Player()
{
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
	
}


void AKirby_Player::ModeInputTick()
{
	switch (KirbyMode)
	{
	case AMode::Base:
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
	if (true == EngineInput::IsPress(VK_LEFT)) // ���� �ȱ�
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
	if (true == EngineInput::IsPress(VK_RIGHT)) // ������ �ȱ�
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
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) +"run_Left");
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
	}
}

void AKirby_Player::BaseKirby()
{
	//if (true == EngineInput::IsDown('A')) // ��� ���
	//{
		//ABase* NewBase = GetWorld()->SpawnActor<ABase>();

		//if (RLpoint == VK_LEFT)
		//{
			//NewBase->SetActorLocation(GetActorLocation() - LRCheck);
			//NewBase->SetDir(FVector::Left);
		//}
		//else {
			//NewBase->SetActorLocation(GetActorLocation() + LRCheck);
			//NewBase->SetDir(FVector::Right);
		//}
	//}

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
	
	
	KirbyRenderer = CreateImageRenderer(10); // �̹��� ���� ����
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
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> �ȱ�
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> �ٱ�
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> ����

	KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "Idle_Right");
	
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�
}

// Ŀ�� ������ ������Ʈ
void AKirby_Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	InputTick(_DeltaTime); // Ŀ�� �⺻ �Է�Ű
	//ModeInputTick(); // Ŀ�� ��庰 �Է�Ű
}
