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
		AddActorLocation(FVector::Left * WalkSpeed * _DeltaTime); // ��ġ �̵�
		RLpoint = VK_LEFT; // ���� Ű �� ����
	}

	if (true == EngineInput::IsPress(VK_LEFT) && true == EngineInput::IsPress(VK_SHIFT)) // ���� �ٱ�
	{
		AddActorLocation(FVector::Left * RunSpeed * _DeltaTime);
	}

	//---------------------------------------------------------------------
	if (true == EngineInput::IsPress(VK_RIGHT)) // ������ �ȱ�
	{
		AddActorLocation(FVector::Right * WalkSpeed * _DeltaTime);
		RLpoint = VK_RIGHT; // ���� Ű �� ����
	}

	if (true == EngineInput::IsPress(VK_RIGHT) && true == EngineInput::IsPress(VK_SHIFT)) // ������ �ٱ�
	{
		AddActorLocation(FVector::Right * RunSpeed * _DeltaTime);
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

	if (true == EngineInput::IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * WalkSpeed * _DeltaTime);
	}

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
		KirbyRenderer->ChangeAnimation("Attack");
		ABase* NewBase = GetWorld()->SpawnActor<ABase>();

		if (RLpoint == VK_LEFT)
		{
			NewBase->SetActorLocation(GetActorLocation() - LRCheck);
			NewBase->SetDir(FVector::Left);
		}
		else {
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

void AKirby_Player::BeginPlay()
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
	
	
	KirbyRenderer = CreateImageRenderer(1); // �̹��� ���� ����
	//KirbyRenderer->SetImage("kirby.bmp"); // �̹��� Set
	//SetActorLocation({100, 500 }); // Level ���� Actor ��ġ ���� 
	//KirbyRenderer->SetTransform({ {0,0}, {80, 80} }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 
	//KirbyRenderer->SetImageCuttingTransform({ {0,0}, {97, 106} }); // ���۰� SetImageCuttingTransform �������� �׷���
	
	KirbyRenderer->SetImage("Player_Right.png");
	KirbyRenderer->SetTransform({ {0,0}, {100, 100} });
	KirbyRenderer->SetImageCuttingTransform({ {64,64}, {32, 32} });
	KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true);
	KirbyRenderer->CreateAnimation("Attack", "Player_Right.png", 26, 32, 0.5f, true);
	KirbyRenderer->ChangeAnimation("Idle");
	
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
