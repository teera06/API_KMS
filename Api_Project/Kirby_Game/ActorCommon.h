#pragma once
#include <EngineCore\ImageRenderer.h>
#include "ModeEnum.h"

// 몬스터, 커비는 사용, 맵은 사용X 
class ActorCommon
{
public:
	// constrcuter destructer
	ActorCommon(); // 디폴트 생성자
	~ActorCommon(); // 디폴트 소멸자

	// delete Function
	ActorCommon(const ActorCommon& _Other) = delete; // 디폴트 복사 생성자
	ActorCommon(ActorCommon&& _Other) noexcept = delete;
	ActorCommon& operator=(const ActorCommon& _Other) = delete; // 디폴트 대입 연산자
	ActorCommon& operator=(ActorCommon&& _Other) noexcept = delete;

	static UWindowImage* ColMapImage; // 우선 맵만 사용

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

	FVector GetDir()
	{
		return Dir;
	}

protected:
	FVector GetGravity(int _X, int _Y,float _DeltaTime); // 중력 부분 공통적으로 쓰일 부분

	void SetAtt(const int _Att)
	{
		Att = _Att;
	}
	void SetHp(const int _Hp)
	{
		Hp = _Hp;
	}
	
	inline int GetAtt()
	{
		return Att;
	}

	inline int GetHp()
	{
		return Hp;
	}

	static void SetEatState(const bool _EatState)
	{
		EatState = _EatState;
	}

	static std::string_view GetModeName() // Get 이름체인지
	{
		return ModeName;
	}

	static void SetModeName(std::string_view _ModeName) // Set 이름 체인지
	{
		ModeName = _ModeName;
	}

	static void SetMode(EAMode _KirbyMode) // 커비 모드 체인지 할때 사용
	{
		KirbyMode = _KirbyMode;
	}
	static bool EatState;
	static EAMode KirbyMode; // Kirby 모드

	// 우선 Set, Get으로 만들지 말지를 정하기
	FVector IceMove = FVector::Zero; // 얼음 이동 관련 공통 
	FVector MonsterDirNormal = FVector::Zero; // 플레이어 추격 방향

	// 아래에는 Set, Get 만들어두기 어중간한 변수들
	int checkX = 0; // 벽에 충돌할때 X축 범위
	bool IsIce = false; // 언 상태 인지 bool값 공통


	// 맴버 변수 고정 값 들
	const float sight = 250.0f; // 몬스터 시야
	float MoveSpeed = 30.0f; // 몬스터 공통 스피드
	const float IceSpeed = 200.0f; // 얼음(얼려진 후) 이동 스피드
	const int TurnValue = 300; // 몬스터 행동 강령
	int Value = TurnValue; // 몬스터 행동 강령

	int scale = 0; // 캐릭터들 이미지 크기 -> 스케일 관련 함수가 많아 헷갈리수  있기에 그냥 변수로 둠
private:
	float Gravity = 700.0f;
	FVector GravityValue = FVector::Zero;
	FVector Dir = FVector::Zero;
	
	// 커비, 몬스터 공통 변수
	
	// static 변수
	static std::string ModeName; // Kirby 모드별 애니메이션 이름 체인지

	int Hp = 0;
	int Att = 0;
};

