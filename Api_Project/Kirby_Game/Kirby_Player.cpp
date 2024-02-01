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

// 입력 진행 모음집
void AKirby_Player::InputTick(float _DeltaTime)
{
	if (true == EngineInput::IsPress(VK_LEFT)) // 왼쪽 걷기
	{
		AddActorLocation(FVector::Left * WalkSpeed * _DeltaTime); // 위치 이동
		RLpoint = VK_LEFT; // 누른 키 값 저장
	}

	if (true == EngineInput::IsPress(VK_LEFT) && true == EngineInput::IsPress(VK_SHIFT)) // 왼쪽 뛰기
	{
		AddActorLocation(FVector::Left * RunSpeed * _DeltaTime);
	}

	//---------------------------------------------------------------------
	if (true == EngineInput::IsPress(VK_RIGHT)) // 오른쪽 걷기
	{
		AddActorLocation(FVector::Right * WalkSpeed * _DeltaTime);
		RLpoint = VK_RIGHT; // 누른 키 값 저장
	}

	if (true == EngineInput::IsPress(VK_RIGHT) && true == EngineInput::IsPress(VK_SHIFT)) // 오른쪽 뛰기
	{
		AddActorLocation(FVector::Right * RunSpeed * _DeltaTime);
	}

	//-------------------------------------------------------------------------
	// 지형과의 콜리전 필요
	if ((true == EngineInput::IsPress(VK_CONTROL) || true == EngineInput::IsDown(VK_CONTROL))) // 점프키를 눌렀을때 값 저장 (Alt)
	{
		JumpKey = VK_CONTROL; // Alt가 메뉴로 인시되서 우선 스페이스로
	}

	if (true == EngineInput::IsPress(VK_UP) && JumpKey==VK_CONTROL) // 점프를 한 상태에서만 공중부양 가능
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
	if (true == EngineInput::IsDown('A')) // 흡수 기능
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

	if (true == EngineInput::IsDown('X')) // 모드 체인지
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

	// 플레이어 100, 100 => Actor
	// 상체? 100, 100 - 50 => Renderer
	// 하체? 100, 100 + 50 => Renderer
	
	//{
		//BodyRenderer = CreateImageRenderer(0);
		//BodyRenderer->SetPosition({ 0, 30 });
		//BodyRenderer->SetScale({ 8, 80 });
	//}
	
	
	KirbyRenderer = CreateImageRenderer(1); // 이미지 랜더 생성
	//KirbyRenderer->SetImage("kirby.bmp"); // 이미지 Set
	//SetActorLocation({100, 500 }); // Level 위의 Actor 위치 설정 
	//KirbyRenderer->SetTransform({ {0,0}, {80, 80} }); // 액터에서의 렌더(이미지) 위치 및 크기 설정 
	//KirbyRenderer->SetImageCuttingTransform({ {0,0}, {97, 106} }); // 버퍼가 SetImageCuttingTransform 기준으로 그려줌
	
	KirbyRenderer->SetImage("Player_Right.png");
	KirbyRenderer->SetTransform({ {0,0}, {100, 100} });
	KirbyRenderer->SetImageCuttingTransform({ {64,64}, {32, 32} });
	KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true);
	KirbyRenderer->CreateAnimation("Attack", "Player_Right.png", 26, 32, 0.5f, true);
	KirbyRenderer->ChangeAnimation("Idle");
	
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> 이전 코드
	
	// UImageRenderer* Ptr = CreateRenderer();
	// 플레이어 기준
	// Ptr->SetPosition({0.0, -50.0f}); // 500, 500
	// Ptr->SetImage("AAAA.png"); // 500, 500
	// Ptr->SetScale();
	// Ptr->SetImageScaleSetting(); 


	// CreateDefaultSubObject<UStaticMeshRenderer>();

	// n장 랜더할수 있게 만들어야 한다.
	// 상체와 하체로 나뉜다고 쳐보자.

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

// 커비 움직임 업데이트
void AKirby_Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	InputTick(_DeltaTime); // 커비 기본 입력키
	ModeInputTick(); // 커비 모드별 입력키
}
