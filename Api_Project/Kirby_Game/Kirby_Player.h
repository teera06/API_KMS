#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"
#include "ActorCommon.h"
#include <EngineCore/Level.h>

class AKirby_Player : public AActor, public ActorCommon // ActorCommon(중력)
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

	static AKirby_Player* GetMainPlayer();
	
	UImageRenderer* GetKirbyRender()
	{
		return KirbyRenderer;
	}

protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// 몬스터, 커비 등 같이 사용하는 공통점이 생길수 있으니 우선 추후 생각
	//--------------------------------------------------
	// 상태 주요 업데이트
	void StateAniChange(EActorState _State);
	void StateUpdate(float _DeltaTime);

	// 상태 함수들
	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Jump(float _DeltaTime);
	void FlyReady(float _DeltaTime);
	void Fly(float _DeltaTime);
	void Flyfall(float _DeltaTime);
	void HeadDown(float _DeltaTime);
	
	// 커비만 가능 한 상태 
	void Run(float _DeltaTime);
	void Absorption(float _DeltaTime); // 흡수
	void All_Attack(float _DeltaTime); // 공격

	// 상태 시작 함수들
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

	// 각 상태마다 언제나 가장 위에 실행되어야 한다.
	void DirCheck();

	std::string GetAnimationName(std::string_view _Name);
	std::string CurAnimationName = "None";
	EActorState State = EActorState::None;
	EActorDir DirState = EActorDir::Right;
	//---------------------------------------------------
private:
	//float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr; // 커비 랜더링 (이미지)
	UCollision* KirbyCollision = nullptr;
	// 행동별 속도 정리
	float checkSpeed = 0.0f;
	float WalkSpeed = 200.0f; // 걷는 속도
	float RunSpeed = 250.0f; // 뛰는 속도

	float FlySpeed = 180.0f;

	float camSpeed = 500.0f; // 카메라 속도

	float HeavyWalkSpeed = 180.0f; // EatState일때 스피드
	float HeavyRunSpeed = 230.0f;
	
	float checkposX = 30.0f;
	float checkposY = 30.0f;

	bool FlyState = false;
	

	void ModeInputTick(float _DeltaTime); // 모드별 입력키
	void AniCreate();

	
	FVector CamstopMove = FVector::Zero; // 카메라 멈췄을 때 캐릭터가 움직인 값
	FVector GravityVector = FVector::Zero; // 중력값 받기

	FVector JumpPowerIdle = FVector::Up * 400;
	FVector JumpPowerMove = FVector::Up * 500;

	FVector JumpVector = FVector::Zero;

	FVector PlayMove = FVector::Zero;

	FVector CurY = FVector::Zero;


	static AKirby_Player* MainPlayer;

	void CalGravityVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime, const FVector& _MovePos= FVector::Zero);
	void MoveUpdate(float _DeltaTime, const FVector& _MovePos=FVector::Zero);
	void FireKirby(); // 불 커비
	void IceKirby(float _DeltaTime); // 아이스 커비
	void CamYMove();

	bool SkillOnOff = false;
};

