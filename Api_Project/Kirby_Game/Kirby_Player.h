#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"
#include "ActorCommon.h"
// 내일 강의로 체크하기 -> 리펙토링
class AKirby_Player : public AActor, public ActorCommon
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

	inline void SetMode(AMode _KirbyMode) // 커비 모드 체인지 할때 사용
	{
		KirbyMode = _KirbyMode;
	}

protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


	// 상태 주요 업데이트
	void StateChange(ActorState _State);
	void StateUpdate(float _DeltaTime);

	// 상태 함수들
	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Run(float _DeltaTime);

	// 상태 시작 함수들
	void IdleStart();
	void WalkStart();
	void JumpStart();
	void RunStart();
	

	// 각 상태마다 언제나 가장 위에 실행되어야 한다.
	void DirCheck();

	std::string GetAnimationName(std::string_view _Name);
	std::string CurAnimationName = "None";
	ActorState State = ActorState::None;
	EActorDir DirState = EActorDir::Right;
private:
	//float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr; // 커비 랜더링 (이미지)
	
	// 행동별 속도 정리
	float WalkSpeed = 100.0f; // 걷는 속도
	float RunSpeed = 250.0f; // 뛰는 속도
	

	void ModeInputTick(); // 모드별 입력키

	FVector GravityCheck = FVector::Zero;
	AMode KirbyMode = AMode::Base; // Kirby 모드 모음집
	std::string Namechange = "Base_"; // 애니메이션 이름 변경해주기
	
	int Hp=100;
};

