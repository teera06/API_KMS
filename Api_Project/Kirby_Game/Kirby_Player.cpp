#include "Kirby_Player.h"

#include <EnginePlatform\EngineInput.h> // Level1 -> �Է� ���(����)
#include <EngineCore/EngineCore.h> // GetWorld ��� -> Level ���� �̿�

#include "AllStar.h"
#include "Base.h"
#include "Ice.h"
#include "Sir.h" // �׽�Ʈ

// Ư�� �̺�Ʈ �� Ŀ�� �������� �ϴ°͵�
#include "BossHpBar.h"
#include "SubBoss.h"

// �׽�Ʈ -> ���߿� �����
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"
#include "Monster_Mike.h"


AKirby_Player* AKirby_Player::MainPlayer = nullptr;

int AKirby_Player::Hp = 100;
int AKirby_Player::StageCheck = 1;


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

	if (StageCheck >= 3)
	{
		
		SoundRenderer = CreateImageRenderer(ERenderOrder::Sound); // �̹��� ���� ����
		SoundRenderer->SetImage("Tock_Right.png"); // �̹��� Set
		SoundRenderer->SetTransform({ {0,0}, {64 * 5, 64 * 5} }); // ������ ��ġ ũ�� 

		SoundRenderer->ActiveOff();
		
	}

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

	{
		MikeCollision = CreateCollision(ECollisionOrder::MikeAttack);
		//MikeCollision->SetScale({ 1000, 500 });
		MikeCollision->SetColType(ECollisionType::Rect);
		MikeCollision->ActiveOff();
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
	KirbyRenderer->CreateAnimation("Base_Stop_Right", "kirby_Left.png", 28, 28, 0.1f, true);
	KirbyRenderer->CreateAnimation("Base_Stop_Left", "kirby_Right.png", 28, 28, 0.1f, true);

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
	KirbyRenderer->CreateAnimation("Fire_Walk_Right", "Fire_Right.png", 32,50, 0.03f, true); // �ȱ�
	KirbyRenderer->CreateAnimation("Fire_Walk_Left", "Fire_Left.png", 32,50, 0.03f, true); // �ȱ�

	// ���̾� �ٴ� ���
	KirbyRenderer->CreateAnimation("Fire_run_Right", "Fire_Right.png", 52, 59, 0.08f, true);
	KirbyRenderer->CreateAnimation("Fire_run_Left", "Fire_Left.png", 52, 59, 0.08f, true);
	KirbyRenderer->CreateAnimation("Fire_Stop_Right", "Fire_Left.png", 60, 61, 0.1f, true);
	KirbyRenderer->CreateAnimation("Fire_Stop_Left", "Fire_Right.png", 60, 61, 0.1f, true);

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
	KirbyRenderer->CreateAnimation("Fire_FireReady_Right", "Fire_Right.png", 122, 128, 0.05f, true);
	KirbyRenderer->CreateAnimation("FIre_FireReady_Left", "Fire_Left.png", 122, 128, 0.05f, true);
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
	KirbyRenderer->CreateAnimation("Ice_Stop_Right", "Ice_Left.png", 50, 50, 0.1f, true);
	KirbyRenderer->CreateAnimation("Ice_Stop_Left", "Ice_Right.png", 50, 50, 0.1f, true);

	// ���̽� ���� ���
	KirbyRenderer->CreateAnimation("Ice_Jump_Right", "Ice_Right.png", 80, 90, 0.06f, true);
	KirbyRenderer->CreateAnimation("Ice_Jump_Left", "Ice_Left.png", 80, 90, 0.06f, true);

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

	// Sir Ŀ��
	if (StageCheck>=2)
	{
		// ���̾� ��� -> �⺻���� ���̽� �߰� �̹��� 
		KirbyRenderer->CreateAnimation("Sir_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
		KirbyRenderer->CreateAnimation("Sir_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);

		KirbyRenderer->CreateAnimation("Sir_Idle_Right", "Sir_Right.png", 0, 0, 0.5f, true); // ������ �� �ֱ�
		KirbyRenderer->CreateAnimation("Sir_Idle_Left", "Sir_Left.png", 0, 0, 0.5f, true); // ���� ���ֱ�

		KirbyRenderer->CreateAnimation("Sir_Walk_Right", "Sir_Right.png", 2, 11, 0.075f, true); // ������ �� �ֱ�
		KirbyRenderer->CreateAnimation("Sir_Walk_Left", "Sir_Left.png", 2, 11, 0.075f, true); // ���� ���ֱ�

		KirbyRenderer->CreateAnimation("Sir_Run_Right", "Sir_Right.png", 12, 19, 0.05f, true); // ������ �� �ֱ�
		KirbyRenderer->CreateAnimation("Sir_Run_Left", "Sir_Left.png", 12, 19, 0.05f, true); // ���� ���ֱ�
		KirbyRenderer->CreateAnimation("Sir_Stop_Right", "Sir_Left.png", 48, 48, 0.1f, true); // ������ �� �ֱ�
		KirbyRenderer->CreateAnimation("Sir_Stop_Left", "Sir_Right.png", 48, 48, 0.1f, true); // ���� ���ֱ�

		KirbyRenderer->CreateAnimation("Sir_Jump_Right", "Sir_Right.png", 20, 26, 0.06f, true); // ������ �� �ֱ�
		KirbyRenderer->CreateAnimation("Sir_Jump_Left", "Sir_Left.png", 20, 26, 0.06f, true); // ���� ���ֱ�

		KirbyRenderer->CreateAnimation("Sir_FlyReady_Right", "Sir_Right.png", {39,38,37,82}, 0.08f, false);
		KirbyRenderer->CreateAnimation("Sir_FlyReady_Left", "Sir_Left.png", { 39,38,37,82 }, 0.08f, false);
		KirbyRenderer->CreateAnimation("Sir_Fly_Right", "Sir_Right.png", 82, 87, 0.08f, true);
		KirbyRenderer->CreateAnimation("Sir_Fly_Left", "Sir_Left.png", 82, 87, 0.08f, true);

		KirbyRenderer->CreateAnimation("Sir_fall_Right", "Sir_Right.png", {41,42,43,26,27,28}, 0.1f, false);
		KirbyRenderer->CreateAnimation("Sir_fall_Left", "Sir_Left.png", { 41,42,43,26,27,28 }, 0.1f, false);

		KirbyRenderer->CreateAnimation("Sir_SirJump_Right", "Sir_Right.png", 20,26, 0.1f, false);
		KirbyRenderer->CreateAnimation("Sir_SirJump_Left", "Sir_Left.png", 20,26, 0.1f, false);

		KirbyRenderer->CreateAnimation("Sir_HeadDown_Right", "Sir_Right.png", 1, 1, 0.5f, true);
		KirbyRenderer->CreateAnimation("Sir_HeadDown_Left", "Sir_Left.png", 1, 1, 0.5f, true);

		KirbyRenderer->CreateAnimation("Sir_hit_Left", "Sir_Left.png", { 36,35,34,33,32,31,30,29,28,27,26}, 0.05f, true);
		KirbyRenderer->CreateAnimation("Sir_hit_Right", "Sir_Right.png", { 36,35,34,33,32,31,30,29,28,27,26 }, 0.05f, true);

		KirbyRenderer->CreateAnimation("Sir_SirAttack_Left", "Sir_Left.png", 88,92, 0.05f, true);
		KirbyRenderer->CreateAnimation("Sir_SirAttack_Right", "Sir_Right.png", 88,92, 0.05f, true);
	}
	
	if (StageCheck >= 3) 
	{
		KirbyRenderer->CreateAnimation("Mike_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
		KirbyRenderer->CreateAnimation("Mike_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);
		// �⺻ ���ִ� ���(��)
		KirbyRenderer->CreateAnimation("Mike_Idle_Right", "kirby_Right.png", 0, 1, 0.5f, true); // ������ �� �ֱ�
		KirbyRenderer->CreateAnimation("Mike_Idle_Left", "kirby_Left.png", 0, 1, 0.5f, true); // ���� ���ֱ�

		// �⺻ �ȴ� ���(��)
		KirbyRenderer->CreateAnimation("Mike_Walk_Right", "kirby_Right.png", 10, 19, 0.07f, true); // �ȱ�
		KirbyRenderer->CreateAnimation("Mike_Walk_Left", "kirby_Left.png", 10, 19, 0.07f, true); // �ȱ�

		// �⺻ �ٴ� ���(��)
		KirbyRenderer->CreateAnimation("Mike_run_Right", "kirby_Right.png", 20, 27, 0.04f, true);
		KirbyRenderer->CreateAnimation("Mike_run_Left", "kirby_Left.png", 20, 27, 0.04f, true);
		KirbyRenderer->CreateAnimation("Mike_Stop_Right", "kirby_Left.png", 28, 28, 0.1f, true);
		KirbyRenderer->CreateAnimation("Mike_Stop_Left", "kirby_Right.png", 28, 28, 0.1f, true);

		// �⺻ ���� ���(��)
		KirbyRenderer->CreateAnimation("Mike_Jump_Right", "kirby_Right.png", 38, 51, 0.06f, true);
		KirbyRenderer->CreateAnimation("Mike_Jump_Left", "kirby_Left.png", 38, 51, 0.06f, true);

		// �⺻ ���� ���
		KirbyRenderer->CreateAnimation("Mike_FlyReady_Right", "kirby_Right.png", 53, 57, 0.08f, false);
		KirbyRenderer->CreateAnimation("Mike_FlyReady_Left", "kirby_Left.png", 53, 57, 0.08f, false);
		KirbyRenderer->CreateAnimation("Mike_Fly_Right", "kirby_Right.png", 58, 65, 0.1f, true);
		KirbyRenderer->CreateAnimation("Mike_Fly_Left", "kirby_Left.png", 58, 65, 0.1f, true);

		// �⺻ �������� ���
		KirbyRenderer->CreateAnimation("Mike_fall_Right", "kirby_Right.png", { 66,67,35,36,37 }, 0.1f, false);
		KirbyRenderer->CreateAnimation("Mike_fall_Left", "kirby_Left.png", { 66,67,35,36,37 }, 0.1f, false);

		// �⺻ ���̱� 
		KirbyRenderer->CreateAnimation("Mike_HeadDown_Right", "kirby_Right.png", 2, 3, 0.5f, true);
		KirbyRenderer->CreateAnimation("Mike_HeadDown_Left", "kirby_Left.png", 2, 3, 0.5f, true);

		// �浹 �ִϸ��̼�
		KirbyRenderer->CreateAnimation("Mike_hit_Right", "kirby_Right.png", { 51,50,49,48,47,46,45,44,43,42,41,40 }, 0.04f, true);
		KirbyRenderer->CreateAnimation("Mike_hit_Left", "kirby_Left.png", { 51,50,49,48,47,46,45,44,43,42,41,40 }, 0.04f, true);

		KirbyRenderer->CreateAnimation("Mike_MikeAttack1_Left", "Mike_Left.png", 0, 12, 0.1f, true);
		KirbyRenderer->CreateAnimation("Mike_MikeAttack1_Right", "Mike_Right.png", 0, 12, 0.1f, true);

		KirbyRenderer->CreateAnimation("Mike_MikeAttack2_Left", "Mike_Left.png", 14, 22, 0.1f, true);
		KirbyRenderer->CreateAnimation("Mike_MikeAttack2_Right", "Mike_Right.png", 14, 22, 0.1f, true);

		KirbyRenderer->CreateAnimation("Mike_MikeAttack3_Left", "Mike_Left.png", 23, 38, 0.1f, true);
		KirbyRenderer->CreateAnimation("Mike_MikeAttack3_Right", "Mike_Right.png", 23, 38, 0.1f, true);

		SoundRenderer->CreateAnimation("AttEffect", "Tock_Right.png", { 16,17,18,19,20,14 }, 0.1f, true);
	}

	if (StageCheck >= 4)
	{
		KirbyRenderer->CreateAnimation("Hammer_Absorption_Right", "kirby2_Right.png", 0, 9, 0.06f, false);
		KirbyRenderer->CreateAnimation("Hammer_Absorption_Left", "kirby2_Left.png", 0, 9, 0.06f, false);
		// �⺻ ���ִ� ���(��)
		KirbyRenderer->CreateAnimation("Hammer_Idle_Right", "Hammer_Right.png", 0, 2, 0.5f, true); // ������ �� �ֱ�
		KirbyRenderer->CreateAnimation("Hammer_Idle_Left", "Hammer_Left.png", 0, 2, 0.5f, true); // ���� ���ֱ�

		// �⺻ �ȴ� ���(��)
		KirbyRenderer->CreateAnimation("Hammer_Walk_Right", "Hammer_Right.png", 6, 15, 0.07f, true); // �ȱ�
		KirbyRenderer->CreateAnimation("Hammer_Walk_Left", "Hammer_Left.png", 6, 15, 0.07f, true); // �ȱ�

		// �⺻ �ٴ� ���(��)
		KirbyRenderer->CreateAnimation("Hammer_run_Right", "Hammer_Right.png", 16, 23, 0.04f, true);
		KirbyRenderer->CreateAnimation("Hammer_run_Left", "Hammer_Left.png", 16, 23, 0.04f, true);
		KirbyRenderer->CreateAnimation("Hammer_Stop_Right", "Hammer_Left.png", 25, 25, 0.1f, true);
		KirbyRenderer->CreateAnimation("Hammer_Stop_Left", "Hammer_Right.png", 25, 25, 0.1f, true);

		// �⺻ ���� ���(��)
		KirbyRenderer->CreateAnimation("Hammer_Jump_Right", "Hammer_Right.png", 26, 34, 0.06f, true);
		KirbyRenderer->CreateAnimation("Hammer_Jump_Left", "Hammer_Left.png", 26, 34, 0.06f, true);

		// �⺻ ���� ���
		KirbyRenderer->CreateAnimation("Hammer_FlyReady_Right", "Hammer_Right.png", {40,41,42,48}, 0.08f, false);
		KirbyRenderer->CreateAnimation("Hammer_FlyReady_Left", "Hammer_Left.png", { 40,41,42,48 }, 0.08f, false);
		KirbyRenderer->CreateAnimation("Hammer_Fly_Right", "Hammer_Right.png", 49, 53, 0.1f, true);
		KirbyRenderer->CreateAnimation("Hammer_Fly_Left", "Hammer_Left.png", 49, 53, 0.1f, true);

		// �⺻ �������� ���
		KirbyRenderer->CreateAnimation("Hammer_fall_Right", "Hammer_Right.png", { 45,46,47,33,34 }, 0.1f, false);
		KirbyRenderer->CreateAnimation("Hammer_fall_Left", "Hammer_Left.png", { 45,46,47,33,34 }, 0.1f, false);

		// �⺻ ���̱� 
		KirbyRenderer->CreateAnimation("Hammer_HeadDown_Right", "Hammer_Right.png", 2, 3, 0.5f, true);
		KirbyRenderer->CreateAnimation("Hammer_HeadDown_Left", "Hammer_Left.png", 2, 3, 0.5f, true);
	}

	// ��� Ŀ���忡�� ��� ������ �ִϸ��̼�
	KirbyRenderer->CreateAnimation("AllAttack_Right", "kirby2_Right.png", 4, 6, 0.03f, false);
	KirbyRenderer->CreateAnimation("AllAttack_Left", "kirby2_Left.png", 4, 6, 0.03f, false);




}

// Ŀ�� ��� ü���� ����
void AKirby_Player::KirbyModeCheck()
{
	if (std::string(GetModeName()) != "Base_") // �⺻ Ŀ�� ������ ���ڿ��� �ƴ� ���
	{
		if (std::string(GetModeName()) == "Ice_") // ���̽� ���ڿ��̸�
		{
			scale = 3;
			SetMode(EAMode::Ice); // ���̽� ���·�
		}
		else if (std::string(GetModeName()) == "Fire_") // �ҵ� ���ڿ��̸�
		{
			scale = 3;
			SetMode(EAMode::Fire); // �ҵ� ���·�
		}
		else if (std::string(GetModeName()) == "Sir_") // �ҵ� ���ڿ��̸�
		{
			scale = 3;
			SetMode(EAMode::Sir); // �ҵ� ���·�
		}
		else if (std::string(GetModeName()) == "Mike_") // �ҵ� ���ڿ��̸�
		{
			scale = 3;
			SetMode(EAMode::Mike); // �ҵ� ���·�
		}
		else if (std::string(GetModeName()) == "Hammer_") // �ҵ� ���ڿ��̸�
		{
			scale = 5;
			SetMode(EAMode::Hammer); // �ҵ� ���·�
		}
	}
	else {
		scale = 3;
	}
	KirbyRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
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
	Color8Bit ColorY = UActorCommon::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::YellowA);


	Color8Bit ColorG = UActorCommon::ColMapImage->GetColor(CamCheckPos.iX(), CamCheckPos.iY(), Color8Bit::GreenA);
	Color8Bit ColorB = UActorCommon::ColMapImage->GetColor(CamCheckPos.iX(), CamCheckPos.iY(), Color8Bit::BlueA);
	Color8Bit ColorM = UActorCommon::ColMapImage->GetColor(CamCheckPos.iX(), CamCheckPos.iY(), Color8Bit::MagentaA);
	Color8Bit ColorBend = UActorCommon::ColMapImage->GetColor(CamCheckPos.iX(), CamCheckPos.iY(), Color8Bit::BlackA);

	if (ColorR == Color8Bit(255, 0, 0, 0)) // ��(Red)�� �浹�� ��� -> �����̴� �� 0
	{
		MovePos = FVector::Zero;
	}

	// 3�������� ����� ��� �̺�Ʈ
	if (ColorY == Color8Bit(255, 255, 0, 0) && true == SubBossWall && StageCheck == 3) // 3�������� Ư�� �̺�Ʈ ���� �� �߰�
	{
		MovePos = FVector::Zero;
	}

	if (ColorY == Color8Bit(255, 255, 0, 0) && StageCheck==3 && false==SubBossEvent) // ó���� ������ �׵ڷδ� ���� ���� 
	{
		// ����� �ȼ� �浹, 3��������, ���� bool�� -> �ѹ��� ����ǰ� �׵ڷδ� ���� �ȵ�
		SubBossEvent = true;
		SubBossWall = true; // �� ����
		SuBBossActive = true;

		// ��ġ ����
		GetWorld()->SetCameraPos({1800,30}); // ī�޶� ��ġ
		AddActorLocation(FVector::Right * 30.0f); // �÷��̾� ��ġ
		GetWorld()->SpawnActor<ASubBoss>()->SetActorLocation({ GetActorLocation().iX() + 800, 500});
		GetWorld()->SpawnActor<ABossHpBar>();
		return;
	}
	//

	AddActorLocation(MovePos + (PlayMove * _DeltaTime)); // ���� Kirby ������ ��� X��(���� ������ ���� ��)�� Y�� (�߷�, ����)


	if (ColorG != Color8Bit(0, 255, 0, 0) && ColorB != Color8Bit(0, 0, 255, 0) && ColorM != Color8Bit(255, 0, 255, 0) && false==SubBossWall) // �ʷ�, �Ķ�, ����Ÿ �ȼ� �浹�� ���� ���
	{
		// ī�޶� ���� �̵�
		FVector Move = (MovePos * FVector::Right) + CamstopMove; // 
	
		GetWorld()->AddCameraPos(Move);
		
		CamstopMove = FVector::Zero;

	}
	else {

		CamstopMove += (MovePos * FVector::Right);
	}

	if (ColorBend == Color8Bit(0, 0, 0, 0)) 
	{
		GetWorld()->SetCameraPos({ 0,585 }); // ī�޶� ��ġ ����
		SetActorLocation({ 500,1200 });
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
		case EActorState::Stop:
			if (true == EatState && KirbyMode == EAMode::Base)
			{
				return;
			}// ����
			StopStart();
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
		case EActorState::SirJump:
			SirJumpStart();
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
		case EActorState::SirAttack:
			SirAttackStart();
			break;
		case EActorState::MikeAttack:
			MikeAttackStart();
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
		case EActorState::Stop: // �ȱ�
			if (true == EatState && KirbyMode == EAMode::Base)
			{
				return;
			}// ����
			Stop(_DeltaTime);
			break;
		case EActorState::Jump: // ����
			Jump(_DeltaTime);
			break;
		case EActorState::SirJump: // ����
			SirJump(_DeltaTime);
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
		case EActorState::SirAttack: // ���̽� ����
			ModeInputTick(_DeltaTime);
			break;
		case EActorState::MikeAttack: // ���̽� ����
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
		StageCheck = 2;
		GEngine->ChangeLevel("Stage2_Level");
	}
	else if (true == UEngineInput::IsDown(VK_UP) && StageCheck == 2)
	{
		StageCheck = 3;
		GEngine->ChangeLevel("Stage3_Level");
	}
	else if (true == UEngineInput::IsDown(VK_UP) && StageCheck == 3)
	{
		StageCheck = 4;
		GEngine->ChangeLevel("LastBoss_Level");
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

	if (true == UEngineInput::IsDown('5') && StageCheck==2)
	{
		if (DirState == EActorDir::Left)
		{
			GetWorld()->SpawnActor<AMonster_Sir>()->SetActorLocation({ GetActorLocation().iX() - 200,700 });
		}
		else {
			GetWorld()->SpawnActor<AMonster_Sir>()->SetActorLocation({ GetActorLocation().iX() + 300,700 });
		}
		Hp = 100;
		return;
	}
	if (true == UEngineInput::IsDown('6') && StageCheck == 3)
	{
		if (DirState == EActorDir::Left)
		{
			GetWorld()->SpawnActor<AMonster_Mike>()->SetActorLocation({ GetActorLocation().iX() - 200,700 });
		}
		else {
			GetWorld()->SpawnActor<AMonster_Mike>()->SetActorLocation({ GetActorLocation().iX() + 300,700 });
		}
		Hp = 100;
		return;
	}

	// �ȱ�
	if (
		true == UEngineInput::IsDoubleClick(VK_LEFT,0.2f) ||
		true == UEngineInput::IsDoubleClick(VK_RIGHT,0.2f)
		)
	{
		RunState = true;
		StateAniChange(EActorState::Run);
		return;
	}

	if (false == RunState)
	{
		if (
			true == UEngineInput::IsPress(VK_LEFT) ||
			true == UEngineInput::IsPress(VK_RIGHT)
			)
		{
			StateAniChange(EActorState::Walk);
			return;
		}
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
		StateAniChange(EActorState::FireReady);
		return;
	}else if (
		true == UEngineInput::IsDown('X') && KirbyMode == EAMode::Sir && false==SirUse // �׽�Ʈ
		)
	{
		SkillOn = true;
		SirUse = true;
		StateAniChange(EActorState::SirAttack);
		ASir* NewSir = GetWorld()->SpawnActor<ASir>();
		NewSir->SetStartPos(this->GetActorLocation() * FVector::Right);
		NewSir->SetActorLocation(this->GetActorLocation());
		NewSir->SetOwner(ESirOwner::kirby);
		if (DirState == EActorDir::Left)
		{
			NewSir->SetDir(FVector::Left);
		}
		else {
			NewSir->SetDir(FVector::Right);
		}
		return;
	}
	else if (
		true == UEngineInput::IsDown('X') && KirbyMode == EAMode::Mike  // �׽�Ʈ
		)
	{
		SkillOn = true;
		MikeCollision->SetActive(true, 0.2f);
		StateAniChange(EActorState::MikeAttack);
		return;
	}

	// �� ��� ���� (��� Ŀ���忡�� ��� ����)
	if (
		true == UEngineInput::IsDown('A') && (true==EatState || KirbyMode != EAMode::Base) && false==SirUse
		)
	{
		scale = 3;
		KirbyRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
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

	if (StageCheck < 3)
	{
		CamYMove(); // ī�޶� Y�� ���
	}

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	
	if (ColorR == Color8Bit(255, 0, 0, 0)) // �ȼ� �浹 -> ���� �� �����Ҷ�
	{
		JumpVector = FVector::Zero; // ������ ���� 0

		if (true == RunState)
		{
			StateAniChange(EActorState::Run); // Idle ��ȭ
		}
		else {
			StateAniChange(EActorState::Idle); // Idle ��ȭ
		}
		
		return;
	}

	if (
		true == UEngineInput::IsDown('X') && KirbyMode == EAMode::Sir && false == SirUse // �׽�Ʈ
		)
	{
		SkillOn = true;
		SirUse = true;
		StateAniChange(EActorState::SirAttack);
		ASir* NewSir = GetWorld()->SpawnActor<ASir>();
		NewSir->SetStartPos(this->GetActorLocation() * FVector::Right);
		NewSir->SetActorLocation(this->GetActorLocation());
		NewSir->SetOwner(ESirOwner::kirby);
		if (DirState == EActorDir::Left)
		{
			NewSir->SetDir(FVector::Left);
		}
		else {
			NewSir->SetDir(FVector::Right);
		}
		return;
	}
}

void AKirby_Player::SirJump(float _DeltaTime)
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

	MoveUpdate(_DeltaTime, MovePos);
	if (StageCheck < 3)
	{
		CamYMove(); // ī�޶� Y�� ���
	}
	// �߶��ؼ� �ٴڰ� �浹�� ���
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		JumpVector = FVector::Zero;
		RunState = false;
		StateAniChange(EActorState::Idle);
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
		RunState = false;
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
	if (StageCheck < 3)
	{
		CamYMove(); // ī�޶� Y�� ���
	}
	// õ�� �ȼ� �浹 -> �߶�
	Color8Bit ColorM = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY()-40, Color8Bit::MagentaA);
	if (ColorM == Color8Bit(255, 0, 255, 0) )
	{
		FlyState = false;
		RunState = false;
		StateAniChange(EActorState::Flyfall);
	    return;
	}

	// �ٴ� �ȼ� �浹  -> �߶�
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{

		FlyState = false;
		RunState = false;
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

	MoveUpdate(_DeltaTime, MovePos);
	if (StageCheck < 3)
	{
		CamYMove(); // ī�޶� Y�� ���
	}
	// �߶��ؼ� �ٴڰ� �浹�� ���
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		JumpVector = FVector::Zero;
		RunState = false;
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

	
	Move = HitDir * 60.0f * _DeltaTime; // ������
	
	Color8Bit ColorG = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::GreenA);
	//Color8Bit ColorB = UActorCommon::ColMapImage->GetColor(CamCheckPos.iX(), CamCheckPos.iY(), Color8Bit::BlueA);
	// Ŀ�� �浹 �� �̵� ����
	AddActorLocation(Move);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // ���߿��� �浹�� �� �ֱ⿡ �߷� �ۿ�
	FlyState = false; // ���ٰ� �߶��� ���
	SkillOn = false;
	FireRenderer->ActiveOff();
	FireCollision->ActiveOff();
	MikeCollision->ActiveOff();
	SoundRenderer->ActiveOff();
	CamstopMove += Move;
	if (StageCheck < 3)
	{
		CamYMove(); // ī�޶� Y�� ���
	}

	// �ִϸ��̼� ���� �� �ٽ� ���� ���·� ���ư�
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		hitState = false;
		RunState = false;
		KirbyRenderer->SetAlpha(1.0f);
		KirbyCollision->SetActive(true, 0.3f);
		
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


	if (true == UEngineInput::IsDown('S'))
	{
		JumpVector = JumpPowerMove;
		StateAniChange(EActorState::Jump);
		return;
	}


	MoveUpdate(_DeltaTime, MovePos);

	if (StageCheck < 3)
	{
		CamYMove(); // ī�޶� Y�� ���
	}
}

void AKirby_Player::Run(float _DeltaTime)
{
	

	RunRL = DirState;

	DirCheck();


	if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		RunState = false;
		StateAniChange(EActorState::Idle);
		return;
	}

	
	FVector MovePos = FVector::Zero;

	
	if (UEngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * checkSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * checkSpeed;
	}

	if (RunRL != DirState)
	{
		MovePos = FVector::Zero;
		StateAniChange(EActorState::Stop);
		return;
	}

	if (true == UEngineInput::IsDown('S'))
	{
		JumpVector = JumpPowerMove;
		StateAniChange(EActorState::Jump);
		return;
	}

	MoveUpdate(_DeltaTime, MovePos);

	if (StageCheck < 3)
	{
		CamYMove(); // ī�޶� Y�� ���
	}
}

void AKirby_Player::Stop(float _DeltaTime)
{
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		StateAniChange(EActorState::Run);
		return;
	}
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

void AKirby_Player::StopStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("Stop"));
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

void AKirby_Player::SirAttackStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("SirAttack"));
}

void AKirby_Player::SirJumpStart()
{
	DirCheck();
	KirbyRenderer->ChangeAnimation(GetAnimationName("SirJump"));
}

void AKirby_Player::SoundCollisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == MikeCollision->CollisionCheck(ECollisionOrder::SubBoss, Result))
	{
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		ASubBoss* Monster = dynamic_cast<ASubBoss*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("�����߰���....");
		}
		Monster->SetIshit(true);

		if (MikeOrder ==1)
		{
			Monster->AddHP(-20);
		}
		else if (MikeOrder == 2)
		{
			Monster->AddHP(-40);
		}
		else
		{
			Monster->AddHP(-40);
		}

		Monster->GetMonsterCollision()->ActiveOff();
	}
	else if (true == MikeCollision->CollisionCheck(ECollisionOrder::MikeMonster, Result))
	{
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Mike* Monster = dynamic_cast<AMonster_Mike*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("�����߰���....");
		}
		FVector DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
	}
}

void AKirby_Player::MikeAttackStart()
{
	DirCheck();
	
	if (MikeOrder == 1)
	{
		KirbyRenderer->ChangeAnimation(GetAnimationName("MikeAttack1"));
	}
	else if (MikeOrder == 2)
	{
		KirbyRenderer->ChangeAnimation(GetAnimationName("MikeAttack2"));
	}
	else if (MikeOrder == 3)
	{
		KirbyRenderer->ChangeAnimation(GetAnimationName("MikeAttack3"));
	}
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
		MikeKirby(_DeltaTime);
		break;
	case EAMode::Sir:
		SirKirby(_DeltaTime);
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

	if (true == UEngineInput::IsUp('X'))
	{
		SkillOn = false;
		StateAniChange(EActorState::Idle);
		return;
	}

	if (true == KirbyRenderer->IsCurAnimationEnd()) //  �ش� �ִϸ��̼� ���� ��
	{
		FireRenderer->ActiveOn();
		FireCollision->ActiveOn();
		if (DirState == EActorDir::Left)
		{
			FireRenderer->ChangeAnimation("Fire_Left");
			FireRenderer->SetTransform({ { -140, 5}, { 64 * 6,64 * 4 } });
			FireCollision->SetTransform({ {-140,-5},{100,70} });
		}
		else {
			FireRenderer->ChangeAnimation("Fire_RIght");
			FireRenderer->SetTransform({ { 140,5}, { 64 * 6,64 * 4} });
			FireCollision->SetTransform({ {140,-5},{100,70} });
		}
		StateAniChange(EActorState::FireAttack); // ����� ��ȯ
		return;
	}
}

void AKirby_Player::FireCollisiongather(float _DeltaTime)
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
	else if (true == FireCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
	{
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Sir* Monster = dynamic_cast<AMonster_Sir*>(Ptr);

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

	FireCollisiongather(_DeltaTime);
	if (true == UEngineInput::IsUp('X'))
	{
		SkillOn = false;
		FireRenderer->ActiveOff();
		FireCollision->ActiveOff();
		StateAniChange(EActorState::Idle);
		return;
	}

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

void AKirby_Player::SirKirby(float _DeltaTime)
{
	DirCheck();

	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		SkillOn = false;
		StateAniChange(EActorState::SirJump);
		return;
	}

	MoveUpdate(_DeltaTime);
}

void AKirby_Player::MikeKirby(float _DeltaTime)
{
	DirCheck();

	if (DirState == EActorDir::Left)
	{
		
		MikeCollision->SetTransform({ {-140,-5},{1000,200} });
	}
	else {
		MikeCollision->SetTransform({ {140,-5},{1000,200} });
	}

	MikeCollision->ActiveOn();
	SoundRenderer->ChangeAnimation("AttEffect");
	SoundRenderer->ActiveOn();
	if (true == KirbyRenderer->IsCurAnimationEnd())
	{
		SkillOn = false;
		++MikeOrder;
		if (MikeOrder >3) // �ݸ��� �޺��� 3���� Ŭ ��� ���� �ʱ�ȭ
		{
			EatState = false;
			SetModeName("Base_");
			SetMode(EAMode::Base);
			MikeOrder = 1;
		}

		SoundCollisiongather(_DeltaTime); // ���� �ݸ��� -> ���� ������ ���� ���Ϳ��Ը� ���Ѵ�.

		if (true == SuBBossActive)
		{
			if (ASubBoss::GetMainSubBoss()->GetHp() > 0) // �����ǰ� 0���� ũ�� �������϶� 
			{
				ASubBoss::GetMainSubBoss()->GetMonsterCollision()->ActiveOn(); // �ݸ����� ���� �ִ� ��� �ٽ� �ݸ��� ��
			}
			else { // ������ ���� ������ -> ī�޶� ����
				SubBossWall = false;
				SuBBossActive = false;
				GetWorld()->SetCameraPos({ GetWorld()->GetCameraPos().iX() - 500,0 });
			}
		}

		MikeCollision->ActiveOff();
		SoundRenderer->ActiveOff();
		StateAniChange(EActorState::Idle);
		return;
	}


	MoveUpdate(_DeltaTime);
}


