#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class ABullet : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	ABullet(); // ����Ʈ ������
	~ABullet(); // ����Ʈ �Ҹ���

	// delete Function
	ABullet(const ABullet& _Other) = delete; // ����Ʈ ���� ������
	ABullet(ABullet&& _Other) noexcept = delete; 
	ABullet& operator=(const ABullet& _Other) = delete; // ����Ʈ ���� ������
	ABullet& operator=(ABullet&& _Other) noexcept = delete;

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	UImageRenderer* bulletRenderer = nullptr;
	UCollision* bulletCollision = nullptr;

	float Speed = 500.0f;
	void AniCreate(); // �ִϸ��̼� ����

	void SkillDir(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
};

