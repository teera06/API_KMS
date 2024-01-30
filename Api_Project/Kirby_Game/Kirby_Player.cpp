#include "Kirby_Player.h"
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineTime.h>

#include "Fire.h"
#include "Base.h"

Kirby_Player::Kirby_Player()
{
}

Kirby_Player::~Kirby_Player()
{
}

// 입력 진행 모음집
void Kirby_Player::InputTick(float _DeltaTime)
{
	if (true == EngineInput::IsPress(VK_LEFT)) // 왼쪽 걷기
	{
		AddActorLocation(FVector::Left * WalkSpeed * _DeltaTime);
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
	if ((true == EngineInput::IsPress(VK_SPACE) || true == EngineInput::IsDown(VK_SPACE))) // 점프키를 눌렀을때 값 저장 (Alt)
	{
		JumpKey = VK_SPACE; // Alt가 메뉴로 인시되서 우선 스페이스로
	}

	if (true == EngineInput::IsPress(VK_UP) && JumpKey==VK_SPACE) // 점프를 한 상태에서만 공중부양 가능
	{
		AddActorLocation(FVector::Up * WalkSpeed * _DeltaTime);
	}

	if (true == EngineInput::IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * WalkSpeed * _DeltaTime);
	}

	//---------------------------------------------------------------------------

}

void Kirby_Player::ModeInputTick(float _DeltaTime)
{
	switch (KirbyMode)
	{
	case Mode::Base:
		if (true == EngineInput::IsDown('A'))
		{
			ABase* NewBase = GetWorld()->SpawnActor<ABase>();
			NewBase->SetActorLocation(GetActorLocation());

			if (RLpoint == VK_LEFT)
			{
				NewBase->SetDir(FVector::Left);
			}
			else {
				NewBase->SetDir(FVector::Right);
			}
		}
		break;
	case Mode::Fire:
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
			SetMode(Mode::Base);
		}
		break;
	case Mode::Mike:
		break;
	case Mode::Sword:
		break;
	case Mode::Hammer:
		break;
	default:
		break;
	}
}

void Kirby_Player::BeginPlay()
{
	AActor::BeginPlay();

	// 플레이어 100, 100 => Actor
	// 상체? 100, 100 - 50 => Renderer
	// 하체? 100, 100 + 50 => Renderer
	
	// Level에서의 위치와 크기
	SetActorLocation({ 100, 500 }); // Actor의 위치
	//SetActorScale({ 100, 100 }); // Acotor 크기는 상관 없음 

	//{
		//BodyRenderer = CreateImageRenderer(0);
		//BodyRenderer->SetPosition({ 0, 30 });
		//BodyRenderer->SetScale({ 8, 80 });
	//}
	
	{
		// Actor에서의 위치와 크기, 이미지
		KirbyRenderer = CreateImageRenderer(0); 
		KirbyRenderer->SetPosition({ 0, 0 });
		KirbyRenderer->SetScale({ 50, 50 });
	}
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
void Kirby_Player::Tick(float _DeltaTime)
{

	InputTick(_DeltaTime); // 커비 기본 입력키
	ModeInputTick(_DeltaTime); // 커비 모드별 입력키
}
