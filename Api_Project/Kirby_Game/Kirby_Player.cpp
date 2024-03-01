#include "Kirby_Player.h"

#include <EnginePlatform\EngineInput.h> // Level1 -> �Է� ���(����)
#include <EngineCore/EngineCore.h> // GetWorld ��� -> Level ���� �̿�

#include "AllStar.h"
#include "Fire.h"
#include "Base.h"
#include "Ice.h"

#include "Stage2_Level.h"
// �׽�Ʈ
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

void AKirby_Player::CamYMove() // ī�޶� Y�� �̵� ���
{
	FVector CamMoveY=FVector::Zero;

	if (CurY.iY() != GetActorLocation().iY()) // Ŀ�� Actor�� Y�� ��ȭ�� �ִ� ���
	{
		if (CurY.iY() > GetActorLocation().iY()) // ���ų� ����������
		{
			CamMoveY = (FVector::Down * CurY) - (FVector::Down * GetActorLocation()); // Kirby�� Y�� ��ȭ�� 
			CamMoveY = CamMoveY * FVector::Up; // -(Up)�� �� ����Ͽ�
			GetWorld()->AddCameraPos(CamMoveY * CamYSpeed); // �� ��ġ ��ŭ ī�޶� Y�࿡ �����ش�.
		}
		else if (CurY.iY() < GetActorLocation().iY()) { // ���ٰ� ������ �� 
			CamMoveY = (FVector::Down * GetActorLocation()) - (FVector::Down * CurY); // Kirby�� Y�� ��ȭ��
			CamMoveY = CamMoveY * FVector::Down; // +(Down)�� �� ����Ͽ�
			GetWorld()->AddCameraPos(CamMoveY * CamYSpeed); // �� ��ġ ��ŭ ī�޶� Y�࿡ �����ش�.
		}
		// ��� ��
		CurY = GetActorLocation(); // Ŀ���� ���� ��ġ ����
	}
	
}

void AKirby_Player::BeginPlay() // ���������� �غ�Ǿ�� �Ұ͵� Set
{
	AActor::BeginPlay();

	MainPlayer = this; // �ٸ� Ŭ������ ����ϱ� ���� ������ �ִ´�.

	scale = 3; // ActorCommon -> ������ ũ�� ����

	// ������ ����
	{
		KirbyRenderer = CreateImageRenderer(ERenderOrder::kirby); // �̹��� ���� ����
		KirbyRenderer->SetImage("kirby_Right.png"); // �̹��� Set
		KirbyRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	}

	{
		effectRenderer= CreateImageRenderer(ERenderOrder::effect);
		effectRenderer->SetImage("Effects.png"); // �̹��� Set//
		effectRenderer->SetTransform({ {0,20}, {64 * 2, 64 * 2} }); // ������ ��ġ ũ�� 
		effectRenderer->ActiveOff();
	}

	{
		FireRenderer= CreateImageRenderer(ERenderOrder::Fire);
		FireRenderer->SetImage("Fire_Right.png"); // �̹��� Set//
		FireRenderer->ActiveOff();
	}

	manual = CreateImageRenderer(ERenderOrder::Menu); // �̹��� ���� ����
	manual->SetImage("menu.png"); // �̹��� Set
	manual->SetTransform({ {0,-200}, {64 * 10, 64 * 10} }); // ������ ��ġ ũ�� 
	manual->ActiveOff();
	AniCreate(); // �ִϸ��̼� ���� ����

	// �ݸ��� ����
	{
		KirbyCollision = CreateCollision(ECollisionOrder::kirby); 
		KirbyCollision->SetScale({ 60, 60 });
		KirbyCollision->SetColType(ECollisionType::Rect); // �ݸ��� Ÿ���� �簢�� �浹
	}

	{
		FireCollision= CreateCollision(ECollisionOrder::FireAttack);
		FireCollision->SetColType(ECollisionType::Rect);
		FireCollision->ActiveOff();
	}

	StateAniChange(EActorState::Idle); // ���� �ִϸ��̼�

	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�
}

// Ŀ�� ������ ������Ʈ
void AKirby_Player::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	StateUpdate(_DeltaTime);
}

// �ִϸ��̼� ���� ����
void AKirby_Player::AniCreate()
{
	effectRenderer->CreateAnimation("effect", "Effects.png", { 6,7,6,7,6,7 }, false);
	FireRenderer->CreateAnimation("Fire_Right", "Fire_Right.png", 140, 156,0.06f, true);
	FireRenderer->CreateAnimation("Fire_Left", "Fire_Left.png", 140, 156, 0.06f, true);
	// (������, ����)
	// (1) Base
	// �⺻ ���ִ� ���(��)
	KirbyRenderer->CreateAnimation("Base_Idle_Right", "kirby_Right.png", 0, 1, 0.5f, true); // ������ �� �ֱ�
	KirbyRenderer->CreateAnimation("Base_Idle_Left", "kirby_Left.png", 0, 1, 0.5f, true); // ���� ���ֱ�

	// �⺻ �ȴ� ���(��)
	KirbyRenderer->CreateAnimation("Base_Walk_Right", "kirby_Right.png", 10, 19, 0.07f, true); // �ȱ�
	KirbyRenderer->CreateAnimation("Base_Walk_Left", "kirby_Left.png", 10, 19, 0.07f, true); // �ȱ�

	// �⺻ �ٴ� ���(��)
	KirbyRenderer->CreateAnimation("Base_run_Right", "kirby_Right.png", 20, 27, 0.04f, true);
	KirbyRenderer->CreateAnimation("Base_run_Left", "kirby_Left.png", 20, 27, 0.04f, true);

	// �⺻ ���� ���(��)
	KirbyRenderer->CreateAnimation("Base_Jump_Right", "kirby_Right.png", 38, 51, 0.06f, true);
	KirbyRenderer->CreateAnimation("Base_Jump_Left", "kirby_Left.png", 38, 51, 0.06f, true);

	// �⺻ ���� ���
	KirbyRenderer->CreateAnimation("Base_FlyReady_Right", "kirby_Right.png", 53, 57, 0.08f, false);
	KirbyRenderer->CreateAnimation("Base_FlyReady_Left", "kirby_Left.png", 53, 57, 0.08f, false);
	KirbyRenderer->CreateAnimation("Base_Fly_Right", "kirby_Right.png", 58, 65, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_Fly_Left", "kirby_Left.png", 58, 65, 0.1f, true);

	// �⺻ �������� ���
	KirbyRenderer->CreateAnimation("Base_fall_Right", "kirby_Right.png", { 66,67,35,36,37 }, 0.1f, false);
	KirbyRenderer->CreateAnimation("Base_fall_Left", "kirby_Left.png", { 66,67,35,36,37 }, 0.1f, false);
	
	// �⺻ ���̱� 
	KirbyRenderer->CreateAnimation("Base_HeadDown_Right", "kirby_Right.png", 2, 3, 0.5f, true);
	KirbyRenderer->CreateAnimation("Base_HeadDown_Left", "kirby_Left.png", 2, 3, 0.5f, true);

	// �浹 �ִϸ��̼�
	KirbyRenderer->CreateAnimation("Base_hit_Right", "kirby_Right.png", { 51,50,49,48,47,46,45,44,43,42,41,40 }, 0.04f, true);
	KirbyRenderer->CreateAnimation("Base_hit_Left", "kirby_Left.png", { 51,50,49,48,47,46,45,44,43,42,41,40 }, 0.04f, true);

	KirbyRenderer->CreateAnimation("Icehit_Right", "hitKirby_Right.png", 5,9, 0.1f, false);
	KirbyRenderer->CreateAnimation("Icehit_Left", "hitKirby_Left.png", 5,9, 0.1f, false);

	KirbyRenderer->CreateAnimation("hothit_Right", "hitKirby_Right.png", 0, 3, 0.1f, false);
	KirbyRenderer->CreateAnimation("hothit_Left", "hitKirby_Left.png", 0, 3, 0.1f, false);

	// ---�⺻������ ������ ��ǵ�----
	// Heavy ��� Idle
	KirbyRenderer->CreateAnimation("HeavyIdle_Right", "kirby2_Right.png", 19, 20, 0.5f, true);
	KirbyRenderer->CreateAnimation("HeavyIdle_Left", "kirby2_Left.png", 19, 20, 0.5f, true);

	// Heavy��� Move
	KirbyRenderer->CreateAnimation("HeavyMove_Right", "kirby2_Right.png", 23, 33, 0.06f, true);
	KirbyRenderer->CreateAnimation("HeavyMove_Left", "kirby2_Left.png", 23, 33, 0.06f, true);

	// Heavy��� Move
	KirbyRenderer->CreateAnimation("HeavyJump_Right", "kirby2_Right.png", 34, 41, 0.09f, true);
	KirbyRenderer->CreateAnimation("HeavyJump_Left", "kirby2_Left.png", 34, 41, 0.09f, true);
	

	// �⺻ ��� 
	KirbyRenderer->CreateAnimation("Base_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
	KirbyRenderer->CreateAnimation("Base_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);
	


	//-- ���̾� Ŀ�� 
	KirbyRenderer->CreateAnimation("Fire_Idle_Right", "Fire_Right.png", 0,6, 0.2f, true); // ������ �� �ֱ�
	KirbyRenderer->CreateAnimation("Fire_Idle_Left", "Fire_Left.png", 0,6, 0.2f, true); // ���� ���ֱ�

	// ���̾� �ȴ� ���
	KirbyRenderer->CreateAnimation("Fire_Walk_Right", "Fire_Right.png", 32,50, 0.045f, true); // �ȱ�
	KirbyRenderer->CreateAnimation("Fire_Walk_Left", "Fire_Left.png", 32,50, 0.045f, true); // �ȱ�

	// ���̾� �ٴ� ���
	KirbyRenderer->CreateAnimation("Fire_run_Right", "Fire_Right.png", 53, 59, 0.08f, true);
	KirbyRenderer->CreateAnimation("Fire_run_Left", "Fire_Left.png", 53, 59, 0.08f, true);

	// ���̾� ���� ���
	KirbyRenderer->CreateAnimation("Fire_Jump_Right", "Fire_Right.png", 21, 31, 0.07f, true);
	KirbyRenderer->CreateAnimation("Fire_Jump_Left", "Fire_Left.png",21, 31, 0.07f, true);

	// ���̾� ���� ���
	KirbyRenderer->CreateAnimation("Fire_FlyReady_Right", "Fire_Right.png", 65, 69, 0.08f, false);
	KirbyRenderer->CreateAnimation("Fire_FlyReady_Left", "Fire_Left.png", 65, 69, 0.08f, false);
	KirbyRenderer->CreateAnimation("Fire_Fly_Right", "Fire_Right.png", 70, 94, 0.08f, true);
	KirbyRenderer->CreateAnimation("Fire_Fly_Left", "Fire_Left.png", 70, 94, 0.08f, true);

	// ���̾� �������� ���
	KirbyRenderer->CreateAnimation("Fire_fall_Right", "Fire_Right.png", 97, 101, 0.1f, false);
	KirbyRenderer->CreateAnimation("Fire_fall_Left", "Fire_Left.png", 97, 101, 0.1f, false);
	// ���̾� ���̱� 
	KirbyRenderer->CreateAnimation("Fire_HeadDown_Right", "Fire_Right.png", 8, 9, 0.5f, true);
	KirbyRenderer->CreateAnimation("FIre_HeadDown_Left", "Fire_Left.png", 8, 9, 0.5f, true);

	// ���̾� ���̱� 
	KirbyRenderer->CreateAnimation("Fire_FireReady_Right", "Fire_Right.png", 122, 128, 0.08f, true);
	KirbyRenderer->CreateAnimation("FIre_FireReady_Left", "Fire_Left.png", 122, 128, 0.08f, true);
	KirbyRenderer->CreateAnimation("Fire_FireAttack_Right", "Fire_Right.png", 129, 131, 0.08f, true);
	KirbyRenderer->CreateAnimation("FIre_FireAttack_Left", "Fire_Left.png", 129, 131, 0.08f, true);

	KirbyRenderer->CreateAnimation("Fire_hit_Right", "Fire_Right.png", {115,114,113,112,111,110,109,108,107,106,105,104,103,102,101}, 0.05f, true);
	KirbyRenderer->CreateAnimation("Fire_hit_Left", "Fire_Left.png", { 115,114,113,112,111,110,109,108,107,106,105,104,103,102,101 }, 0.05f, true);



	// ���̾� ��� -> �⺻���� ���̽� �߰� �̹��� 
	KirbyRenderer->CreateAnimation("Fire_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
	KirbyRenderer->CreateAnimation("Fire_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);

	//-- ���̽� Ŀ��
	KirbyRenderer->CreateAnimation("Ice_Idle_Right", "Ice_Right.png", 0, 1, 0.5f, true); // ������ �� �ֱ�
	KirbyRenderer->CreateAnimation("Ice_Idle_Left", "Ice_Left.png", 0, 1, 0.5f, true); // ���� ���ֱ�

	// ���̽� �ȴ� ���
	KirbyRenderer->CreateAnimation("Ice_Walk_Right", "Ice_Right.png", 32, 39, 0.075f, true); // �ȱ�
	KirbyRenderer->CreateAnimation("Ice_Walk_Left", "Ice_Left.png", 32, 39, 0.075f, true); // �ȱ�

	// ���̽� �ٴ� ���
	KirbyRenderer->CreateAnimation("Ice_run_Right", "Ice_Right.png", 42, 49, 0.05f, true);
	KirbyRenderer->CreateAnimation("Ice_run_Left", "Ice_Left.png", 42, 49, 0.05f, true);

	// ���̽� ���� ���
	KirbyRenderer->CreateAnimation("Ice_Jump_Right", "Ice_Right.png", 80, 90, 0.07f, true);
	KirbyRenderer->CreateAnimation("Ice_Jump_Left", "Ice_Left.png", 80, 90, 0.07f, true);

	// ���̽� ���� ���
	KirbyRenderer->CreateAnimation("Ice_FlyReady_Right", "Ice_Right.png", 54, 58, 0.08f, false);
	KirbyRenderer->CreateAnimation("Ice_FlyReady_Left", "Ice_Left.png", 54, 58, 0.08f, false);
	KirbyRenderer->CreateAnimation("Ice_Fly_Right", "Ice_Right.png", 59, 74, 0.08f, true);
	KirbyRenderer->CreateAnimation("Ice_Fly_Left", "Ice_Left.png", 59, 74, 0.08f, true);

	// ���̽� �������� ���
	KirbyRenderer->CreateAnimation("Ice_fall_Right", "Ice_Right.png", 75, 79, 0.1f, false);
	KirbyRenderer->CreateAnimation("Ice_fall_Left", "Ice_Left.png", 75, 79, 0.1f, false);
	// ���̽� ���̱� 
	KirbyRenderer->CreateAnimation("Ice_HeadDown_Right", "Ice_Right.png", 10, 11, 0.5f, true);
	KirbyRenderer->CreateAnimation("Ice_HeadDown_Left", "Ice_Left.png", 10, 11, 0.5f, true);

	KirbyRenderer->CreateAnimation("Ice_hit_Right", "Ice_Right.png", { 90,89,88,87,86,85,84,83,82,81,80,79 }, 0.05f, true);
	KirbyRenderer->CreateAnimation("Ice_hit_Left", "Ice_Left.png", { 90,89,88,87,86,85,84,83,82,81,80,79 }, 0.05f, true);

	// ���̽� ����
	KirbyRenderer->CreateAnimation("Ice_IceAttack_Right", "Ice_Right.png", 94, 103, 0.05f, true);
	KirbyRenderer->CreateAnimation("Ice_IceAttack_Left", "Ice_Left.png", 94, 103, 0.05f, true);

	// ���̽� ��� -> �⺻���� ���̽� �߰� �̹��� 
	KirbyRenderer->CreateAnimation("Ice_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
	KirbyRenderer->CreateAnimation("Ice_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);


	// ��� Ŀ���忡�� ��� ������ �ִϸ��̼�
	KirbyRenderer->CreateAnimation("AllAttack_Right", "kirby2_Right.png", 42, 52, 0.03f, false);
	KirbyRenderer->CreateAnimation("AllAttack_Left", "kirby2_Left.png", 42, 52, 0.03f, false);
}

// Ŀ�� ��� ü���� ����
void AKirby_Player::KirbyModeCheck()
{
	if (std::string(GetModeName()) != "Base_") // �⺻ Ŀ�� ������ ���ڿ��� �ƴ� ���
	{
		if (std::string(GetModeName()) == "Ice_") // ���̽� ���ڿ��̸�
		{
			SetMode(EAMode::Ice); // ���̽� ���·�
		}
		else if (std::string(GetModeName()) == "Fire_") // �ҵ� ���ڿ��̸�
		{
			SetMode(EAMode::Fire); // �ҵ� ���·�
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

// �߷� ����
void AKirby_Player::CalGravityVector(float _DeltaTime)
{
	GravityVector += GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime); // �߷��� ��� ��������.

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0)) // ColMapImage���� �������� ��ġ�ϴ� ���
	{
		GravityVector = FVector::Zero; // �߷��� ���� 0����
	}
}

// ���� �̵� ����
void AKirby_Player::MoveLastMoveVector(float _DeltaTime, const FVector& _MovePos)
{
	// ���η� ���� �ʱ�ȭ ��Ų��.
	PlayMove = FVector::Zero; // Kirby �̵� ����
	
	PlayMove = PlayMove + JumpVector;

	if (false == FlyState) // ���� ���� ���
	{
		PlayMove = PlayMove + GravityVector; // �߷� ���� O
	}
	else { // ���� ���
		GravityVector = FVector::Zero; // �߷��� ���� X
	}

	FVector MovePos = _MovePos;
	
	FVector CheckPos = GetActorLocation(); // Kirby
	FVector CamCheckPos = GetActorLocation(); // camera

	// ���� �� �ȼ� �浹 �ν� ����
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= checkposX;
		CamCheckPos.X -= 3.0f;// 3���� �켱 ����
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

	if (ColorR == Color8Bit(255, 0, 0, 0)) // ��(Red)�� �浹�� ��� -> �����̴� �� 0
	{
		MovePos = FVector::Zero;
	}

	AddActorLocation(MovePos + (PlayMove * _DeltaTime)); // ���� Kirby ������ ��� X��(���� ������ ���� ��)�� Y�� (�߷�, ����)

	if (ColorG != Color8Bit(0, 255, 0, 0) && ColorB != Color8Bit(0, 0, 255, 0) && ColorM != Color8Bit(255, 0, 255, 0)) // �ʷ�, �Ķ�, ����Ÿ �ȼ� �浹�� ���� ���
	{
		// ī�޶� ���� �̵�
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

void AKirby_Player::DirCheck() // Ŀ�� ���� ������ ���� üũ
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

	if (Dir != DirState && false==SkillOn) // ��ų ����߿��� ���� ��ȯ �Ұ���
	{
		DirState = Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		KirbyRenderer->ChangeAnimation(Name, true,KirbyRenderer->GetCurAnimationFrame(), KirbyRenderer->GetCurAnimationTime());
	}
}

// ���� �����ؾ��� �ִϸ��̼� ����
std::string AKirby_Player::GetAnimationName(std::string_view _Name)
{
	std::string DirName = "";

	// ���� üũ
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

	if (std::string(_Name) == "AllAttack" || std::string(_Name) == "HeavyIdle" || std::string(_Name) == "HeavyMove" || std::string(_Name) == "HeavyJump" || std::string(_Name) == "Icehit" || std::string(_Name) == "hothit") // AllAttack�� ��� Ŀ���忡�� ��� �����ϱ⿡
	{
		return std::string(_Name) + DirName; // // �տ� GetModeName���� AllAttack ���ڿ��� ���⸸ ����
	}
	return std::string(GetModeName()) + std::string(_Name) + DirName; // ���� �����ؾ��� �ִϸ��̼� �̸� (Ŀ�� ���) + �ִϸ��̼� �̸� + (����)
}

// Ŀ���� ������ ���¿� �´� �ִϸ��̼� ����
void AKirby_Player::StateAniChange(EActorState _State) 
{
	
	// Ŀ�� ������ ���ڿ��� �°� Ŀ�� ��带 ���� ���ش�.
	//KirbyModeCheck();

	// �������¿� ���� ���°� �ٸ� ��� �� ���Ϳ��� �浹�� ������ �� ����
	// ex) �������� move ������ Idle
	if (State != _State && false==hitState)
	{
		switch (_State) // ���º� �ִϸ��̼� ��ŸƮ
		{
		case EActorState::Idle:
			if (true == EatState && KirbyMode == EAMode::Base) // Eat���� (��������) �� Ŀ�� �⺻ ����϶��� üũ�� �����Ѵ�.
			{
				HeavyIdleStart(); // Heavy�� �⺻ ������ Ŀ�񿡼��� ������ �ִϸ��̼�
			}
			else
			{
				IdleStart();
			}
			break;
		case EActorState::Walk:
			if (true == EatState && KirbyMode == EAMode::Base) // ����
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
			if (true == EatState && KirbyMode == EAMode::Base) // ����
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
			if (true == EatState && KirbyMode == EAMode::Base) // ����
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

	if (true == hitState) // ���Ϳ� �浹�� ��Ȳ����
	{
		State = EActorState::hit; // ���� ���´� hit�� ����
		return;
	}

	State = _State; // �Ϲ����� ��Ȳ�� _State�� ����
}

void AKirby_Player::StateUpdate(float _DeltaTime)
{
	if (false == hitState) // ���Ϳ� �浹���� ���� ���¿����� ���¿� ���� ���� ����
	{
		switch (State) // ���� ���º� �����ؾ��ϴ� ����
		{
		case EActorState::Idle: // ���ֱ�
			Idle(_DeltaTime);
			break;
		case EActorState::Walk: // �ȱ�
			Walk(_DeltaTime);
			break;
		case EActorState::Run: // �ȱ�
			Run(_DeltaTime);
			break;
		case EActorState::Jump: // ����
			Jump(_DeltaTime);
			break;
		case EActorState::FlyReady: // ���� �غ�
			FlyReady(_DeltaTime);
			break;
		case EActorState::Fly: // ����
			Fly(_DeltaTime);
			break;
		case EActorState::Flyfall: // ���ٰ� �߶�
			Flyfall(_DeltaTime);
			break;
		case EActorState::HeadDown: // ���̱�
			HeadDown(_DeltaTime);
			break;
		case EActorState::All_Attack: // ��� �� ���� -> �� ��� ����
			All_Attack(_DeltaTime);
			break;
		case EActorState::Absorption: // ���
			ModeInputTick(_DeltaTime);
			break;
		case EActorState::IceAttack: // ���̽� ����
			ModeInputTick(_DeltaTime);
			break;
		case EActorState::FireReady: // ���̽� ����
			FireReady( _DeltaTime);
			break;
		case EActorState::FireAttack: // ���̽� ����
			ModeInputTick(_DeltaTime);
			break;
		default:
			break;
		}
	}
	else { // ���Ϳ� �浹�� ����
		hit(_DeltaTime);
	}
	
}

void AKirby_Player::Idle(float _DeltaTime)
{
	// ���� �����ʵ� �ȵǰ� �ְ�.
	// ���⼭�� ����
	// ������ �������� ��� ���� �Ű澲�� �˴ϴ�.
	CurY = GetActorLocation(); // ī�޶� Y�� ����� ���� ���� Ŀ�� ��ġ�� ����
	
	if (true == transform)
	{
		
		transform = false;
		GetWorld()->SetAllTimeScale(1.0f);
		effectRenderer->ActiveOff();
		
	}

	// �׽�Ʈ ���



	
	Color8Bit ColorB = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::BlueA);
	
	if (true == UEngineInput::IsDown(VK_UP) && StageCheck == 1)
	{
		// && ColorB != Color8Bit(0, 0, 255, 0)
		if (false == CreateStage2)
		{
			CreateStage2 = true;
			GEngine->CreateLevel<UStage2_Level>("Stage2_Level"); // stage1_Level ����
		}
		StageCheck = 2;
		GEngine->ChangeLevel("Stage2_Level");
	}else if (true == UEngineInput::IsDown(VK_UP) && StageCheck == 2)// �ʷ�, �Ķ�, ����Ÿ �ȼ� �浹�� ���� ���
	{
		// && ColorB != Color8Bit(0, 0, 255, 0)
		//if (false == CreateStage2)
		//{
			//GEngine->CreateLevel<UStage2_Level>("Stage2_Level"); // stage1_Level ����
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

	// �ȱ�
	if (
		true == UEngineInput::IsPress(VK_LEFT) ||
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		StateAniChange(EActorState::Walk);
		return;
	}

	// ����
	if (
		true == UEngineInput::IsDown('S') 
		)
	{
		JumpVector = JumpPowerIdle;
		StateAniChange(EActorState::Jump);
		return;
	}

	// ���̱�
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

	// Ŀ�� ��忡 ���� ��ų ����
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

	// �� ��� ���� (��� Ŀ���忡�� ��� ����)
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
	DirCheck(); // ���� üũ

	FVector MovePos;

	// ���� ���� X�� �̵�
	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * checkSpeed * _DeltaTime;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * checkSpeed * _DeltaTime;
	}

	// ���� ���� Fly
	if (UEngineInput::IsDown('S'))
	{
		switch (KirbyMode)
		{
		case EAMode::Base:
			// Base������ EatState�� true�̸� ���� ���Ѵ�.
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

	MoveUpdate(_DeltaTime,MovePos); // ���� ������

	CamYMove(); // ī�޶� Y�� ���
	
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	
	if (ColorR == Color8Bit(255, 0, 0, 0)) // �ȼ� �浹 -> ���� �� �����Ҷ�
	{
		JumpVector = FVector::Zero; // ������ ���� 0
		StateAniChange(EActorState::Idle); // Idle ��ȭ
		return;
	}
}

// ���� ���� �غ� ���
void AKirby_Player::FlyReady(float _DeltaTime)
{
	DirCheck(); 

	FlyState = true; // ���� ���� Bool�� True
	JumpVector = FVector::Zero; // ������ 0
	
	if (true == KirbyRenderer->IsCurAnimationEnd()) //  �ش� �ִϸ��̼� ���� ��
	{
		StateAniChange(EActorState::Fly); // ����� ��ȯ
		return;
	}
}

void AKirby_Player::Fly(float _DeltaTime)
{
	DirCheck();

	// ���� ���� XŰ ���� ��� -> ������
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
	// õ�� �ȼ� �浹 -> �߶�
	Color8Bit ColorM = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY()-40, Color8Bit::MagentaA);
	if (ColorM == Color8Bit(255, 0, 255, 0) )
	{
		FlyState = false;
		StateAniChange(EActorState::Flyfall);
	    return;
	}

	// �ٴ� �ȼ� �浹  -> �߶�
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{

		FlyState = false;
		StateAniChange(EActorState::Flyfall);
		return;
	}
}

// ���ٰ� �߶��� ��
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
	// �߶��ؼ� �ٴڰ� �浹�� ���
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

// ���Ϳ� �浹�ϴ� ���
void AKirby_Player::hit(float _DeltaTime)
{
	DirCheck();

	FVector Move = FVector::Zero;
	JumpVector = FVector::Zero; // ���� ���߿� �浹�� ��� -> ������ 0

	// ���Ϳ� �ݴ� �������� �̵��ؾ��ϱ� ����
	if (DirState == EActorDir::Left) // ������ ���� 
	{
		Move = FVector::Right * 60.0f * _DeltaTime; // ������
	}
	else { // �������� ����
		Move = FVector::Left * 60.0f * _DeltaTime; // ����
	}

	
	Color8Bit ColorG = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::GreenA);
	//Color8Bit ColorB = UActorCommon::ColMapImage->GetColor(CamCheckPos.iX(), CamCheckPos.iY(), Color8Bit::BlueA);
	// Ŀ�� �浹 �� �̵� ����
	AddActorLocation(Move);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // ���߿��� �浹�� �� �ֱ⿡ �߷� �ۿ�
	FlyState = false; // ���ٰ� �߶��� ���
	
	CamstopMove += Move;
	CamYMove(); // Y��

	// �ִϸ��̼� ���� �� �ٽ� ���� ���·� ���ư�
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

// �ִϸ��̼� ��ŸƮ ����
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

void AKirby_Player::ModeInputTick(float _DeltaTime) // Ŀ�� �Ӽ� �� �� �͵�
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

	if (true == KirbyRenderer->IsCurAnimationEnd()) //  �ش� �ִϸ��̼� ���� ��
	{
		StateAniChange(EActorState::FireAttack); // ����� ��ȯ
		return;
	}
}

void AKirby_Player::Collisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == FireCollision->CollisionCheck(ECollisionOrder::Monster, Result))
	{
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("�����߰���....");
		}
		Monster->Destroy();
	}
	else if (true == FireCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
	{
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("�����߰���....");
		}
		Monster->Destroy();
	}
	else if (true == FireCollision->CollisionCheck(ECollisionOrder::FireMonster, Result))
	{
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Fire* Monster = dynamic_cast<AMonster_Fire*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("�����߰���....");
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


