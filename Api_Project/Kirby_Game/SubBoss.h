#pragma once
// 상속
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class SubBoss : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	SubBoss(); // 디폴트 생성자
	~SubBoss(); // 디폴트 소멸자

	// delete Function
	SubBoss(const SubBoss& _Other) = delete; // 디폴트 복사 생성자
	SubBoss(SubBoss&& _Other) noexcept = delete; 
	SubBoss& operator=(const SubBoss& _Other) = delete; // 디폴트 대입 연산자
	SubBoss& operator=(SubBoss&& _Other) noexcept = delete;

	UImageRenderer* GetMonsterRenderer()
	{
		return MonsterRenderer;
	}

protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	// 몬스터 랜더링, 콜리전
	UImageRenderer* MonsterRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* MonsterCollision = nullptr;

	FVector StartDir = FVector::Left; // 몬스터 초반 이동 방향
	FVector MovePos = FVector::Zero;

	void MoveUpdate(float _DeltaTime); // 몬스터 최종 움직임 제어

	void AniCreate(); // 애니메이션 관리

	void IceToMonster(float _DeltaTime);

	void CalDir(float _DeltaTime);
	void IceAtt();

	void Collisiongather(float _DeltaTime);
	void CalResult(float _DeltaTime);


	void GroundUp();

	bool BaseOn = false; // 커비에게 흡수 당할 때 확인 
	bool IsDie = false; // 죽은 상태 인지 확인
	bool IsIce = false; // 얼음 상태인지 확인
	bool IsAtt = false;
	float skillcooldowntime = 0.0f;

	int WallX = 0; // 벽에 충돌할때 X축 범위

	float MoveSpeed = 50.0f; // 몬스터 스피드
	const float IceSpeed = 350.0f; // 얼음(얼려진 후) 이동 스피드
	const float sight = 250.0f; // 몬스터 시야
	const float AttRange = 150.0f; // 몬스터 공격 범위
};

