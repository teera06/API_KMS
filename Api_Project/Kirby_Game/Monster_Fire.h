#pragma once
#include <EnginePlatform\EngineSound.h>
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class AMonster_Fire : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMonster_Fire(); // 디폴트 생성자
	~AMonster_Fire(); // 디폴트 소멸자

	// delete Function
	AMonster_Fire(const AMonster_Fire& _Other) = delete; // 디폴트 복사 생성자
	AMonster_Fire(AMonster_Fire&& _Other) noexcept = delete; 
	AMonster_Fire& operator=(const AMonster_Fire& _Other) = delete; // 디폴트 대입 연산자
	AMonster_Fire& operator=(AMonster_Fire&& _Other) noexcept = delete;

	void IceState();

	void SetBaseOnOff(const bool& _BaseOn)
	{
		BaseOn = _BaseOn;
	}

	UImageRenderer* GetMonsterRenderer()
	{
		return MonsterRenderer;
	}

	UCollision* GetMonsterCollision() // Get 랜더
	{
		return MonsterCollision;
	}

	void SetIsDie(const bool& _IsDie)
	{
		IsDie = _IsDie;
	}

	bool GetIsDie()
	{
		return IsDie;
	}

	void SetDiePos(const FVector& _DiePos)
	{
		DiePos = _DiePos;
	}

protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	UEngineSoundPlayer SAtt;
	// 몬스터 랜더링, 콜리전
	UImageRenderer* MonsterRenderer = nullptr; // 커비 랜더링 (이미지)
	UImageRenderer* MonsterDieRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* MonsterCollision = nullptr;

	FVector StartDir = FVector::Right; // 몬스터 초반 이동 방향

	FVector IceMove = FVector::Zero; // 얼음 이동 
	FVector DiePos = FVector::Zero; // 죽음 이동
	FVector MovePos = FVector::Zero;

	// 일반 몬스터 행동 범위
	FVector CurLocation = FVector::Zero; // 현재 액터 위치 저장
	FVector RangeXL = FVector::Zero; // 현재위치 기준 왼쪽 이동 범위
	FVector RangeXR = FVector::Zero; // 현재위치 기준 오른쪽 이동 범위

	float MoveSpeed = 30.0f; // 몬스터 스피드
	const float IceSpeed = 350.0f; // 얼음(얼려진 후) 이동 스피드

	float RangeX = 100.0f; // 이동 단위

	const float sight = 250.0f; // 몬스터 시야
	const float AttRange = 150.0f; // 몬스터 공격 범위

	int WallX = 0; // 벽에 충돌할때 X축 범위

	bool BaseOn = false; // 커비에게 흡수 당할 때 확인 
	bool IsDie = false; // 죽은 상태 인지 확인
	bool IsIce = false; // 얼음 상태인지 확인
	bool checkLocation = false; // 현재 위치 체크
	bool IsAtt = false;
	bool Iseffect = false;
	bool SAttIs = false;

	void MoveUpdate(float _DeltaTime); // 몬스터 최종 움직임 제어
	void BaseMove(float _DeltaTime); // 몬스터 기본 움직임

	void AniCreate(); // 애니메이션 관리


	void IceToMonster(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
	void CalDir(float _DeltaTime);
	void CalResult(float _DeltaTime);

	void GroundUp();
};

