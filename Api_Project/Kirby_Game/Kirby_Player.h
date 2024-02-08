#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"
#include "ActorCommon.h"
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

	void BaseKirby(float _DeltaTime); // �⺻ Ŀ�� 
	void FireKirby(); // �� Ŀ��

	std::string_view GetAniNamechange() // Get �̸�ü����
	{
		return AniNamechange;
	}

	void SetNamechange(std::string_view _AniNamechange) // Set �̸� ü����
	{
		AniNamechange = _AniNamechange;
	}

	inline void SetMode(AMode _KirbyMode) // Ŀ�� ��� ü���� �Ҷ� ���
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
	void StateChange(ActorState _State);
	void StateUpdate(float _DeltaTime);

	// ���� �Լ���
	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Jump(float _DeltaTime);
	void HeadDown(float _DeltaTime);
	// Ŀ�� ���� �� ���� 
	void Run(float _DeltaTime);
	void Absorption(float _DeltaTime); // ���

	// ���� ���� �Լ���
	void IdleStart();
	void HeavyIdleStart();

	void WalkStart();
	void HeavyMoveStart();

	void JumpStart();
	void RunStart();
	void AbsorptionStart();
	void HeadDownStart();

	// �� ���¸��� ������ ���� ���� ����Ǿ�� �Ѵ�.
	void DirCheck();

	std::string GetAnimationName(std::string_view _Name);
	std::string CurAnimationName = "None";
	ActorState State = ActorState::None;
	EActorDir DirState = EActorDir::Right;
	//---------------------------------------------------
private:
	//float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr; // Ŀ�� ������ (�̹���)
	
	// �ൿ�� �ӵ� ����
	float checkSpeed = 0.0f;
	float WalkSpeed = 100.0f; // �ȴ� �ӵ�
	float RunSpeed = 250.0f; // �ٴ� �ӵ�
	float camSpeed = 500.0f; // ī�޶� �ӵ�
	float HeavySpeed = 80.0f; // EatState�϶� ���ǵ�
	
	bool EatState = false;

	void ModeInputTick(float _DeltaTime); // ��庰 �Է�Ű
	void AniCreate();

	FVector GravityCheck = FVector::Zero; // �߷°� �ޱ�
	AMode KirbyMode = AMode::Base; // Kirby ���
	std::string AniNamechange = "Base_"; // Kirby ��庰 �ִϸ��̼� �̸� ü����
};

