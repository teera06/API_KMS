#pragma once

#include <EngineCore\Actor.h>

#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class AMainBoss : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMainBoss(); // 디폴트 생성자
	~AMainBoss(); // 디폴트 소멸자

	// delete Function
	AMainBoss(const AMainBoss& _Other) = delete; // 디폴트 복사 생성자
	AMainBoss(AMainBoss&& _Other) noexcept = delete; 
	AMainBoss& operator=(const AMainBoss& _Other) = delete; // 디폴트 대입 연산자
	AMainBoss& operator=(AMainBoss&& _Other) noexcept = delete;
	
	static AMainBoss* GetMainBoss(); // 몬스터나 상태창이 플레이어에 대한 정보를 알아야 할 때 사용

	UCollision* GetMonsterCollision()
	{
		return MonsterCollision;
	}

	UImageRenderer* GetMonsterRenderer()
	{
		return MonsterRenderer;
	}

	int GetHp() const
	{
		return Hp;
	}

	bool GetEndingChange() const
	{
		return EndingChange;
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

	// 몬스터 랜더링, 콜리전
	UImageRenderer* MonsterRenderer = nullptr; // 커비 랜더링 (이미지)
	UImageRenderer* Att2Renderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* MonsterCollision = nullptr;

	UCollision* Att1Collision = nullptr;
	UCollision* Att3Collision = nullptr;
	
	static AMainBoss* MainBoss;

	FVector MovePos = FVector::Zero;
	FVector JumpVector = FVector::Up*750.0f;

	float skillcooldowntime = 3.0f;
	float MoveSpeed = 50.0f; // 몬스터 스피드

	int WallX = 0; // 벽에 충돌할때 X축 범위
	int RandomAtt = 0;
	int Hp = 100;


	bool Ishit = false; 
	bool IsAtt = false;
	bool IsBullet = false;
	bool IsIce = false;
	bool Att1Ready = false;
	bool Att3Delay = false;
	bool Att2Delay = false;
	bool Att4Ready = false;

	bool Att1Sound = false;
	bool Att3Sound = false;
	bool Att4Sound = false;

	bool hitSound = false;


	bool EndingChange = false;

	void MoveUpdate(float _DeltaTime); // 몬스터 최종 움직임 제어

	void AniCreate(); // 애니메이션 관리

	void CalDir(float _DeltaTime);
	void Att1(float _DeltaTime);
	void Att2();
	void Att3(float _DeltaTime);
	void Att4(float _DeltaTime);

	void Att1Collisiongather(float _DeltaTime);
	void Att3Collisiongather(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
	void CalResult(float _DeltaTime);
	void hitEvent();

	void GroundUp();
};

