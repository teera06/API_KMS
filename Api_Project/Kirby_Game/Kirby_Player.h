#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"
#include "ActorCommon.h"
#include <EngineCore/Level.h>
// ���� ���Ƿ� üũ�ϱ� -> �����丵
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

	void FireKirby(); // �� Ŀ��

	static AKirby_Player* GetMainPlayer();

	std::string_view GetModeName() // Get �̸�ü����
	{
		return ModeName;
	}

	void SetModeName(std::string_view _ModeName) // Set �̸� ü����
	{
		ModeName = _ModeName;
	}

	inline void SetMode(EAMode _KirbyMode) // Ŀ�� ��� ü���� �Ҷ� ���
	{
		KirbyMode = _KirbyMode;
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
	void Fly(float _DeltaTime);
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
	void FlyReadyStart();
	void FlyStart();
	void RunStart();
	void AbsorptionStart();
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
	float WalkSpeed = 100.0f; // �ȴ� �ӵ�
	float RunSpeed = 250.0f; // �ٴ� �ӵ�
	float camSpeed = 500.0f; // ī�޶� �ӵ�
	float HeavyWalkSpeed = 80.0f; // EatState�϶� ���ǵ�
	float HeavyRunSpeed = 100.0f;
	float checkposvalue = 30;

	bool EatState = false;

	void ModeInputTick(float _DeltaTime); // ��庰 �Է�Ű
	void AniCreate();

	FVector GravityCheck = FVector::Zero; // �߷°� �ޱ�
	FVector CamstopMove = FVector::Zero; // ī�޶� ������ �� ĳ���Ͱ� ������ ��


	EAMode KirbyMode = EAMode::Base; // Kirby ���
	std::string ModeName = "Base_"; // Kirby ��庰 �ִϸ��̼� �̸� ü����

	static AKirby_Player* MainPlayer;


	void CalLastMoveVector(float _DeltaTime);
	void CalMoveVector(float _DeltaTime);
	void CalJumpVector(float _DeltaTime);
	void CalGravityVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);
};

