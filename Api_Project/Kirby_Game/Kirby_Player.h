#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"
#include "ActorCommon.h"
#include <EngineCore/Level.h>

class AKirby_Player : public AActor, public ActorCommon // ActorCommon(�߷�)
{
public:
	// constrcuter destructer
	AKirby_Player(); // ����Ʈ ������
	~AKirby_Player(); // ����Ʈ �Ҹ���

	// delete Function
	AKirby_Player(const AKirby_Player& _Other) = delete; // ����Ʈ ���� ������
	AKirby_Player(AKirby_Player&& _Other) noexcept = delete;
	AKirby_Player& operator=(const AKirby_Player& _Other) = delete; // ����Ʈ ���� ������
	AKirby_Player& operator=(AKirby_Player&& _Other) noexcept = delete;

	static AKirby_Player* GetMainPlayer();
	
	UImageRenderer* GetKirbyRender()
	{
		return KirbyRenderer;
	}

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// ����, Ŀ�� �� ���� ����ϴ� �������� ����� ������ �켱 ���� ����
	//--------------------------------------------------
	// ���� �ֿ� ������Ʈ
	void StateAniChange(EActorState _State);
	void StateUpdate(float _DeltaTime);

	// ���� �Լ���
	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Jump(float _DeltaTime);
	void FlyReady(float _DeltaTime);
	void Fly(float _DeltaTime);
	void Flyfall(float _DeltaTime);
	void HeadDown(float _DeltaTime);
	
	// Ŀ�� ���� �� ���� 
	void Run(float _DeltaTime);
	void Absorption(float _DeltaTime); // ���
	void All_Attack(float _DeltaTime); // ����

	// ���� ���� �Լ���
	void IdleStart();
	void HeavyIdleStart();

	void WalkStart();
	void HeavyMoveStart();

	void JumpStart();
	void HeavyJumpStart();

	void FlyReadyStart();
	void FlyStart();
	void FlyFallStart();
	void RunStart();
	void AbsorptionStart();
	void IceAttackStart();
	void HeadDownStart();
	void AllAttackStart();

	// �� ���¸��� ������ ���� ���� ����Ǿ�� �Ѵ�.
	void DirCheck();

	std::string GetAnimationName(std::string_view _Name);
	std::string CurAnimationName = "None";
	EActorState State = EActorState::None;
	EActorDir DirState = EActorDir::Right;
	//---------------------------------------------------
private:
	//float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr; // Ŀ�� ������ (�̹���)
	UCollision* KirbyCollision = nullptr;
	// �ൿ�� �ӵ� ����
	float checkSpeed = 0.0f;
	float WalkSpeed = 200.0f; // �ȴ� �ӵ�
	float RunSpeed = 250.0f; // �ٴ� �ӵ�

	float FlySpeed = 180.0f;

	float camSpeed = 500.0f; // ī�޶� �ӵ�

	float HeavyWalkSpeed = 180.0f; // EatState�϶� ���ǵ�
	float HeavyRunSpeed = 230.0f;
	
	float checkposX = 30.0f;
	float checkposY = 30.0f;

	bool FlyState = false;
	

	void ModeInputTick(float _DeltaTime); // ��庰 �Է�Ű
	void AniCreate();

	
	FVector CamstopMove = FVector::Zero; // ī�޶� ������ �� ĳ���Ͱ� ������ ��
	FVector GravityVector = FVector::Zero; // �߷°� �ޱ�

	FVector JumpPowerIdle = FVector::Up * 400;
	FVector JumpPowerMove = FVector::Up * 500;

	FVector JumpVector = FVector::Zero;

	FVector PlayMove = FVector::Zero;

	FVector CurY = FVector::Zero;


	static AKirby_Player* MainPlayer;

	void CalGravityVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime, const FVector& _MovePos= FVector::Zero);
	void MoveUpdate(float _DeltaTime, const FVector& _MovePos=FVector::Zero);
	void FireKirby(); // �� Ŀ��
	void IceKirby(float _DeltaTime); // ���̽� Ŀ��
	void CamYMove();

	bool SkillOnOff = false;
};

