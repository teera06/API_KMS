#pragma once
// 상속
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class AMonster_Base : public AActor, public UActorCommon
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

	UImageRenderer* GetMonsterRenderer() // Get 랜더
	{
		return MonsterRenderer;
	}

	void IceState(); // 아이스 공격을 당했을 때

	void SetBaseOnOff(const bool& _BaseOn) // 베이스 공격 당했을 때 값 확인 Set
	{
		BaseOn = _BaseOn; // 흡수 공격 당했을때 true
	}

	void SetIsDie(const bool& _IsDie) // 몬스터 죽음 bool
	{
		IsDie = _IsDie;
	}

	void SetDiePos(const FVector& _DiePos) // 몬스터가 죽으면서 이동하는 위치 Set
	{
		DiePos = _DiePos;
	}
protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	// 몬스터 랜더링, 콜리전
	UImageRenderer* MonsterRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* MonsterCollision = nullptr; // 몬스터 콜리전

	FVector StartDir = FVector::Right; // 몬스터 초반 이동 방향

	FVector IceMove = FVector::Zero; // 얼음 이동 
	FVector DiePos = FVector::Zero; // 죽음 이동
	// 일반 몬스터 행동 범위
	FVector CurLocation = FVector::Zero; // 현재 액터 위치 저장
	FVector RangeXL = FVector::Zero; // 현재위치 기준 왼쪽 이동 범위
	FVector RangeXR = FVector::Zero; // 현재위치 기준 오른쪽 이동 범위

	const float IceSpeed = 350.0f; // 얼음(얼려진 후) 이동 스피드
	float MoveSpeed = 30.0f; // 몬스터 스피드
	float RangeX = 100.0f; // 이동 단위
	
	int WallX = 0; // 벽에 충돌할때 X축 범위

	bool BaseOn = false; // 커비에게 흡수 당할 때 확인 
	bool IsDie = false; // 죽은 상태 인지 확인
	bool IsIce = false; // 얼음 상태인지 확인
	bool checkLocation = false; // 현재 위치 체크

	void MoveUpdate(float _DeltaTime); // 몬스터 최종 움직임 제어
	void BaseMove(float _DeltaTime); // 몬스터 기본 움직임

	void AniCreate(); // 애니메이션 관리

	void IceToMonster(float _DeltaTime); // 얼음 상태일 때 충돌 관리
	void Collisiongather(float _DeltaTime); // 얼지 않은 상태일때 충돌 관리
	void CalDir(); // 플레이어 위치 계산
	void CalResult(float _DeltaTime); // 최종 움직임 계산

	void GroundUp(); // 땅 박힘 해결
};

