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

	Leftwalk(_DeltaTime); // 왼쪽 걷기
	Rightwalk(_DeltaTime); // 오른쪽 걷기
	RLrun(_DeltaTime); // 오른쪽, 왼쪽 뛰기

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
	if (true == EngineInput::IsPress(VK_LEFT)) // 왼쪽 걷기
	{

		if (true == EngineInput::IsDown(VK_LEFT)) // 왼쪽 걷기 애니메이션 실행
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) +"walk_Left");
		}

		AddActorLocation(FVector::Left * WalkSpeed * _DeltaTime); // 이동
		RLpoint = VK_LEFT; // 누른 키 값 저장
	}
	else if (true == EngineInput::IsUp(VK_LEFT) && RLpoint == VK_LEFT) { // 떼어진 키와 마지막으로 확인된 RLpoint가 같은 방향이야지 방향에 맞는 애니메이션으로 교체
		KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) +"Idle_Left");
	}
}

void AKirby_Player::Rightwalk(float _DeltaTime)
{
	if (true == EngineInput::IsPress(VK_RIGHT)) // 오른쪽 걷기
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
	if (true == EngineInput::IsPress(VK_SHIFT) && true == EngineInput::IsPress(VK_LEFT)) // 왼쪽 뛰기
	{
		if (true == EngineInput::IsDown(VK_SHIFT))
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) +"run_Left");
			lRunanicheck = true;
		}

		// run_Left 애니메이션을 실행했을때만 달리기 속도로 이동 이렇게 if문쓴 이유? : Shift키 + 이동키를 하면 걷는 모션에서 속도만 빨라짐 -> 반드시 run애니메이션을 걸치고 이동속도가 달라지게함
		if (true == lRunanicheck)
		{
			AddActorLocation(FVector::Left * RunSpeed * _DeltaTime);
		}

	}
	else if (true == EngineInput::IsPress(VK_SHIFT) && true == EngineInput::IsPress(VK_RIGHT)) // 오른쪽 뛰기
	{

		if (true == EngineInput::IsDown(VK_SHIFT))
		{
			KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) +"run_Right");
			rRunanicheck = true;
		}

		if (true == rRunanicheck) // 달리기 애니메이션을 진행하고 나서 이동
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
	//if (true == EngineInput::IsDown('A')) // 흡수 기능
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

	//if (true == EngineInput::IsDown('X')) // 모드 체인지
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
	KirbyRenderer->SetImage("kirby_Right.png"); // 이미지 Set
	KirbyRenderer->SetTransform({ {0,0}, {210, 210} }); // 랜더의 위치 크기 
	KirbyRenderer->SetImageCuttingTransform({ {0,0}, {128, 128} });
	// 기본 서있는 애니메이션 (오른쪽, 왼쪽)
	KirbyRenderer->CreateAnimation("Base_Idle_Right", "kirby_Right.png", 0, 1, 0.5f, true); // 오른쪽 서 있기
	KirbyRenderer->CreateAnimation("Base_Idle_Left", "kirby_Left.png", 0, 1, 0.5f, true); // 왼쪽 서있기
	
	// 기본 걷는 모션 (오른쪽, 왼쪽)
	KirbyRenderer->CreateAnimation("Base_walk_Right", "kirby_Right.png", 10, 19, 0.1f, true); // 걷기
	KirbyRenderer->CreateAnimation("Base_walk_Left", "kirby_Left.png",10, 19, 0.1f, true); // 걷기

	// 기본 뛰는 모션
	KirbyRenderer->CreateAnimation("Base_run_Right", "kirby_Right.png", 20, 27, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_run_Left", "kirby_Left.png", 20, 27, 0.1f, true);
	
	KirbyRenderer->CreateAnimation("Base_jump_Right", "kirby_Right.png", 38, 52, 0.1f, true); 
	KirbyRenderer->CreateAnimation("Base_jump_Left", "kirby_Left.png",38, 52, 0.1f, true); 

	KirbyRenderer->CreateAnimation("Base_jump2_Right", "kirby_Right.png", 53, 64, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_jump2_Left", "kirby_Left.png", 53, 64, 0.1f, true);
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> 걷기
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> 뛰기
	//KirbyRenderer->CreateAnimation("Idle", "Player_Right.png", 0, 12, 0.5f, true); -> 공중

	KirbyRenderer->ChangeAnimation(std::string(GetNamechange()) + "Idle_Right");
	
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> 이전 코드
}

// 커비 움직임 업데이트
void AKirby_Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	InputTick(_DeltaTime); // 커비 기본 입력키
	//ModeInputTick(); // 커비 모드별 입력키
}
