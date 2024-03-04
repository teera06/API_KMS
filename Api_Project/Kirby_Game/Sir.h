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

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // 몬스터는 플레이어를 알고 있어야함

	UImageRenderer* SirRenderer = nullptr;
	UCollision* SirCollision = nullptr;

	EIceOwner Owner = EIceOwner::None;

	void AniCreate(); // 애니메이션 관리
	void SkillDir();
	void Collisiongather(float _DeltaTime);
};

