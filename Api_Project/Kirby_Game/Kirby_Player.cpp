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

	if (true == EngineInput::IsPress(VK_LEFT)) // ���� �ȱ�
	{

		if (true == EngineInput::IsDown(VK_LEFT)) // ������ �ȱ�
		{
			KirbyRenderer->ChangeAnimation("walk_Left");
			//KirbyRenderer->ChangeAnimation("Idle_Right");
		}
		
		AddActorLocation(FVector::Left * WalkSpeed * _DeltaTime);
		RLpoint = VK_LEFT; // ���� Ű �� ����
	}
	else if(true == EngineInput::IsUp(VK_LEFT) && RLpoint== VK_LEFT){ // ������ Ű�� ���������� Ȯ�ε� RLpoint�� ���� �����̾��� ���⿡ �´� �ִϸ��̼����� ��ü
		KirbyRenderer->ChangeAnimation("Idle_Left");
	}

	//---------------------------------------------------------------------
	if (true == EngineInput::IsPress(VK_RIGHT)) // ������ �ȱ�
	{
		if (true == EngineInput::IsDown(VK_RIGHT)) // ������ �ȱ�
		{
			KirbyRenderer->ChangeAnimation("walk_Right");
			//KirbyRenderer->ChangeAnimation("Idle_Right");
		}
		AddActorLocation(FVector::Right * WalkSpeed * _DeltaTime);
		RLpoint = VK_RIGHT; // ���� Ű �� ����
	}
	else if (true == EngineInput::IsUp(VK_RIGHT) && RLpoint== VK_RIGHT) {
		KirbyRenderer->ChangeAnimation("Idle_Right");
	}

	if (true == EngineInput::IsPress(VK_SHIFT) && true == EngineInput::IsPress(VK_LEFT)) // ���� �ٱ�
	{
		if (true == EngineInput::IsDown(VK_SHIFT))
		{
			KirbyRenderer->ChangeAnimation("run_Left");
			//KirbyRenderer->ChangeAnimation("Idle_Right");
			lRunanicheck = true;
		}

		if (true == lRunanicheck)
		{
			AddActorLocation(FVector::Left * RunSpeed * _DeltaTime);
		}
		
	}
	else if (true == EngineInput::IsPress(VK_SHIFT) && true == EngineInput::IsPress(VK_RIGHT)) // ������ �ٱ�
	{

		if (true == EngineInput::IsDown(VK_SHIFT)) // ������ �ȱ�
		{
			KirbyRenderer->ChangeAnimation("run_Right");
			//KirbyRenderer->ChangeAnimation("Idle_Right");
			rRunanicheck = true;
		}
		
		//if(true == EngineInput::IsUp(VK_SHIFT) || true == EngineInput::IsUp(VK_RIGHT)){
			//check = false;
		//}

		if (true== rRunanicheck)
		{
			AddActorLocation(FVector::Right * RunSpeed * _DeltaTime);
		}
	}
	else
	{
		rRunanicheck = false;
		lRunanicheck = false;
	}

	//-------------------------------------------------------------------------
	// �������� �ݸ��� �ʿ�
	if ((true == EngineInput::IsPress(VK_CONTROL) || true == EngineInput::IsDown(VK_CONTROL))) // ����Ű�� �������� �� ���� (Alt)
	{
		JumpKey = VK_CONTROL; // Alt�� �޴��� �νõǼ� �켱 �����̽���
	}

	if (true == EngineInput::IsPress(VK_UP) && JumpKey==VK_CONTROL) // ������ �� ���¿����� ���ߺξ� ����
	{
		AddActorLocation(FVector::Up * WalkSpeed * _DeltaTime);
	}

	//if (true == EngineInput::IsPress(VK_DOWN))
	//{
		//AddActorLocation(FVector::Down * WalkSpeed * _DeltaTime);
	//}

	//---------------------------------------------------------------------------

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

void AKirby_Player::BaseKirby()
{
	if (true == EngineInput::IsDown('A')) // ��� ���
	{
		ABase* NewBase = GetWorld()->SpawnActor<ABase>();

		if (RLpoint == VK_LEFT)
		{
			NewBase->SetActorLocation(GetActorLocation() - LRCheck);
			NewBase->SetDir(FVector::Left);
		}
		else {
			//KirbyRenderer->ChangeAnimation("Attack");
			NewBase->SetActorLocation(GetActorLocation() + LRCheck);
			NewBase->SetDir(FVector::Right);
		}
	}

	if (true == EngineInput::IsUp('A'))
	{
		KirbyRenderer->ChangeAnimation("Idle");
	}

	if (true == EngineInput::IsDown('X')) // ��� ü����
	{
		SetMode(AMode::Fire);
	}
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
	//KirbyRenderer->SetImage("kirby.bmp"); // �̹��� Set
	//SetActorLocation({100, 500 }); // Level ���� Actor ��ġ ���� 
	//KirbyRenderer->SetTransform({ {0,0}, {80, 80} }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 
	//KirbyRenderer->SetImageCuttingTransform({ {0,0}, {97, 106} }); // ���۰� SetImageCuttingTransform �������� �׷���
	
	KirbyRenderer->SetImage("kirby_Right.png");
	//KirbyRenderer->SetTransColor({ 255,255, 255, 255 });
	KirbyRenderer->SetTransform({ {0,0}, {210, 210} }); // ������ ��ġ ũ�� 
	KirbyRenderer->SetImageCuttingTransform({ {0,0}, {128, 128} });
	// �⺻ ���ִ� �ִϸ��̼� (������, ����)
	KirbyRenderer->CreateAnimation("Idle_Right", "kirby_Right.png", 0, 1, 0.5f, true); // ������ �� �ֱ�
	KirbyRenderer->CreateAnimation("Idle_Left", "kirby_Left.png", 0, 1, 0.5f, true); // ���� ���ֱ�
	
	// �⺻ �ȴ� ��� (������, ����)
	KirbyRenderer->CreateAnimation("walk_Right", "kirby_Right.png", 10, 19, 0.1f, true); // �ȱ�
	KirbyRenderer->CreateAnimation("walk_Left", "kirby_Left.png",10, 19, 0.1f, true); // �ȱ�

	// �⺻ �ٴ� ���
	KirbyRenderer->CreateAnimation("run_Right", "kirby_Right.png", 20, 27, 0.1f, true); // �ȱ�
	KirbyRenderer->CreateAnimation("run_Left", "kirby_Left.png", 20, 27, 0.1f, true); // �ȱ�
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> �ʱ�
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> ����
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> �ȱ�
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> �ٱ�
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> ����

	KirbyRenderer->ChangeAnimation("Idle_Right");
	
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�
	
	// UImageRenderer* Ptr = CreateRenderer();
	// �÷��̾� ����
	// Ptr->SetPosition({0.0, -50.0f}); // 500, 500
	// Ptr->SetImage("AAAA.png"); // 500, 500
	// Ptr->SetScale();
	// Ptr->SetImageScaleSetting(); 


	// CreateDefaultSubObject<UStaticMeshRenderer>();

	// n�� �����Ҽ� �ְ� ������ �Ѵ�.
	// ��ü�� ��ü�� �����ٰ� �ĺ���.

	//{
	//	EngineTime NewTime;
	//	NewTime.TimeCheckStart();
	//	std::vector<int> NewInt;
	//	for (int i = 0; i < 10000000; i++)
	//	{
	//		NewInt.push_back(i);
	//	}
	//	float Time = NewTime.TimeCheck();
	//	int a = 0;
	//}
	//{
	//	EngineTime NewTime;
	//	NewTime.TimeCheckStart();
	//	std::list<int> NewInt;
	//	for (int i = 0; i < 10000000; i++)
	//	{
	//		NewInt.push_back(i);
	//	}
	//	float Time = NewTime.TimeCheck();
	//	int a = 0;
	//}
}

// Ŀ�� ������ ������Ʈ
void AKirby_Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	InputTick(_DeltaTime); // Ŀ�� �⺻ �Է�Ű
	ModeInputTick(); // Ŀ�� ��庰 �Է�Ű
}
