#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"
#include "ActorCommon.h"
// 내일 강의로 체크하기 -> 리펙토링
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

	void BaseKirby(float _DeltaTime); // 기본 커비 
	void FireKirby(); // 불 커비

	std::string_view GetAniNamechange() // Get 이름체인지
	{
		return AniNamechange;
	}

	void SetNamechange(std::string_view _AniNamechange) // Set 이름 체인지
	{
		AniNamechange = _AniNamechange;
	}

	inline void SetMode(AMode _KirbyMode) // 커비 모드 체인지 할때 사용
	{
		KirbyMode = _KirbyMode;
	}

protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// 몬스터, 커비 등 같이 사용하는 공통점이 생길수 있으니 우선 추후 생각
	//--------------------------------------------------
	// 상태 주요 업데이트
	void StateChange(ActorState _State);
	void StateUpdate(float _DeltaTime);

	// 상태 함수들
	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Jump(float _DeltaTime);
	void HeadDown(float _DeltaTime);
	// 커비만 가능 한 상태 
	void Run(float _DeltaTime);
	void Absorption(float _DeltaTime); // 흡수

	// 상태 시작 함수들
	void IdleStart();
	void HeavyIdleStart();

	void WalkStart();
	void HeavyMoveStart();

	void JumpStart();
	void RunStart();
	void AbsorptionStart();
	void HeadDownStart();

	// 각 상태마다 언제나 가장 위에 실행되어야 한다.
	void DirCheck();

	std::string GetAnimationName(std::string_view _Name);
	std::string CurAnimationName = "None";
	ActorState State = ActorState::None;
	EActorDir DirState = EActorDir::Right;
	//---------------------------------------------------
private:
	//float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr; // 커비 랜더링 (이미지)
	
	// 행동별 속도 정리
	float checkSpeed = 0.0f;
	float WalkSpeed = 100.0f; // 걷는 속도
	float RunSpeed = 250.0f; // 뛰는 속도
	float camSpeed = 500.0f; // 카메라 속도
	float HeavySpeed = 80.0f; // EatState일때 스피드
	
	bool EatState = false;

	void ModeInputTick(float _DeltaTime); // 모드별 입력키
	void AniCreate();

	FVector GravityCheck = FVector::Zero; // 중력값 받기
	AMode KirbyMode = AMode::Base; // Kirby 모드
	std::string AniNamechange = "Base_"; // Kirby 모드별 애니메이션 이름 체인지
};

