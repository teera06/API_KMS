#include "Kirby_Player.h"
#include <EnginePlatform\EngineInput.h>


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
		AddActorLocation(FVector::Left * WalkSpeed * _DeltaTime);
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
	if ((true == EngineInput::IsPress(VK_SPACE) || true == EngineInput::IsDown(VK_SPACE))) // ����Ű�� �������� �� ���� (Alt)
	{
		JumpKey = VK_SPACE; // Alt�� �޴��� �νõǼ� �켱 �����̽���
	}

	if (true == EngineInput::IsPress(VK_UP) && JumpKey==VK_SPACE) // ������ �� ���¿����� ���ߺξ� ����
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
	
	// Level������ ��ġ�� ũ��
	SetActorLocation({ 100, 500 }); // Actor�� ��ġ
	//SetActorScale({ 100, 100 }); // Acotor ũ��� ��� ���� 

	//{
		//BodyRenderer = CreateImageRenderer(0);
		//BodyRenderer->SetPosition({ 0, 30 });
		//BodyRenderer->SetScale({ 8, 80 });
	//}
	
	{
		// Actor������ ��ġ�� ũ��, �̹���
		KirbyRenderer = CreateImageRenderer(0); 
		KirbyRenderer->SetPosition({ 0, 0 });
		KirbyRenderer->SetImageToScale("kirby.bmp");
	}
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
