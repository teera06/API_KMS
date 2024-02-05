#pragma once
#include <EngineCore\Actor.h>
#include "ModeEnum.h"
#include <string>
#include <string_view>

// 내일 강의로 체크하기 -> 리펙토링
enum class PlayState
{
	Idle,
	Move,
	Jump,
	Attack,

};


class AKirby_Player : public AActor
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

	void Leftwalk(float _DeltaTime);
	void Rightwalk(float _DeltaTime);
	void RLrun(float _DeltaTime);


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
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	//float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr;
	
	int RLpoint = 0; // 방향(왼쪽, 오른쪽 방향 전환) 체크 -> 발사 방향 
	int JumpKey = 0; // 점프키를 눌렀을때 할수 있는것 -> 공중부양

	// 좌우 달리기 ani가 실행되기 위한 조건
	bool rRunanicheck = false;
	bool lRunanicheck = false;
	bool AttMotion = false; // 공격 모션중 커비는 이동 불가
	bool flyMotion = false; // 나는 모션 체크
	bool SeetMotion = false;


	float WalkSpeed = 100.0f; // 걷는 속도
	float RunSpeed = 200.0f; // 뛰는 속도

	void GravityCheck(float _DeltaTime);

	void InputTick(float _DeltaTime); // 기본 입력키
	void ModeInputTick(); // 모드별 입력키

	AMode KirbyMode = AMode::Base; // Kirby 모드 모음집
	std::string Namechange = "Base_"; // 애니메이션 이름 변경해주기
	FVector LRCheck = { 100.0f, 0.0f, 0.0f, 0.0f }; // 기본 커비가 사용
	int Hp=100;
};

