#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"

// ���� ���Ƿ� üũ�ϱ� -> �����丵
class AKirby_Player : public AActor
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

	void BaseKirby();
	void FireKirby();

	std::string_view GetNamechange()
	{
		return Namechange;
	}

	void SetNamechange(std::string_view _Namechange)
	{
		Namechange = _Namechange;
	}

	inline void SetMode(AMode _KirbyMode) // Ŀ�� ��� ü���� �Ҷ� ���
	{
		KirbyMode = _KirbyMode;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// ���� �ֿ� ������Ʈ
	void StateChange(ActorState _State);
	void StateUpdate(float _DeltaTime);

	// ���� �Լ���
	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Run(float _DeltaTime);

	// ���� ���� �Լ���
	void IdleStart();
	void WalkStart();
	void JumpStart();
	void RunStart();
	

	// �� ���¸��� ������ ���� ���� ����Ǿ�� �Ѵ�.
	void DirCheck();

	std::string GetAnimationName(std::string_view _Name);
	std::string CurAnimationName = "None";
	ActorState State = ActorState::None;
	EActorDir DirState = EActorDir::Right;
private:
	//float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr; // Ŀ�� ����
	
	int RLpoint = 0; // ����(����, ������ ���� ��ȯ) üũ -> �߻� ���� 
	int JumpKey = 0; // ����Ű�� �������� �Ҽ� �ִ°� -> ���ߺξ�

	// �¿� �޸��� ani�� ����Ǳ� ���� ����
	bool rRunanicheck = false;
	bool lRunanicheck = false;
	bool AttMotion = false; // ���� ����� Ŀ��� �̵� �Ұ�
	bool flyMotion = false; // ���� ��� üũ
	bool SeetMotion = false;


	float WalkSpeed = 100.0f; // �ȴ� �ӵ�
	float RunSpeed = 250.0f; // �ٴ� �ӵ�

	void GravityCheck(float _DeltaTime);

	void ModeInputTick(); // ��庰 �Է�Ű

	AMode KirbyMode = AMode::Base; // Kirby ��� ������
	std::string Namechange = "Base_"; // �ִϸ��̼� �̸� �������ֱ�
	FVector LRCheck = { 100.0f, 0.0f, 0.0f, 0.0f }; // �⺻ Ŀ�� ���
	float Gravity = 500.0f;
	int Hp=100;
};

