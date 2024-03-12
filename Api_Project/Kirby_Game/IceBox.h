#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class AIceBox : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AIceBox(); // ����Ʈ ������
	~AIceBox(); // ����Ʈ �Ҹ���

	// delete Function
	AIceBox(const AIceBox& _Other) = delete; // ����Ʈ ���� ������
	AIceBox(AIceBox&& _Other) noexcept = delete; 
	AIceBox& operator=(const AIceBox& _Other) = delete; // ����Ʈ ���� ������
	AIceBox& operator=(AIceBox&& _Other) noexcept = delete;

	

	void SetIsItem(const bool& _IsItem)
	{
		IsItem = _IsItem;
	}

	void SetIsDelete(const bool& _IsDelete)
	{
		IsDelete = _IsDelete;
	}

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����
	// ���� ������, �ݸ���
	UImageRenderer* Renderer = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* hitRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* CollisionTop = nullptr;
	UCollision* CollisionBody = nullptr;
	UCollision* CollisionItem = nullptr;

	FVector GravityVector = FVector::Zero; // �߷°� �ޱ�

	bool IsItem = false;
	bool IsDelete = false;
	void GroundUp();
	
	void Collisiongather(float _DeltaTime);
	void ItemCollisiongather();

	void ItemDrop();
};

