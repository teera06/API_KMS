#pragma once

// ���
#include <EngineCore/Actor.h> 
#include "ActorCommon.h"

// Enum ������
#include "ModeEnum.h"

class AKirby_Player : public AActor, public UActorCommon // ActorCommon(�߷�)
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


	static AKirby_Player* GetMainPlayer(); // ���ͳ� ����â�� �÷��̾ ���� ������ �˾ƾ� �� �� ���
	
	UImageRenderer* GetKirbyRender()
	{
		return KirbyRenderer;
	}

	UCollision* GetKirbyCollision()
	{
		return KirbyCollision;
	}

	void SetHitDir(const FVector& _HitDir)
	{
		HitDir = _HitDir;
	}

	void HitStart(); // ���Ϳ� �浹�� ����
	void IcehitStart();
	void hothitStart();

	void Sethitstate(bool _hitState) // Set hitState
	{
		hitState = _hitState;
	}

	void SetSirUse(const bool& _SirUse)
	{
		SirUse = _SirUse;
	}

	bool GetSirUse() const
	{
		return SirUse;
	}

	static void SetHp(const int& _Hp)
	{
		Hp = _Hp;
	}

	static void AddHP(const int& _Value)
	{
		Hp += _Value;
	}

	static int GetHp()
	{
		return Hp;
	}

	static int GetStageCheck()
	{
		return StageCheck;
	}

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// ���¿� ���� ����, �ִϸ��̼� ������Ʈ
	void StateAniChange(EActorState _State); // Ŀ���� ������ ���¿� �´� �ִϸ��̼� ����
	void StateUpdate(float _DeltaTime);

	// ���¿� ���� ����
	void Idle(float _DeltaTime); // ���ֱ�
	void Walk(float _DeltaTime); // �ȱ�
	void Run(float _DeltaTime); // �޸���
	void Stop(float _DeltaTime);
	void Jump(float _DeltaTime); // ����
	void SirJump(float _DeltaTime);
	void FlyReady(float _DeltaTime); // ���� �� �غ����
	void Fly(float _DeltaTime); // ����
	void Flyfall(float _DeltaTime); // ���ٰ� ������ ��
	void HeadDown(float _DeltaTime); // ���̱�
	void hit(float _DeltaTime); // ���Ϳ��� �浹
	void Absorption(float _DeltaTime); // ���(���� ���Ƶ��̱�)
	void All_Attack(float _DeltaTime); // �� ��� ����

	// ���¿� ���� �ִϸ��̼� ��ŸƮ
	void IdleStart(); // ���ֱ�
	void HeavyIdleStart(); // �԰� �ִ� ������ ���ֱ�

	void WalkStart(); // �ȱ�
	void HeavyMoveStart(); // �԰� �ִ� ������ �ȱ�

	void JumpStart(); // ����
	void HeavyJumpStart(); // �԰� �ִ� ������ ����

	void FlyReadyStart(); // ���� �� �غ����
	void FlyStart(); // ����
	void FlyFallStart(); // ���ٰ� ������ ��
	void RunStart(); // �޸���
	void StopStart();
	void AbsorptionStart(); // ��� 
	void HeadDownStart(); // ���̱�

	// ���� ���

	void ModeInputTick(float _DeltaTime); // ��庰 �Է�Ű
	void FireReady(float _DeltaTime);
	void FireCollisiongather(float _DeltaTime);



	void AllAttackStart(); // �� ��� ����
	void IceAttackStart(); // ���̽� ����

	void FireReadyStart();
	void FireAttackStart(); 

	void SirAttackStart(); // ���̽� ����
	void SirJumpStart();

	void HammerStart();

	void SoundCollisiongather(float _DeltaTime);
	void MikeAttackStart();
	int MikeOrder = 1;
	// �� ���¸��� ������ ���� ���� ����Ǿ�� �Ѵ�.
	void DirCheck(); // ������, ���� ���� üũ

	// �ִϸ��̼� ó��
	std::string GetAnimationName(std::string_view _Name);
	std::string CurAnimationName = "None"; 
	
	// Ŀ�� ���� ó��
	EActorState State = EActorState::None;
	
	// ����ó��
	EActorDir DirState = EActorDir::Right;
	
private:
	
	UImageRenderer* KirbyRenderer=nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* effectRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* FireRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* SoundRenderer = nullptr; // Ŀ�� ������ (�̹���)
	
	UCollision* KirbyCollision = nullptr; // Ŀ�� �ݸ��� (�浹)
	UCollision* FireCollision = nullptr; // Ŀ�� �ݸ��� (�浹)
	UCollision* MikeCollision = nullptr; // Ŀ�� �ݸ��� (�浹)

	UImageRenderer* manual = nullptr;
	// �ൿ�� �ӵ� ����
	float checkSpeed = 0.0f; // ���� ���ǵ�

	float WalkSpeed = 200.0f; // �ȴ� �ӵ�
	float RunSpeed = 280.0f; // �ٴ� �ӵ�

	float FlySpeed = 180.0f; // ���� �ӵ�

	float HeavyWalkSpeed = 180.0f; // EatState�϶� ���ǵ� -> �ȱ�
	float HeavyRunSpeed = 230.0f; // �ٱ�
	
	float checkposX = 30.0f;
	float checkposY = 30.0f;

	float camSpeed = 500.0f; // ī�޶� �ӵ�

	float CamYSpeed = 0.5f; // Y�� CamYMove() ī�޶� �̵� ��ġ
	
	// Ư�� ���º� bool ��
	bool FlyState = false; // ���� ����
	bool hitState = false; // �浹 ����
	bool SkillOn = false; // ��ų ��� ���� ����
	bool SirUse = false; // Sir Kirby ����

	bool transform = false;
	bool RunState = false;
	EActorDir RunRL = EActorDir::None;

	// 3�������� ���� ����
	bool SubBossEvent=false;
	bool SubBossWall = false;
	bool SuBBossActive = false;

	// Ŀ���� �Ǵ����� ������ �÷��� ���� ������
	static int StageCheck;

	static int Hp;

	void AniCreate(); // �ִϸ��̼� ����
	void KirbyModeCheck(); // Ŀ�� ��� ü����
	void GroundUp();
	
	FVector CamstopMove = FVector::Zero; // ī�޶� ������ �� ĳ���Ͱ� ������ ��
	FVector GravityVector = FVector::Zero; // �߷°� �ޱ�

	// ������ ����
	FVector JumpPowerIdle = FVector::Up * 400; // ���ִ� ��쿡�� ������
	FVector JumpPowerMove = FVector::Up * 500; // �̵��Ҷ��� ������
	FVector JumpVector = FVector::Zero; // ���� ������

	FVector PlayMove = FVector::Zero; // Kirby Move

	FVector CurY = FVector::Zero; // Camera Y Move

	FVector HitDir = FVector::Zero;

	static AKirby_Player* MainPlayer;
	
	// ������ ���� �Լ�
	void CalGravityVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime, const FVector& _MovePos= FVector::Zero);
	void MoveUpdate(float _DeltaTime, const FVector& _MovePos=FVector::Zero);
	
	// Ŀ�� ��庰 ���� �Լ�
	void FireKirby(float _DeltaTime); // �� Ŀ��
	void IceKirby(float _DeltaTime); // ���̽� Ŀ��
	void SirKirby(float _DeltaTime);
	void MikeKirby(float _DeltaTime);
	void HammerKirby(float _DeltaTime);
	
	// ī�޶� Y�� ���� �Լ�
	void CamYMove();
};

