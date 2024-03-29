#pragma once

#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h"

class Apengi_Ice : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	Apengi_Ice(); // 디폴트 생성자
	~Apengi_Ice(); // 디폴트 소멸자

	// delete Function
	Apengi_Ice(const Apengi_Ice& _Other) = delete; // 디폴트 복사 생성자
	Apengi_Ice(Apengi_Ice&& _Other) noexcept = delete; 
	Apengi_Ice& operator=(const Apengi_Ice& _Other) = delete; // 디폴트 대입 연산자
	Apengi_Ice& operator=(Apengi_Ice&& _Other) noexcept = delete;
	
	UImageRenderer* GetMonsterRenderer()
	{
		return MonsterRenderer;
	}

	UCollision* GetMonsterCollision() // Get 랜더
	{
		return MonsterCollision;
	}
	
	void IceState();
	void SetBaseOnOff(const bool& _BaseOn)
	{
		BaseOn = _BaseOn;
	}

	void SetIsDie(const bool& _IsDie)
	{
		IsDie = _IsDie;
	}

	void SetDiePos(const FVector& _DiePos)
	{
		DiePos = _DiePos;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer();

	UImageRenderer* MonsterRenderer = nullptr; // 커비 랜더링 (이미지)
	UImageRenderer* MonsterDieRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* MonsterCollision = nullptr;

	FVector StartDir = FVector::Left; // 몬스터 초반 이동 방향

	FVector IceMove = FVector::Zero; // 얼음 이동 
	FVector DiePos = FVector::Zero; // 죽음 이동
	FVector MovePos = FVector::Zero;

	const float IceSpeed = 350.0f; // 얼음(얼려진 후) 이동 스피드
	const float sight = 250.0f; // 몬스터 시야
	const float AttRange = 150.0f; // 몬스터 공격 범위
	
	float skillcooldowntime = 0.0f;
	float MoveSpeed = 50.0f; // 몬스터 스피드
	float HitDietime = 0.2f;

	int WallX = 0; // 벽에 충돌할때 X축 범위

	bool BaseOn = false; // 커비에게 흡수 당할 때 확인 
	bool IsDie = false; // 죽은 상태 인지 확인
	bool IsIce = false; // 얼음 상태인지 확인
	bool IsAtt = false;
	bool IceAttcheck = false;
	bool Iseffect = false;

	void MoveUpdate(float _DeltaTime); // 몬스터 최종 움직임 제어

	void AniCreate(); // 애니메이션 관리

	void IceToMonster(float _DeltaTime);

	void CalDir(float _DeltaTime);
	void IceAtt();

	void Collisiongather(float _DeltaTime);
	void CalResult(float _DeltaTime);


	void GroundUp();
	
};

