#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h"

class AIce :public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AIce(); // ����Ʈ ������
	~AIce(); // ����Ʈ �Ҹ���

	// delete Function
	AIce(const AIce& _Other) = delete; // ����Ʈ ���� ������
	AIce(AIce&& _Other) noexcept = delete; 
	AIce& operator=(const AIce& _Other) = delete; // ����Ʈ ���� ������
	AIce& operator=(AIce&& _Other) noexcept = delete;

	void SetOwner(EIceOwner _Owner) // Ŀ�� ��� ü���� �Ҷ� ���
	{
		Owner = _Owner;
	}
protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	UImageRenderer* IceRenderer = nullptr;
	UCollision* IceCollision = nullptr;

	EIceOwner Owner = EIceOwner::None;
};

