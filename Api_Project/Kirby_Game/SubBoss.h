#pragma once
// 상속
#include <EngineCore\Actor.h>

#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class ASubBoss : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	ASubBoss(); // 디폴트 생성자
	~ASubBoss(); // 디폴트 소멸자

	// delete Function
	ASubBoss(const ASubBoss& _Other) = delete; // 디폴트 복사 생성자
	ASubBoss(ASubBoss&& _Other) noexcept = delete; 
	ASubBoss& operator=(const ASubBoss& _Other) = delete; // 디폴트 대입 연산자
	ASubBoss& operator=(ASubBoss&& _Other) noexcept = delete;

	static ASubBoss* GetMainSubBoss(); // 몬스터나 상태창이 플레이어에 대한 정보를 알아야 할 때 사용

	UImageRenderer* GetMonsterRenderer()
	{
		return MonsterRenderer;
	}

	int GetHp() const
	{ 
		return Hp;
	}

protected:
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	static ASubBoss* MainSubBoss;

	// 몬스터 랜더링, 콜리전
	UImageRenderer* MonsterRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* MonsterCollision = nullptr;

	UImageRenderer* AttRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* AttCollision = nullptr;

	FVector StartDir = FVector::Left; // 몬스터 초반 이동 방향
	FVector MovePos = FVector::Zero;

	void MoveUpdate(float _DeltaTime); // 몬스터 최종 움직임 제어

	void AniCreate(); // 애니메이션 관리

	void CalDir(float _DeltaTime);
	void Att1(float _DeltaTime);
	void Att2();

	void AttCollisiongather(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
	void CalResult(float _DeltaTime);

	void GroundUp();

	bool BaseOn = false; // 커비에게 흡수 당할 때 확인 
	bool IsDie = false; // 죽은 상태 인지 확인
	bool IsIce = false; // 얼음 상태인지 확인
	bool IsAtt = false;

	int WallX = 0; // 벽에 충돌할때 X축 범위
	int RandomAtt = 0;
	int Hp = 100;

	float skillcooldowntime = 3.0f;
	float MoveSpeed = 50.0f; // 몬스터 스피드
	const float IceSpeed = 350.0f; // 얼음(얼려진 후) 이동 스피드
	const float sight = 250.0f; // 몬스터 시야
};

