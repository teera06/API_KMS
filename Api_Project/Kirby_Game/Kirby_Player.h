#pragma once

// 상속
#include <EnginePlatform\EngineSound.h>
#include <EngineCore/Actor.h> 
#include "ActorCommon.h"

// Enum 모음집
#include "ModeEnum.h"

class AKirby_Player : public AActor, public UActorCommon // ActorCommon(중력)
{
public:
	// constrcuter destructer
	AKirby_Player(); // 디폴트 생성자
	~AKirby_Player(); // 디폴트 소멸자

	// delete Function
	AKirby_Player(const AKirby_Player& _Other) = delete; // 디폴트 복사 생성자
	AKirby_Player(AKirby_Player&& _Other) noexcept = delete;
	AKirby_Player& operator=(const AKirby_Player& _Other) = delete; // 디폴트 대입 연산자
	AKirby_Player& operator=(AKirby_Player&& _Other) noexcept = delete;


	static AKirby_Player* GetMainPlayer(); // 몬스터나 상태창이 플레이어에 대한 정보를 알아야 할 때 사용

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

	void HitStart(); // 몬스터와 충돌시 시작
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
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// 상태에 따른 조작, 애니메이션 업데이트
	void StateAniChange(EActorState _State); // 커비의 움직임 상태에 맞는 애니메이션 실행
	void StateUpdate(float _DeltaTime);

	// 상태에 따른 조작
	void Idle(float _DeltaTime); // 서있기
	void Walk(float _DeltaTime); // 걷기
	void Run(float _DeltaTime); // 달리기
	void Stop(float _DeltaTime);
	void Jump(float _DeltaTime); // 점프
	void SirJump(float _DeltaTime);
	void FlyReady(float _DeltaTime); // 날기 전 준비상태
	void Fly(float _DeltaTime); // 날기
	void Flyfall(float _DeltaTime); // 날다가 떨어질 때
	void HeadDown(float _DeltaTime); // 숙이기
	void hit(float _DeltaTime); // 몬스터와의 충돌
	void Absorption(float _DeltaTime); // 흡수(몬스터 빨아들이기)
	void All_Attack(float _DeltaTime); // 별 뱉기 공겨

	// 상태에 따른 애니메이션 스타트
	void IdleStart(); // 서있기
	void HeavyIdleStart(); // 먹고 있는 상태의 서있기

	void WalkStart(); // 걷기
	void HeavyMoveStart(); // 먹고 있는 상태의 걷기

	void JumpStart(); // 점프
	void HeavyJumpStart(); // 먹고 있는 상태의 점프

	void FlyReadyStart(); // 날기 전 준비상태
	void FlyStart(); // 날기
	void FlyFallStart(); // 날다가 떨어질 때
	void RunStart(); // 달리기
	void StopStart();
	void AbsorptionStart(); // 흡수 
	void HeadDownStart(); // 숙이기

	// 공격 모션

	void ModeInputTick(float _DeltaTime); // 모드별 입력키
	void FireReady(float _DeltaTime);
	void FireCollisiongather(float _DeltaTime);



	void AllAttackStart(); // 별 뱉기 공격
	void IceAttackStart(); // 아이스 공격

	void FireReadyStart();
	void FireAttackStart(); 

	void SirAttackStart(); // 아이스 공격
	void SirJumpStart();

	void HammerAttStart1();
	void HammerAttStart2();
	void HammerAttStart3();
	int HammerAttOrder = 0;

	void HammerCollisiongather(float _DeltaTime);

	void SoundCollisiongather(float _DeltaTime);
	void MikeAttackStart();
	int MikeOrder = 1;
	// 각 상태마다 언제나 가장 위에 실행되어야 한다.
	void DirCheck(); // 오른쪽, 왼쪽 방향 체크

	// 애니메이션 처리
	std::string GetAnimationName(std::string_view _Name);
	std::string CurAnimationName = "None"; 
	
	// 커비 상태 처리
	EActorState State = EActorState::None;
	
	// 방향처리
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

	UImageRenderer* KirbyRenderer=nullptr; // 커비 랜더링 (이미지)
	UImageRenderer* effectRenderer = nullptr; // 커비 랜더링 (이미지)
	UImageRenderer* FireRenderer1 = nullptr; // 커비 랜더링 (이미지)
	UImageRenderer* FireRenderer2 = nullptr; // 커비 랜더링 (이미지)
	UImageRenderer* FireRenderer3 = nullptr; // 커비 랜더링 (이미지)
	UImageRenderer* SoundRenderer = nullptr; // 커비 랜더링 (이미지)
	
	UCollision* KirbyCollision = nullptr; // 커비 콜리전 (충돌)
	UCollision* BoxCollision = nullptr; // 커비 콜리전 (충돌)
	UCollision* FireCollision = nullptr; // 커비 콜리전 (충돌)
	UCollision* MikeCollision = nullptr; // 커비 콜리전 (충돌)
	UCollision* HammerCollision = nullptr; // 커비 콜리전 (충돌)

	// 이동 제어
	FVector CamstopMove = FVector::Zero; // 카메라 멈췄을 때 캐릭터가 움직인 값
	FVector GravityVector = FVector::Zero; // 중력값 받기

	// 점프력 제어
	FVector JumpPowerIdle = FVector::Up * 400; // 서있는 경우에서 점프력
	FVector JumpPowerMove = FVector::Up * 500; // 이동할때의 점프력
	FVector JumpVector = FVector::Zero; // 최종 점프력

	FVector PlayMove = FVector::Zero; // Kirby Move

	FVector CurY = FVector::Zero; // Camera Y Move

	FVector HitDir = FVector::Zero;

	FVector MoveY = FVector::Zero;

	// 행동별 속도 정리
	float SJumptime = 0.3f;
	float SFiretime = 0.3f;
	float SIcetime = 0.3f;
	float SSirtime = 0.3f;
	float SFlytime = 0.2f;
	float SFlyFalltime = 0.2f;

	float checkSpeed = 0.0f; // 최종 스피드

	float WalkSpeed = 200.0f; // 걷는 속도
	float RunSpeed = 280.0f; // 뛰는 속도

	float FlySpeed = 180.0f; // 나는 속도

	float HeavyWalkSpeed = 180.0f; // EatState일때 스피드 -> 걷기
	float HeavyRunSpeed = 230.0f; // 뛰기
	
	float checkposX = 30.0f;
	float checkposY = 30.0f;

	float camSpeed = 500.0f; // 카메라 속도

	float CamYSpeed = 0.5f; // Y축 CamYMove() 카메라 이동 수치
	
	// 커비의 판단으로 나머지 플레이 레벨 만들자
	static int StageCheck;

	static int Hp;
	int HammerAtt = 0;
	int HammerAttCombo = 0;
	int hitwallx = 0;
	int AllAttcheck = 0;

	// 2스테이지 한정 변수
	bool fall = false;

	// 3스테이지 한정 변수
	bool SubBossEvent = false;
	bool BossEventWall = false;
	bool SuBBossActive = false;

	bool MainBossEvent = false;
	// 특정 상태별 bool 값
	bool FlyState = false; // 나는 상태
	bool hitState = false; // 충돌 상태
	bool SkillOn = false; // 스킬 사용 중인 상태
	bool SirUse = false; // Sir Kirby 한정
	bool MikeSoundReset = false;

	bool transform = false;
	bool RunState = false;
	EActorDir RunRL = EActorDir::None;

	void AniCreate(); // 애니메이션 생성
	void SoundCreate();
	void SoundReset();
	void KirbyModeCheck(); // 커비 모드 체인지
	void GroundUp();

	// 움직임 제어 함수
	void CalGravityVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime, const FVector& _MovePos= FVector::Zero);
	void MoveUpdate(float _DeltaTime, const FVector& _MovePos=FVector::Zero);
	
	// 커비 모드별 정리 함수
	void FireKirby(float _DeltaTime); // 불 커비
	void IceKirby(float _DeltaTime); // 아이스 커비
	void SirKirby(float _DeltaTime);
	void MikeKirby(float _DeltaTime);
	void HammerKirby(float _DeltaTime);
	
	// 카메라 Y축 제어 함수
	void CamYMove();
};

