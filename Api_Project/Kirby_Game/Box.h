#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class ABox : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	ABox(); // 디폴트 생성자
	~ABox(); // 디폴트 소멸자

	// delete Function
	ABox(const ABox& _Other) = delete; // 디폴트 복사 생성자
	ABox(ABox&& _Other) noexcept = delete; 
	ABox& operator=(const ABox& _Other) = delete; // 디폴트 대입 연산자
	ABox& operator=(ABox&& _Other) noexcept = delete;
	
	void SetIsItem(const bool& _IsItem)
	{
		IsItem = _IsItem;
	}

	void SetIsDelete(const bool& _IsDelete)
	{
		IsDelete = _IsDelete;
	}
	// TickObject (Level2) 오버라이드
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함
	// 몬스터 랜더링, 콜리전
	UImageRenderer* Renderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* CollisionTop = nullptr;
	UCollision* CollisionBody = nullptr;
	UCollision* CollisionItem = nullptr;

	FVector GravityVector = FVector::Zero; // 중력값 받기

	bool IsItem = false;
	bool IsDelete = false;
	void GroundUp();

	void Collisiongather(float _DeltaTime);
	void ItemCollisiongather();

	void ItemDrop();
};

