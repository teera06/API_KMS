#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h"

class ASir :public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	ASir(); // 디폴트 생성자
	~ASir(); // 디폴트 소멸자

	// delete Function
	ASir(const ASir& _Other) = delete; // 디폴트 복사 생성자
	ASir(ASir&& _Other) noexcept = delete; 
	ASir& operator=(const ASir& _Other) = delete; // 디폴트 대입 연산자
	ASir& operator=(ASir&& _Other) noexcept = delete;

	void SetOwner(ESirOwner _Owner) // 커비, 몬스터 사용자가 누군이지 확인
	{
		Owner = _Owner;
	}

	void SetStartPos(const FVector& _StartPos)
	{
		StartPos = _StartPos;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	UImageRenderer* SirRenderer = nullptr;
	UCollision* SirCollision = nullptr;

	ESirOwner Owner = ESirOwner::None; // 누가 주인인지 -> 커비 Or 몬스터

	FVector StartPos = FVector::Zero; // 부메랑의 던지 방향의 이동 범위 계산 (왼쪽으로 던질 경우) 범위
	FVector StartDir = FVector::Right; // 부메랑의 이동 방향

	FVector DelX = FVector::Zero; // 커비가 받아내지 못하는 경우 대비 -> 범위 계산을 위한 플레이어 위치 저장 용
	
	float RangeX = 450.0f; // 던지는 방향의 이동 범위

	bool skillOn = false; // 스킬 On/Off 구분
	bool LRCheck = false; // false::Left, true=right -> 부메랑이 돌아오는 방향
	bool SirMonsterDelete = false;

	void AniCreate(); // 애니메이션 관리

	void CalDir();
	void SkillDir(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
};

