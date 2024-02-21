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

	bool iceState = false;
	int scale = 0;
protected:
	FVector GetGravity(int _X, int _Y,float _DeltaTime); // 중력 부분 공통적으로 쓰일 부분

	void SetAtt(int _Att)
	{
		Att = _Att;
	}

	void SetHp(int _Hp)
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
	static bool EatState;
	static EAMode KirbyMode; // Kirby 모드
	static std::string ModeName; // Kirby 모드별 애니메이션 이름 체인지
private:
	float Gravity = 700.0f;
	FVector GravityValue = FVector::Zero;
	FVector Dir = FVector::Zero;
	
	// 커비, 몬스터 공통 변수
	int Hp = 0;
	int Att = 0;
};

