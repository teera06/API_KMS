#pragma once
// 상속
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class AMonster_Base : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	AMonster_Base(); // 디폴트 생성자
	~AMonster_Base(); // 디폴트 소멸자

	// delete Function
	AMonster_Base(const AMonster_Base& _Other) = delete; // 디폴트 복사 생성자
	AMonster_Base(AMonster_Base&& _Other) noexcept = delete; 
	AMonster_Base& operator=(const AMonster_Base& _Other) = delete; // 디폴트 대입 연산자
	AMonster_Base& operator=(AMonster_Base&& _Other) noexcept = delete;

	void IceState();

	void SetBaseOnOff(const bool& _BaseOn)
	{
		BaseOn = _BaseOn;
	}

	bool GetBaseOnOff() const
	{
		return BaseOn;
	}


protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	// 몬스터 랜더링, 콜리전
	UImageRenderer* MonsterRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* MonsterCollision=nullptr;

	FVector StartDir = FVector::Left; // 몬스터 초반 이동 방향

	FVector IceMove = FVector::Zero; // 얼음 이동 
	FVector DiePos = FVector::Zero; // 죽음 이동

	void MoveUpdate(float _DeltaTime); // 몬스터 최종 움직임 제어
	void BaseMove(float _DeltaTime); // 몬스터 기본 움직임
	
	void AniCreate(); // 애니메이션 관리
	
	bool BaseOn = false; // 커비에게 흡수 당할 때 확인 
	bool IsDie = false; // 죽은 상태 인지 확인
	bool IsIce = false; // 얼음 상태인지 확인

	int WallX = 0; // 벽에 충돌할때 X축 범위

	float MoveSpeed = 80.0f; // 몬스터 스피드
	const float IceSpeed = 400.0f; // 얼음(얼려진 후) 이동 스피드

	// 일반 몬스터 행동 범위
	const int TurnValue = 300; // 몬스터 행동 강령
	int Value = TurnValue; // 몬스터 행동 강령

};

