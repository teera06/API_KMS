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

		if (true == EngineInput::IsDown(VK_LEFT)) // 오른쪽 걷기
		{
			KirbyRenderer->ChangeAnimation("walk_Left");
			//KirbyRenderer->ChangeAnimation("Idle_Right");
		}
		
		AddActorLocation(FVector::Left * WalkSpeed * _DeltaTime);
		RLpoint = VK_LEFT; // 누른 키 값 저장
	}
	else if(true == EngineInput::IsUp(VK_LEFT) && RLpoint== VK_LEFT){ // 떼어진 키와 마지막으로 확인된 RLpoint가 같은 방향이야지 방향에 맞는 애니메이션으로 교체
		KirbyRenderer->ChangeAnimation("Idle_Left");
	}

	//---------------------------------------------------------------------
	if (true == EngineInput::IsPress(VK_RIGHT)) // 오른쪽 걷기
	{
		if (true == EngineInput::IsDown(VK_RIGHT)) // 오른쪽 걷기
		{
			KirbyRenderer->ChangeAnimation("walk_Right");
			//KirbyRenderer->ChangeAnimation("Idle_Right");
		}
		AddActorLocation(FVector::Right * WalkSpeed * _DeltaTime);
		RLpoint = VK_RIGHT; // 누른 키 값 저장
	}
	else if (true == EngineInput::IsUp(VK_RIGHT) && RLpoint== VK_RIGHT) {
		KirbyRenderer->ChangeAnimation("Idle_Right");
	}

	if (true == EngineInput::IsPress(VK_SHIFT) && true == EngineInput::IsPress(VK_LEFT)) // 왼쪽 뛰기
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
	else if (true == EngineInput::IsPress(VK_SHIFT) && true == EngineInput::IsPress(VK_RIGHT)) // 오른쪽 뛰기
	{

		if (true == EngineInput::IsDown(VK_SHIFT)) // 오른쪽 걷기
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
	// 지형과의 콜리전 필요
	if ((true == EngineInput::IsPress(VK_CONTROL) || true == EngineInput::IsDown(VK_CONTROL))) // 점프키를 눌렀을때 값 저장 (Alt)
	{
		JumpKey = VK_CONTROL; // Alt가 메뉴로 인시되서 우선 스페이스로
	}

	if (true == EngineInput::IsPress(VK_UP) && JumpKey==VK_CONTROL) // 점프를 한 상태에서만 공중부양 가능
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
	if (true == EngineInput::IsDown('A')) // 흡수 기능
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

void AKirby_Player::BeginPlay() // 실행했을때 준비되어야 할것들 Set
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
	
	
	KirbyRenderer = CreateImageRenderer(10); // 이미지 랜더 생성
	//KirbyRenderer->SetImage("kirby.bmp"); // 이미지 Set
	//SetActorLocation({100, 500 }); // Level 위의 Actor 위치 설정 
	//KirbyRenderer->SetTransform({ {0,0}, {80, 80} }); // 액터에서의 렌더(이미지) 위치 및 크기 설정 
	//KirbyRenderer->SetImageCuttingTransform({ {0,0}, {97, 106} }); // 버퍼가 SetImageCuttingTransform 기준으로 그려줌
	
	KirbyRenderer->SetImage("kirby_Right.png");
	//KirbyRenderer->SetTransColor({ 255,255, 255, 255 });
	KirbyRenderer->SetTransform({ {0,0}, {210, 210} }); // 랜더의 위치 크기 
	KirbyRenderer->SetImageCuttingTransform({ {0,0}, {128, 128} });
	// 기본 서있는 애니메이션 (오른쪽, 왼쪽)
	KirbyRenderer->CreateAnimation("Idle_Right", "kirby_Right.png", 0, 1, 0.5f, true); // 오른쪽 서 있기
	KirbyRenderer->CreateAnimation("Idle_Left", "kirby_Left.png", 0, 1, 0.5f, true); // 왼쪽 서있기
	
	// 기본 걷는 모션 (오른쪽, 왼쪽)
	KirbyRenderer->CreateAnimation("walk_Right", "kirby_Right.png", 10, 19, 0.1f, true); // 걷기
	KirbyRenderer->CreateAnimation("walk_Left", "kirby_Left.png",10, 19, 0.1f, true); // 걷기

	// 기본 뛰는 모션
	KirbyRenderer->CreateAnimation("run_Right", "kirby_Right.png", 20, 27, 0.1f, true); // 걷기
	KirbyRenderer->CreateAnimation("run_Left", "kirby_Left.png", 20, 27, 0.1f, true); // 걷기
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> 않기
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> 점프
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> 걷기
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> 뛰기
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> 공중

	KirbyRenderer->ChangeAnimation("Idle_Right");
	
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
