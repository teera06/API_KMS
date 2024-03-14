#pragma once

// ���
#include <EnginePlatform\EngineSound.h>
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

	void ReStartState();

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

	bool GetMainBossEvent() const
	{
		return MainBossEvent;
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

	static void SetStageCheck(const int& _StageCheck)
	{
		StageCheck = _StageCheck;
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

	void HammerAttStart1();
	void HammerAttStart2();
	void HammerAttStart3();
	int HammerAttOrder = 0;

	void HammerCollisiongather(float _DeltaTime);

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
	static AKirby_Player* MainPlayer;

	UEngineSoundPlayer SModeChange;
	UEngineSoundPlayer SBase;
	UEngineSoundPlayer SFire;
	UEngineSoundPlayer SIce;
	UEngineSoundPlayer SSir;
	UEngineSoundPlayer SIceHit;
	UEngineSoundPlayer SMike1;
	UEngineSoundPlayer SMike2;
	UEngineSoundPlayer SMike3;
	UEngineSoundPlayer SHammer1;
	UEngineSoundPlayer SChargeHammer2;
	UEngineSoundPlayer SHammer2;
	UEngineSoundPlayer SHammer3;

	UImageRenderer* KirbyRenderer=nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* effectRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* FireRenderer1 = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* FireRenderer2 = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* FireRenderer3 = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* SoundRenderer = nullptr; // Ŀ�� ������ (�̹���)
	
	UCollision* KirbyCollision = nullptr; // Ŀ�� �ݸ��� (�浹)
	UCollision* BoxCollision = nullptr; // Ŀ�� �ݸ��� (�浹)
	UCollision* FireCollision = nullptr; // Ŀ�� �ݸ��� (�浹)
	UCollision* MikeCollision = nullptr; // Ŀ�� �ݸ��� (�浹)
	UCollision* HammerCollision = nullptr; // Ŀ�� �ݸ��� (�浹)

	// �̵� ����
	FVector CamstopMove = FVector::Zero; // ī�޶� ������ �� ĳ���Ͱ� ������ ��
	FVector GravityVector = FVector::Zero; // �߷°� �ޱ�

	// ������ ����
	FVector JumpPowerIdle = FVector::Up * 400; // ���ִ� ��쿡�� ������
	FVector JumpPowerMove = FVector::Up * 500; // �̵��Ҷ��� ������
	FVector JumpVector = FVector::Zero; // ���� ������

	FVector PlayMove = FVector::Zero; // Kirby Move

	FVector CurY = FVector::Zero; // Camera Y Move

	FVector HitDir = FVector::Zero;

	FVector MoveY = FVector::Zero;

	// �ൿ�� �ӵ� ����
	float SJumptime = 0.3f;
	float SFiretime = 0.3f;
	float SIcetime = 0.3f;
	float SSirtime = 0.3f;
	float SFlytime = 0.2f;
	float SFlyFalltime = 0.2f;

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
	
	// Ŀ���� �Ǵ����� ������ �÷��� ���� ������
	static int StageCheck;

	static int Hp;
	int HammerAtt = 0;
	int HammerAttCombo = 0;
	int hitwallx = 0;
	int AllAttcheck = 0;

	// 2�������� ���� ����
	bool fall = false;

	// 3�������� ���� ����
	bool SubBossEvent = false;
	bool BossEventWall = false;
	bool SuBBossActive = false;

	bool MainBossEvent = false;
	// Ư�� ���º� bool ��
	bool FlyState = false; // ���� ����
	bool hitState = false; // �浹 ����
	bool SkillOn = false; // ��ų ��� ���� ����
	bool SirUse = false; // Sir Kirby ����
	bool MikeSoundReset = false;

	bool transform = false;
	bool RunState = false;
	EActorDir RunRL = EActorDir::None;

	void AniCreate(); // �ִϸ��̼� ����
	void SoundCreate();
	void SoundReset();
	void KirbyModeCheck(); // Ŀ�� ��� ü����
	void GroundUp();

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

