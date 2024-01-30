#pragma once
#include <EngineCore\Actor.h>
#include "ModeEnum.h"

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

	void InputTick(float _DeltaTime);

	void ModeInputTick(float _DeltaTime);

	inline void SetMode(AMode _KirbyMode)
	{
		KirbyMode = _KirbyMode;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr;

	int RLpoint = 0; // 방향(왼쪽, 오른쪽 방향 전환) 체크 -> 발사 방향 
	int JumpKey = 0; // 점프키를 눌렀을때 할수 있는것 -> 공중부양
	float WalkSpeed = 100.0f; // 걷는 속도
	float RunSpeed = 200.0f; // 뛰는 속도

	AMode KirbyMode = AMode::Base; // Kirby 모드 모음집
	FVector LRCheck = { 100.0f, 0.0f, 0.0f, 0.0f };
	int Hp=100;
};

