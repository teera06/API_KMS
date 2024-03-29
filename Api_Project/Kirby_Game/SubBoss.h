#pragma once
// 상속
#include <EngineBase\EngineRandom.h>
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

	UCollision* GetMonsterCollision()
	{
		return MonsterCollision;
	}

	int GetHp() const
	{
		return Hp;
	}

	void AddHP(const int& _Value)
	{
		Hp += _Value;
	}

	void SetIshit(const bool& _Ishit)
	{
		Ishit = _Ishit;
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
	UImageRenderer* AttRenderer = nullptr; // 커비 랜더링 (이미지)
	
	UCollision* MonsterCollision = nullptr;
	UCollision* AttCollision = nullptr;

	FVector MovePos = FVector::Zero;

	float skillcooldowntime = 3.0f;
	float MoveSpeed = 50.0f; // 몬스터 스피드

	int WallX = 0; // 벽에 충돌할때 X축 범위
	int RandomAtt = 0;
	int Hp = 100;

	bool Ishit = false; // 죽은 상태 인지 확인
	bool Sound1 = false;
	bool Sound2 = false;

	bool hitSound = false;

	void MoveUpdate(float _DeltaTime); // 몬스터 최종 움직임 제어

	void AniCreate(); // 애니메이션 관리

	void CalDir(float _DeltaTime);
	void Att1(float _DeltaTime);
	void Att2();

	void AttCollisiongather(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
	void CalResult(float _DeltaTime);
	void hitEvent();

	void GroundUp();
};

