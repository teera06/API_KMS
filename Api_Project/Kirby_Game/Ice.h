#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h"

class AIce :public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AIce(); // 디폴트 생성자
	~AIce(); // 디폴트 소멸자

	// delete Function
	AIce(const AIce& _Other) = delete; // 디폴트 복사 생성자
	AIce(AIce&& _Other) noexcept = delete; 
	AIce& operator=(const AIce& _Other) = delete; // 디폴트 대입 연산자
	AIce& operator=(AIce&& _Other) noexcept = delete;

	void SetOwner(EIceOwner _Owner) // 커비 모드 체인지 할때 사용
	{
		Owner = _Owner;
	}
protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	UImageRenderer* IceRenderer = nullptr;
	UCollision* IceCollision = nullptr;

	EIceOwner Owner = EIceOwner::None;
};

