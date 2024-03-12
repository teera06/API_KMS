#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class AAllStar : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AAllStar(); // ����Ʈ ������
	~AAllStar(); // ����Ʈ �Ҹ���

	// delete Function
	AAllStar(const AAllStar& _Other) = delete; // ����Ʈ ���� ������
	AAllStar(AAllStar&& _Other) noexcept = delete;
	AAllStar& operator=(const AAllStar& _Other) = delete; // ����Ʈ ���� ������
	AAllStar& operator=(AAllStar&& _Other) noexcept = delete;

	
protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	UImageRenderer* AllStarRenderer = nullptr;
	UCollision* AllStarCollision = nullptr;

	FVector Move = FVector::Zero;
	float Speed = 500.0f;

	bool hit = false;
	bool hit2 = false;

	void Collisiongather(float _DeltaTime);
	void CalDir();
};
