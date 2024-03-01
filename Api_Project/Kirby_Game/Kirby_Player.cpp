#include "Kirby_Player.h"

#include <EnginePlatform\EngineInput.h> // Level1 -> 입력 담당(조작)
#include <EngineCore/EngineCore.h> // GetWorld 사용 -> Level 정보 이용

#include "AllStar.h"
#include "Fire.h"
#include "Base.h"
#include "Ice.h"

#include "Stage2_Level.h"
// 테스트
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"


AKirby_Player* AKirby_Player::MainPlayer = nullptr;

int AKirby_Player::Hp = 100;
int AKirby_Player::StageCheck = 1;
bool AKirby_Player::CreateStage2=false;
bool AKirby_Player::CreateStage3 = false;


AKirby_Player* AKirby_Player::GetMainPlayer()
{
	return MainPlayer;
}

AKirby_Player::AKirby_Player()
{
}

AKirby_Player::~AKirby_Player()
{

}

void AKirby_Player::CamYMove() // 카메라 Y축 이동 담당
{
	FVector CamMoveY=FVector::Zero;

	if (CurY.iY() != GetActorLocation().iY()) // 커비 Actor의 Y축 변화가 있는 경우
	{
		if (CurY.iY() > GetActorLocation().iY()) // 날거나 점프했을때
		{
			CamMoveY = (FVector::Down * CurY) - (FVector::Down * GetActorLocation()); // Kirby의 Y축 변화가 
			CamMoveY = CamMoveY * FVector::Up; // -(Up)일 때 계산하여
			GetWorld()->AddCameraPos(CamMoveY * CamYSpeed); // 그 수치 만큼 카메라 Y축에 더해준다.
		}
		else if (CurY.iY() < GetActorLocation().iY()) { // 날다가 떨어질 때 
			CamMoveY = (FVector::Down * GetActorLocation()) - (FVector::Down * CurY); // Kirby의 Y축 변화가
			CamMoveY = CamMoveY * FVector::Down; // +(Down)일 때 계산하여
			GetWorld()->AddCameraPos(CamMoveY * CamYSpeed); // 그 수치 만큼 카메라 Y축에 더해준다.
		}
		// 계산 후
		CurY = GetActorLocation(); // 커비의 현재 위치 갱신
	}
	
}

void AKirby_Player::BeginPlay() // 실행했을때 준비되어야 할것들 Set
{
	AActor::BeginPlay();

	MainPlayer = this; // 다른 클래스가 사용하기 위해 본인을 넣는다.

	scale = 3; // ActorCommon -> 랜더링 크기 설정

	// 랜더링 설정
	{
		KirbyRenderer = CreateImageRenderer(ERenderOrder::kirby); // 이미지 랜더 생성
		KirbyRenderer->SetImage("kirby_Right.png"); // 이미지 Set
		KirbyRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // 랜더의 위치 크기 
	}

	{
		effectRenderer= CreateImageRenderer(ERenderOrder::effect);
		effectRenderer->SetImage("Effects.png"); // 이미지 Set//
		effectRenderer->SetTransform({ {0,20}, {64 * 2, 64 * 2} }); // 랜더의 위치 크기 
		effectRenderer->ActiveOff();
	}

	{
		FireRenderer= CreateImageRenderer(ERenderOrder::Fire);
		FireRenderer->SetImage("Fire_Right.png"); // 이미지 Set//
		FireRenderer->ActiveOff();
	}

	manual = CreateImageRenderer(ERenderOrder::Menu); // 이미지 랜더 생성
	manual->SetImage("menu.png"); // 이미지 Set
	manual->SetTransform({ {0,-200}, {64 * 10, 64 * 10} }); // 랜더의 위치 크기 
	manual->ActiveOff();
	AniCreate(); // 애니메이션 종합 관리

	// 콜리전 설정
	{
		KirbyCollision = CreateCollision(ECollisionOrder::kirby); 
		KirbyCollision->SetScale({ 60, 60 });
		KirbyCollision->SetColType(ECollisionType::Rect); // 콜리전 타입은 사각형 충돌
	}

	{
		FireCollision= CreateCollision(ECollisionOrder::FireAttack);
		FireCollision->SetColType(ECollisionType::Rect);
		FireCollision->ActiveOff();
	}

	StateAniChange(EActorState::Idle); // 시작 애니메이션

	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> 이전 코드
}

// 커비 움직임 업데이트
void AKirby_Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	StateUpdate(_DeltaTime);
}

// 애니메이션 생성 관리
void AKirby_Player::AniCreate()
{
	effectRenderer->CreateAnimation("effect", "Effects.png", { 6,7,6,7,6,7 }, false);
	FireRenderer->CreateAnimation("Fire_Right", "Fire_Right.png", 140, 156,0.06f, true);
	FireRenderer->CreateAnimation("Fire_Left", "Fire_Left.png", 140, 156, 0.06f, true);
	// (오른쪽, 왼쪽)
	// (1) Base
	// 기본 서있는 모션(완)
	KirbyRenderer->CreateAnimation("Base_Idle_Right", "kirby_Right.png", 0, 1, 0.5f, true); // 오른쪽 서 있기
	KirbyRenderer->CreateAnimation("Base_Idle_Left", "kirby_Left.png", 0, 1, 0.5f, true); // 왼쪽 서있기

	// 기본 걷는 모션(완)
	KirbyRenderer->CreateAnimation("Base_Walk_Right", "kirby_Right.png", 10, 19, 0.07f, true); // 걷기
	KirbyRenderer->CreateAnimation("Base_Walk_Left", "kirby_Left.png", 10, 19, 0.07f, true); // 걷기

	// 기본 뛰는 모션(완)
	KirbyRenderer->CreateAnimation("Base_run_Right", "kirby_Right.png", 20, 27, 0.04f, true);
	KirbyRenderer->CreateAnimation("Base_run_Left", "kirby_Left.png", 20, 27, 0.04f, true);

	// 기본 점프 모션(완)
	KirbyRenderer->CreateAnimation("Base_Jump_Right", "kirby_Right.png", 38, 51, 0.06f, true);
	KirbyRenderer->CreateAnimation("Base_Jump_Left", "kirby_Left.png", 38, 51, 0.06f, true);

	// 기본 나는 모션
	KirbyRenderer->CreateAnimation("Base_FlyReady_Right", "kirby_Right.png", 53, 57, 0.08f, false);
	KirbyRenderer->CreateAnimation("Base_FlyReady_Left", "kirby_Left.png", 53, 57, 0.08f, false);
	KirbyRenderer->CreateAnimation("Base_Fly_Right", "kirby_Right.png", 58, 65, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_Fly_Left", "kirby_Left.png", 58, 65, 0.1f, true);

	// 기본 떨어지는 모션
	KirbyRenderer->CreateAnimation("Base_fall_Right", "kirby_Right.png", { 66,67,35,36,37 }, 0.1f, false);
	KirbyRenderer->CreateAnimation("Base_fall_Left", "kirby_Left.png", { 66,67,35,36,37 }, 0.1f, false);
	
	// 기본 숙이기 
	KirbyRenderer->CreateAnimation("Base_HeadDown_Right", "kirby_Right.png", 2, 3, 0.5f, true);
	KirbyRenderer->CreateAnimation("Base_HeadDown_Left", "kirby_Left.png", 2, 3, 0.5f, true);

	// 충돌 애니메이션
	KirbyRenderer->CreateAnimation("Base_hit_Right", "kirby_Right.png", { 51,50,49,48,47,46,45,44,43,42,41,40 }, 0.04f, true);
	KirbyRenderer->CreateAnimation("Base_hit_Left", "kirby_Left.png", { 51,50,49,48,47,46,45,44,43,42,41,40 }, 0.04f, true);

	KirbyRenderer->CreateAnimation("Icehit_Right", "hitKirby_Right.png", 5,9, 0.1f, false);
	KirbyRenderer->CreateAnimation("Icehit_Left", "hitKirby_Left.png", 5,9, 0.1f, false);

	KirbyRenderer->CreateAnimation("hothit_Right", "hitKirby_Right.png", 0, 3, 0.1f, false);
	KirbyRenderer->CreateAnimation("hothit_Left", "hitKirby_Left.png", 0, 3, 0.1f, false);

	// ---기본에서만 가능한 모션들----
	// Heavy 모드 Idle
	KirbyRenderer->CreateAnimation("HeavyIdle_Right", "kirby2_Right.png", 19, 20, 0.5f, true);
	KirbyRenderer->CreateAnimation("HeavyIdle_Left", "kirby2_Left.png", 19, 20, 0.5f, true);

	// Heavy모드 Move
	KirbyRenderer->CreateAnimation("HeavyMove_Right", "kirby2_Right.png", 23, 33, 0.06f, true);
	KirbyRenderer->CreateAnimation("HeavyMove_Left", "kirby2_Left.png", 23, 33, 0.06f, true);

	// Heavy모드 Move
	KirbyRenderer->CreateAnimation("HeavyJump_Right", "kirby2_Right.png", 34, 41, 0.09f, true);
	KirbyRenderer->CreateAnimation("HeavyJump_Left", "kirby2_Left.png", 34, 41, 0.09f, true);
	

	// 기본 흡수 
	KirbyRenderer->CreateAnimation("Base_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
	KirbyRenderer->CreateAnimation("Base_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);
	


	//-- 파이어 커비 
	KirbyRenderer->CreateAnimation("Fire_Idle_Right", "Fire_Right.png", 0,6, 0.2f, true); // 오른쪽 서 있기
	KirbyRenderer->CreateAnimation("Fire_Idle_Left", "Fire_Left.png", 0,6, 0.2f, true); // 왼쪽 서있기

	// 파이어 걷는 모션
	KirbyRenderer->CreateAnimation("Fire_Walk_Right", "Fire_Right.png", 32,50, 0.045f, true); // 걷기
	KirbyRenderer->CreateAnimation("Fire_Walk_Left", "Fire_Left.png", 32,50, 0.045f, true); // 걷기

	// 파이어 뛰는 모션
	KirbyRenderer->CreateAnimation("Fire_run_Right", "Fire_Right.png", 53, 59, 0.08f, true);
	KirbyRenderer->CreateAnimation("Fire_run_Left", "Fire_Left.png", 53, 59, 0.08f, true);

	// 파이어 점프 모션
	KirbyRenderer->CreateAnimation("Fire_Jump_Right", "Fire_Right.png", 21, 31, 0.07f, true);
	KirbyRenderer->CreateAnimation("Fire_Jump_Left", "Fire_Left.png",21, 31, 0.07f, true);

	// 파이어 나는 모션
	KirbyRenderer->CreateAnimation("Fire_FlyReady_Right", "Fire_Right.png", 65, 69, 0.08f, false);
	KirbyRenderer->CreateAnimation("Fire_FlyReady_Left", "Fire_Left.png", 65, 69, 0.08f, false);
	KirbyRenderer->CreateAnimation("Fire_Fly_Right", "Fire_Right.png", 70, 94, 0.08f, true);
	KirbyRenderer->CreateAnimation("Fire_Fly_Left", "Fire_Left.png", 70, 94, 0.08f, true);

	// 파이어 떨어지는 모션
	KirbyRenderer->CreateAnimation("Fire_fall_Right", "Fire_Right.png", 97, 101, 0.1f, false);
	KirbyRenderer->CreateAnimation("Fire_fall_Left", "Fire_Left.png", 97, 101, 0.1f, false);
	// 파이어 숙이기 
	KirbyRenderer->CreateAnimation("Fire_HeadDown_Right", "Fire_Right.png", 8, 9, 0.5f, true);
	KirbyRenderer->CreateAnimation("FIre_HeadDown_Left", "Fire_Left.png", 8, 9, 0.5f, true);

	// 파이어 숙이기 
	KirbyRenderer->CreateAnimation("Fire_FireReady_Right", "Fire_Right.png", 122, 128, 0.08f, true);
	KirbyRenderer->CreateAnimation("FIre_FireReady_Left", "Fire_Left.png", 122, 128, 0.08f, true);
	KirbyRenderer->CreateAnimation("Fire_FireAttack_Right", "Fire_Right.png", 129, 131, 0.08f, true);
	KirbyRenderer->CreateAnimation("FIre_FireAttack_Left", "Fire_Left.png", 129, 131, 0.08f, true);

	KirbyRenderer->CreateAnimation("Fire_hit_Right", "Fire_Right.png", {115,114,113,112,111,110,109,108,107,106,105,104,103,102,101}, 0.05f, true);
	KirbyRenderer->CreateAnimation("Fire_hit_Left", "Fire_Left.png", { 115,114,113,112,111,110,109,108,107,106,105,104,103,102,101 }, 0.05f, true);



	// 파이어 흡수 -> 기본에서 아이스 중간 이미지 
	KirbyRenderer->CreateAnimation("Fire_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
	KirbyRenderer->CreateAnimation("Fire_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);

	//-- 아이스 커비
	KirbyRenderer->CreateAnimation("Ice_Idle_Right", "Ice_Right.png", 0, 1, 0.5f, true); // 오른쪽 서 있기
	KirbyRenderer->CreateAnimation("Ice_Idle_Left", "Ice_Left.png", 0, 1, 0.5f, true); // 왼쪽 서있기

	// 아이스 걷는 모션
	KirbyRenderer->CreateAnimation("Ice_Walk_Right", "Ice_Right.png", 32, 39, 0.075f, true); // 걷기
	KirbyRenderer->CreateAnimation("Ice_Walk_Left", "Ice_Left.png", 32, 39, 0.075f, true); // 걷기

	// 아이스 뛰는 모션
	KirbyRenderer->CreateAnimation("Ice_run_Right", "Ice_Right.png", 42, 49, 0.05f, true);
	KirbyRenderer->CreateAnimation("Ice_run_Left", "Ice_Left.png", 42, 49, 0.05f, true);

	// 아이스 점프 모션
	KirbyRenderer->CreateAnimation("Ice_Jump_Right", "Ice_Right.png", 80, 90, 0.07f, true);
	KirbyRenderer->CreateAnimation("Ice_Jump_Left", "Ice_Left.png", 80, 90, 0.07f, true);

	// 아이스 나는 모션
	KirbyRenderer->CreateAnimation("Ice_FlyReady_Right", "Ice_Right.png", 54, 58, 0.08f, false);
	KirbyRenderer->CreateAnimation("Ice_FlyReady_Left", "Ice_Left.png", 54, 58, 0.08f, false);
	KirbyRenderer->CreateAnimation("Ice_Fly_Right", "Ice_Right.png", 59, 74, 0.08f, true);
	KirbyRenderer->CreateAnimation("Ice_Fly_Left", "Ice_Left.png", 59, 74, 0.08f, true);

	// 아이스 떨어지는 모션
	KirbyRenderer->CreateAnimation("Ice_fall_Right", "Ice_Right.png", 75, 79, 0.1f, false);
	KirbyRenderer->CreateAnimation("Ice_fall_Left", "Ice_Left.png", 75, 79, 0.1f, false);
	// 아이스 숙이기 
	KirbyRenderer->CreateAnimation("Ice_HeadDown_Right", "Ice_Right.png", 10, 11, 0.5f, true);
	KirbyRenderer->CreateAnimation("Ice_HeadDown_Left", "Ice_Left.png", 10, 11, 0.5f, true);

	KirbyRenderer->CreateAnimation("Ice_hit_Right", "Ice_Right.png", { 90,89,88,87,86,85,84,83,82,81,80,79 }, 0.05f, true);
	KirbyRenderer->CreateAnimation("Ice_hit_Left", "Ice_Left.png", { 90,89,88,87,86,85,84,83,82,81,80,79 }, 0.05f, true);

	// 아이스 공격
	KirbyRenderer->CreateAnimation("Ice_IceAttack_Right", "Ice_Right.png", 94, 103, 0.05f, true);
	KirbyRenderer->CreateAnimation("Ice_IceAttack_Left", "Ice_Left.png", 94, 103, 0.05f, true);

	// 아이스 흡수 -> 기본에서 아이스 중간 이미지 
	KirbyRenderer->CreateAnimation("Ice_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
	KirbyRenderer->CreateAnimation("Ice_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);


	// 모든 커비모드에서 사용 가능한 애니메이션
	KirbyRenderer->CreateAnimation("AllAttack_Right", "kirby2_Right.png", 42, 52, 0.03f, false);
	KirbyRenderer->CreateAnimation("AllAttack_Left", "kirby2_Left.png", 42, 52, 0.03f, false);
}

// 커비 모드 체인지 관리
void AKirby_Player::KirbyModeCheck()
{
	if (std::string(GetModeName()) != "Base_") // 기본 커비 형태의 문자열이 아닌 경우
	{
		if (std::string(GetModeName()) == "Ice_") // 아이스 문자열이면
		{
			SetMode(EAMode::Ice); // 아이스 형태로
		}
		else if (std::string(GetModeName()) == "Fire_") // 소드 문자열이면
		{
			SetMode(EAMode::Fire); // 소드 형태로
		}
	}
}

void AKirby_Player::GroundUp()
{
	while (true)
	{
		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY()-1, Color8Bit::RedA);
		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			AddActorLocation(FVector::Up*2);
		}
		else
		{
			break;
		}
	}
}

// 중력 제어
void AKirby_Player::CalGravityVector(float _DeltaTime)
{
	GravityVector += GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime); // 중력은 계속 가해진다.

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0)) // ColMapImage에서 빨간색과 일치하는 경우
	{
		GravityVector = FVector::Zero; // 중력의 힘은 0으로
	}
}

// 최종 이동 관리
void AKirby_Player::MoveLastMoveVector(float _DeltaTime, const FVector& _MovePos)
{
	// 제로로 만들어서 초기화 시킨다.
	PlayMove = FVector::Zero; // Kirby 이동 관리
	
	PlayMove = PlayMove + JumpVector;

	if (false == FlyState) // 날지 않은 경우
	{
		PlayMove = PlayMove + GravityVector; // 중력 영향 O
	}
	else { // 나는 경우
		GravityVector = FVector::Zero; // 중력의 영향 X
	}

	FVector MovePos = _MovePos;
	
	FVector CheckPos = GetActorLocation(); // Kirby
	FVector CamCheckPos = GetActorLocation(); // camera

	// 방향 별 픽셀 충돌 인식 범위
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= checkposX;
		CamCheckPos.X -= 3.0f;// 3으로 우선 고정
		break;
	case EActorDir::Right:
		CheckPos.X += checkposX;
		CamCheckPos.X += 3.0f;
		break;
	default:
		break;
	}

	CheckPos.Y -= checkposY;
	CamCheckPos.Y -= checkposY;

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::RedA);
	Color8Bit ColorG = UActorCommon::ColMapImage->GetColor(CamCheckPos.iX(), CamCheckPos.iY(), Color8Bit::GreenA);
	Color8Bit ColorB = UActorCommon::ColMapImage->GetColor(CamCheckPos.iX(), CamCheckPos.iY(), Color8Bit::BlueA);
	Color8Bit ColorM = UActorCommon::ColMapImage->GetColor(CamCheckPos.iX(), CamCheckPos.iY(), Color8Bit::MagentaA);

	if (ColorR == Color8Bit(255, 0, 0, 0)) // 벽(Red)랑 충돌인 경우 -> 움직이는 값 0
	{
		MovePos = FVector::Zero;
	}

	AddActorLocation(MovePos + (PlayMove * _DeltaTime)); // 최종 Kirby 움직임 계산 X축(게임 조작을 통한 값)과 Y축 (중력, 점프)

	if (ColorG != Color8Bit(0, 255, 0, 0) && ColorB != Color8Bit(0, 0, 255, 0) && ColorM != Color8Bit(255, 0, 255, 0)) // 초록, 파랑, 마젠타 픽셀 충돌이 없는 경우
	{
		// 카메라 최종 이동
		FVector Move = (MovePos * FVector::Right) + CamstopMove; // 
	
		GetWorld()->AddCameraPos(Move);
		
		CamstopMove = FVector::Zero;

	}
	else {

		CamstopMove += (MovePos * FVector::Right);
	}
}



void AKirby_Player::MoveUpdate(float _DeltaTime, const FVector& _MovePos)
{
	CalGravityVector(_DeltaTime);
	MoveLastMoveVector(_DeltaTime, _MovePos);
	GroundUp();
}

//----------------------------------------------------------------------------------------------------

void AKirby_Player::DirCheck() // 커비 왼쪽 오른쪽 방향 체크
{
	EActorDir Dir = DirState;
	if (UEngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
	}

	if (Dir != DirState && false==SkillOn) // 스킬 사용중에는 방향 전환 불가능
	{
		DirState = Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		KirbyRenderer->ChangeAnimation(Name, true,KirbyRenderer->GetCurAnimationFrame(), KirbyRenderer->GetCurAnimationTime());
	}
}

// 최종 변경해야할 애니메이션 관리
std::string AKirby_Player::GetAnimationName(std::string_view _Name)
{
	std::string DirName = "";

	// 방향 체크
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

	if (std::string(_Name) == "AllAttack" || std::string(_Name) == "HeavyIdle" || std::string(_Name) == "HeavyMove" || std::string(_Name) == "HeavyJump" || std::string(_Name) == "Icehit" || std::string(_Name) == "hothit") // AllAttack은 모든 커비모드에서 사용 가능하기에
	{
		return std::string(_Name) + DirName; // // 앞에 GetModeName없이 AllAttack 문자열과 방향만 리턴
	}
	return std::string(GetModeName()) + std::string(_Name) + DirName; // 최종 변경해야할 애니메이션 이름 (커비 모드) + 애니메이션 이름 + (방향)
}

// 커비의 움직임 상태에 맞는 애니메이션 실행
void AKirby_Player::StateAniChange(EActorState _State) 
{
	
	// 커비 형태의 문자열에 맞게 커비 모드를 설정 해준다.
	//KirbyModeCheck();

	// 이전상태와 현재 상태가 다른 경우 와 몬스터와의 충돌이 안했을 때 실행
	// ex) 이전에는 move 지금은 Idle
	if (State != _State && false==hitState)
	{
		switch (_State) // 상태별 애니메이션 스타트
		{
		case EActorState::Idle:
			if (true == EatState && KirbyMode == EAMode::Base) // Eat상태 (먹은상태) 는 커비가 기본 모드일때만 체크후 변경한다.
			{
				HeavyIdleStart(); // Heavy는 기본 형태의 커비에서만 가능한 애니메이션
			}
			else
			{
				IdleStart();
			}
			break;
		case EActorState::Walk:
			if (true == EatState && KirbyMode == EAMode::Base) // 동일
			{
				checkSpeed = HeavyWalkSpeed;
				HeavyMoveStart();
			}
			else
			{
				checkSpeed = WalkSpeed;
				WalkStart();;
			}
			break;
		case EActorState::Run:
			if (true == EatState && KirbyMode == EAMode::Base) // 동일
			{
				checkSpeed = HeavyRunSpeed;
				HeavyMoveStart();
			}
			else
			{
				checkSpeed = RunSpeed;
				RunStart();
			}
			break;
		case EActorState::Jump:
			if (true == EatState && KirbyMode == EAMode::Base) // 동일
			{
				HeavyJumpStart();
			}
			else
			{
				JumpStart();
			}
			break;
		case EActorState::FlyReady:
			FlyReadyStart();
			break;
		case EActorState::Fly:
			checkSpeed = FlySpeed;
			FlyStart();
			break;
		case EActorState::Flyfall:
			FlyFallStart();
			break;
		case EActorState::Absorption:
			AbsorptionStart();
			break;
		case EActorState::IceAttack:
			IceAttackStart();
			break;
		case EActorState::FireReady:
			FireReadyStart();
			break;
		case EActorState::FireAttack:
			FireAttackStart();
			break;
		case EActorState::HeadDown:
			HeadDownStart();
			break;
		case EActorState::All_Attack:
			AllAttackStart();
			break;
		default:
			break;
		}
	}

	if (true == hitState) // 몬스터와 충돌인 상황에서
	{
		State = EActorState::hit; // 현재 상태는 hit로 리턴
		return;
	}

	State = _State; // 일반적인 상황은 _State로 저장
}

void AKirby_Player::StateUpdate(float _DeltaTime)
{
	if (false == hitState) // 몬스터와 충돌하지 않은 상태에서만 상태에 따른 조작 가능
	{
		switch (State) // 현재 상태별 진행해야하는 형태
		{
		case EActorState::Idle: // 서있기
			Idle(_DeltaTime);
			break;
		case EActorState::Walk: // 걷기
			Walk(_DeltaTime);
			break;
		case EActorState::Run: // 걷기
			Run(_DeltaTime);
			break;
		case EActorState::Jump: // 점프
			Jump(_DeltaTime);
			break;
		case EActorState::FlyReady: // 날기 준비
			FlyReady(_DeltaTime);
			break;
		case EActorState::Fly: // 날기
			Fly(_DeltaTime);
			break;
		case EActorState::Flyfall: // 날다가 추락
			Flyfall(_DeltaTime);
			break;
		case EActorState::HeadDown: // 숙이기
			HeadDown(_DeltaTime);
			break;
		case EActorState::All_Attack: // 흡수 후 가능 -> 별 뱉기 공격
			All_Attack(_DeltaTime);
			break;
		case EActorState::Absorption: // 흡수
			ModeInputTick(_DeltaTime);
			break;
		case EActorState::IceAttack: // 아이스 공격
			ModeInputTick(_DeltaTime);
			break;
		case EActorState::FireReady: // 아이스 공격
			FireReady( _DeltaTime);
			break;
		case EActorState::FireAttack: // 아이스 공격
			ModeInputTick(_DeltaTime);
			break;
		default:
			break;
		}
	}
	else { // 몬스터와 충돌시 실행
		hit(_DeltaTime);
	}
	
}

void AKirby_Player::Idle(float _DeltaTime)
{
	// 왼쪽 오른쪽도 안되고 있고.
	// 여기서는 정말
	// 가만히 있을때만 어떻게 할지 신경쓰면 됩니다.
	CurY = GetActorLocation(); // 카메라 Y축 계산을 위한 현재 커비 위치를 저장
	
	if (true == transform)
	{
		
		transform = false;
		GetWorld()->SetAllTimeScale(1.0f);
		effectRenderer->ActiveOff();
		
	}

	// 테스트 모드



	
	Color8Bit ColorB = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::BlueA);
	
	if (true == UEngineInput::IsDown(VK_UP) && StageCheck == 1)
	{
		// && ColorB != Color8Bit(0, 0, 255, 0)
		if (false == CreateStage2)
		{
			CreateStage2 = true;
			GEngine->CreateLevel<UStage2_Level>("Stage2_Level"); // stage1_Level 생성
		}
		StageCheck = 2;
		GEngine->ChangeLevel("Stage2_Level");
	}else if (true == UEngineInput::IsDown(VK_UP) && StageCheck == 2)// 초록, 파랑, 마젠타 픽셀 충돌이 없는 경우
	{
		// && ColorB != Color8Bit(0, 0, 255, 0)
		//if (false == CreateStage2)
		//{
			//GEngine->CreateLevel<UStage2_Level>("Stage2_Level"); // stage1_Level 생성
		//}
		
		//return;
		StageCheck = 1;
		GEngine->ChangeLevel("Stage1_Level");
	}

	if (true == UEngineInput::IsDown('1'))
	{
		
		if (true == manual->IsActive())
		{
			manual->ActiveOff();
		}
		else
		{
			manual->ActiveOn();
		}
	}

	if (true == UEngineInput::IsDown('2'))
	{
		if (DirState == EActorDir::Left)
		{
			GetWorld()->SpawnActor<AMonster_Base>()->SetActorLocation({ GetActorLocation().iX() - 200,600 });
		}
		else {
			GetWorld()->SpawnActor<AMonster_Base>()->SetActorLocation({ GetActorLocation().iX() + 300,600 });
		}
		
		Hp = 100;
		return;
	}

	if (true == UEngineInput::IsDown('3'))
	{
		if (DirState == EActorDir::Left)
		{
			GetWorld()->SpawnActor<Apengi_Ice>()->SetActorLocation({ GetActorLocation().iX() - 200,600 });
		}
		else {
			GetWorld()->SpawnActor<Apengi_Ice>()->SetActorLocation({ GetActorLocation().iX() + 300,600 });
		}
		Hp = 100;
		return;
	}

	if (true == UEngineInput::IsDown('4'))
	{
		if (DirState == EActorDir::Left)
		{
			GetWorld()->SpawnActor<AMonster_Fire>()->SetActorLocation({ GetActorLocation().iX() - 200,700 });
		}
		else {
			GetWorld()->SpawnActor<AMonster_Fire>()->SetActorLocation({ GetActorLocation().iX() + 300,700 });
		}
		Hp = 100;
		return;
	}

	// 걷기
	if (
		true == UEngineInput::IsPress(VK_LEFT) ||
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		StateAniChange(EActorState::Walk);
		return;
	}

	// 점프
	if (
		true == UEngineInput::IsDown('S') 
		)
	{
		JumpVector = JumpPowerIdle;
		StateAniChange(EActorState::Jump);
		return;
	}

	// 숙이기
	if (
		true == UEngineInput::IsPress(VK_DOWN)
		)
	{
		if (true==EatState && GetModeName() == "Base_")
		{
			EatState = false;
		}
		else if (true == EatState &&  GetModeName()!="Base_") {
			transform = true;
			EatState = false;
			effectRenderer->ActiveOn();
			effectRenderer->ChangeAnimation("effect");
			GetWorld()->SetOtherTimeScale(ERenderOrder::kirby, 0.0f);
		}
		StateAniChange(EActorState::HeadDown);
		return;
	}

	// 커비 모드에 따른 스킬 공격
	if (
		true == UEngineInput::IsPress('X') && false == EatState && KirbyMode == EAMode::Base
		)
	{
		SkillOn = true;
		StateAniChange(EActorState::Absorption);
		ABase* NewBase = GetWorld()->SpawnActor<ABase>();
		NewBase->SetActorLocation(this->GetActorLocation());

		if (DirState == EActorDir::Left)
		{
			NewBase->SetDir(FVector::Left);
		}
		else {
			NewBase->SetDir(FVector::Right);
		}
		return;
	}
	else if(true == UEngineInput::IsPress('X') && KirbyMode==EAMode::Ice ){
		SkillOn = true;
		StateAniChange(EActorState::IceAttack);
		AIce* NewIce = GetWorld()->SpawnActor<AIce>();
		NewIce->SetOwner(EIceOwner::kirby);

		if (DirState == EActorDir::Left)
		{
			NewIce->SetDir(FVector::Left);
		}
		else {
			NewIce->SetDir(FVector::Right);
		}

	
		NewIce->SetActive(true, 0.22f);
		NewIce->SetOwner(EIceOwner::kirby);
		NewIce->SetActorLocation(this->GetActorLocation());
		return;
	}
	else if (true == UEngineInput::IsPress('X') && KirbyMode == EAMode::Fire) {
		SkillOn = true;
		FireRenderer->SetActive(true, 0.4f);
		FireCollision->SetActive(true, 0.6f);
		if (DirState == EActorDir::Left)
		{
			FireRenderer->ChangeAnimation("Fire_Left");
			FireRenderer->SetTransform({ { -140, 5}, { 64*6,64*4 } });
			FireCollision->SetTransform({ {-140,-5},{100,70} });
		}
		else {
			FireRenderer->ChangeAnimation("Fire_RIght");
			FireRenderer->SetTransform({ { 140,5}, { 64*6,64*4}});
			FireCollision->SetTransform({ {140,-5},{100,70} });
		}
		StateAniChange(EActorState::FireReady);
		return;
	}

	// 별 뱉기 공격 (모든 커비모드에서 사용 가능)
	if (
		true == UEngineInput::IsDown('A') && (true==EatState || KirbyMode != EAMode::Base)
		)
	{
		SkillOn = true;
		StateAniChange(EActorState::All_Attack);
		AAllStar* NewStar = GetWorld()->SpawnActor<AAllStar>();
		NewStar->SetActorLocation(this->GetActorLocation());

		if (DirState == EActorDir::Left)
		{
			NewStar->SetDir(FVector::Left);
		}
		else {
			NewStar->SetDir(FVector::Right);
		}
		return;
	}

	MoveUpdate(_DeltaTime);
}

void AKirby_Player::Jump(float _DeltaTime)
{
	DirCheck(); // 방향 체크

	FVector MovePos;

	// 점프 도중 X축 이동
	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * checkSpeed * _DeltaTime;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * checkSpeed * _DeltaTime;
	}

	// 점프 도중 Fly
	if (UEngineInput::IsDown('S'))
	{
		switch (KirbyMode)
		{
		case EAMode::Base:
			// Base에서는 EatState가 true이면 날지 못한다.
			if (false == EatState)
			{
				StateAniChange(EActorState::FlyReady);
				return;
			}
			break;
		default:
			StateAniChange(EActorState::FlyReady);
			return;
			break;
		}
	}

	MoveUpdate(_DeltaTime,MovePos); // 최종 움직임

	CamYMove(); // 카메라 Y축 계산
	
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	
	if (ColorR == Color8Bit(255, 0, 0, 0)) // 픽셀 충돌 -> 점프 후 착지할때
	{
		JumpVector = FVector::Zero; // 점프력 힘은 0
		StateAniChange(EActorState::Idle); // Idle 변화
		return;
	}
}

// 날기 위한 준비 모션
void AKirby_Player::FlyReady(float _DeltaTime)
{
	DirCheck(); 

	FlyState = true; // 날기 위한 Bool값 True
	JumpVector = FVector::Zero; // 점프력 0
	
	if (true == KirbyRenderer->IsCurAnimationEnd()) //  해당 애니메이션 종료 후
	{
		StateAniChange(EActorState::Fly); // 날기로 전환
		return;
	}
}

void AKirby_Player::Fly(float _DeltaTime)
{
	DirCheck();

	// 나는 도중 X키 누를 경우 -> 떨어짐
	if (UEngineInput::IsDown('X'))
	{
		FlyState = false;
		StateAniChange(EActorState::Flyfall);
		return;
	}

	FVector MovePos= FVector::Zero;
	
	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		MovePos += FVector::Up * _DeltaTime * 100.0f;
	}
	else {
		MovePos += FVector::Down * _DeltaTime * 100.0f;
	}

	MoveUpdate(_DeltaTime, MovePos);
	CamYMove();
	// 천장 픽셀 충돌 -> 추락
	Color8Bit ColorM = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY()-40, Color8Bit::MagentaA);
	if (ColorM == Color8Bit(255, 0, 255, 0) )
	{
		FlyState = false;
		StateAniChange(EActorState::Flyfall);
	    return;
	}

	// 바닥 픽셀 충돌  -> 추락
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{

		FlyState = false;
		StateAniChange(EActorState::Flyfall);
		return;
	}
}

// 날다가 추락할 때
void AKirby_Player::Flyfall(float _DeltaTime)
{
	
	DirCheck();
	
	FVector MovePos = FVector::Zero;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * checkSpeed;
	}

	MoveUpdate(_DeltaTime, MovePos);
	CamYMove();
	// 추락해서 바닥과 충돌할 경우
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		JumpVector = FVector::Zero;
		StateAniChange(EActorState::Idle);
		return;
	}
}

void AKirby_Player::HeadDown(float _DeltaTime)
{
	DirCheck();
	KirbyModeCheck();

	if (true == UEngineInput::IsFree(VK_DOWN))
	{
		StateAniChange(EActorState::Idle);
		return;
	}

	MoveUpdate(_DeltaTime);
}

// 몬스터와 충돌하는 경우
void AKirby_Player::hit(float _DeltaTime)
{
	DirCheck();

	FVector Move = FVector::Zero;
	JumpVector = FVector::Zero; // 점프 도중에 충돌할 경우 -> 점프력 0

	// 몬스터와 반대 방향으로 이동해야하기 위해
	if (DirState == EActorDir::Left) // 왼쪽일 때는 
	{
		Move = FVector::Right * 60.0f * _DeltaTime; // 오른쪽
	}
	else { // 오른쪽일 때는
		Move = FVector::Left * 60.0f * _DeltaTime; // 왼쪽
	}

	
	Color8Bit ColorG = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::GreenA);
	//Color8Bit ColorB = UActorCommon::ColMapImage->GetColor(CamCheckPos.iX(), CamCheckPos.iY(), Color8Bit::BlueA);
	// 커비 충돌 시 이동 제어
	AddActorLocation(Move);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // 공중에서 충돌할 수 있기에 중력 작용
	FlyState = false; // 날다가 추락할 경우
	
	CamstopMove += Move;
	CamYMove(); // Y축

	// 애니메이션 종료 시 다시 원래 상태로 돌아감
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		hitState = false;
		KirbyRenderer->SetAlpha(1.0f);
		KirbyCollision->SetActive(true, 0.1f);
		
	}
	StateAniChange(EActorState::Idle);
	return;
}


void AKirby_Player::Walk(float _DeltaTime)
{
	DirCheck();
	

	if (true == UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		StateAniChange(EActorState::Idle);
		return;
	}

	FVector MovePos = FVector::Zero;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime* checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime*checkSpeed;
	}

	if (UEngineInput::IsPress(VK_SHIFT))
	{
		StateAniChange(EActorState::Run);
		return;
	}

	if (true == UEngineInput::IsDown('S'))
	{
		JumpVector = JumpPowerMove;
		StateAniChange(EActorState::Jump);
		return;
	}


	MoveUpdate(_DeltaTime, MovePos);

	CamYMove();
}

void AKirby_Player::Run(float _DeltaTime)
{
	DirCheck();
	

	if (UEngineInput::IsFree(VK_SHIFT))
	{
		StateAniChange(EActorState::Walk);
		return;
	}
	else if (UEngineInput::IsPress(VK_SHIFT) && UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		StateAniChange(EActorState::Idle);
		return;
	}

	FVector MovePos = FVector::Zero;
	if (UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsPress(VK_SHIFT))
	{
		MovePos += FVector::Left * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT) && UEngineInput::IsPress(VK_SHIFT))
	{
		MovePos += FVector::Right * _DeltaTime * checkSpeed;
	}

	MoveUpdate(_DeltaTime, MovePos);

	CamYMove();
}

void AKirby_Player::Absorption(float _DeltaTime)
{
	
	DirCheck();
	
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		SkillOn = false;
		StateAniChange(EActorState::Idle);
		return;
	}

	MoveUpdate(_DeltaTime);
}

void AKirby_Player::All_Attack(float _DeltaTime)
{
	DirCheck();
	
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		SkillOn = false;
		EatState = false;
		SetModeName("Base_");
		SetMode(EAMode::Base);
		StateAniChange(EActorState::Idle);
		return;
	}

	MoveUpdate(_DeltaTime);
}

// 애니메이션 스타트 관리
void AKirby_Player::IdleStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Idle"));
}

void AKirby_Player::HeavyIdleStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("HeavyIdle"));
}

void AKirby_Player::WalkStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Walk"));
}

void AKirby_Player::HeavyMoveStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("HeavyMove"));
	
}

void AKirby_Player::JumpStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Jump"));
}

void AKirby_Player::HeavyJumpStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("HeavyJump"));
}

void AKirby_Player::HitStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Hit"));
}

void AKirby_Player::IcehitStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Icehit"));
}

void AKirby_Player::hothitStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("hothit"));
}

void AKirby_Player::FlyReadyStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("FlyReady"));
}

void AKirby_Player::FlyStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Fly"));
}

void AKirby_Player::FlyFallStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("fall"));
}

void AKirby_Player::RunStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Run"));
	
}

void AKirby_Player::AbsorptionStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Absorption"));
}

void AKirby_Player::IceAttackStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("IceAttack"));
}

void AKirby_Player::FireReadyStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("FireReady"));
}

void AKirby_Player::FireAttackStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("FireAttack"));
}

void AKirby_Player::HeadDownStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("HeadDown"));
}

void AKirby_Player::AllAttackStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("AllAttack"));
}

//------------------------------------------------------------------------------

void AKirby_Player::ModeInputTick(float _DeltaTime) // 커비 속성 별 할 것들
{
	switch (KirbyMode)
	{
	case EAMode::Base:
		//SetNamechange("Base_");
		Absorption(_DeltaTime);
		break;
	case EAMode::Ice:
		IceKirby(_DeltaTime);
		break;
	case EAMode::Fire:
		FireKirby(_DeltaTime);
		break;
	case EAMode::Mike:
		break;
	case EAMode::Sword:
		break;
	case EAMode::Hammer:
		break;
	default:
		break;
	}
}

void AKirby_Player::FireReady(float _DeltaTime)
{
	DirCheck();

	if (true == KirbyRenderer->IsCurAnimationEnd()) //  해당 애니메이션 종료 후
	{
		StateAniChange(EActorState::FireAttack); // 날기로 전환
		return;
	}
}

void AKirby_Player::Collisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == FireCollision->CollisionCheck(ECollisionOrder::Monster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("터져야겠지....");
		}
		Monster->Destroy();
	}
	else if (true == FireCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("터져야겠지....");
		}
		Monster->Destroy();
	}
	else if (true == FireCollision->CollisionCheck(ECollisionOrder::FireMonster, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Fire* Monster = dynamic_cast<AMonster_Fire*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("터져야겠지....");
		}
		Monster->Destroy();
	}
}

void AKirby_Player::FireKirby(float _DeltaTime)
{
	DirCheck();

	//if (true == KirbyRenderer->IsCurAnimationEnd())
	//{
		//SkillOn = false;
		//StateAniChange(EActorState::Idle);
		//return;
	//}
	Collisiongather(_DeltaTime);
	if (true == UEngineInput::IsUp('X'))
	{
		SkillOn = false;
		FireRenderer->ActiveOff();
		FireCollision->ActiveOff();
		StateAniChange(EActorState::Idle);
		return;
	}

	MoveUpdate(_DeltaTime);
}

void AKirby_Player::IceKirby(float _DeltaTime)
{
	DirCheck();

	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		SkillOn = false;
		StateAniChange(EActorState::Idle);
		return;
	}

	MoveUpdate(_DeltaTime);
}


