#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class ABox : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	ABox(); // ����Ʈ ������
	~ABox(); // ����Ʈ �Ҹ���

	// delete Function
	ABox(const ABox& _Other) = delete; // ����Ʈ ���� ������
	ABox(ABox&& _Other) noexcept = delete; 
	ABox& operator=(const ABox& _Other) = delete; // ����Ʈ ���� ������
	ABox& operator=(ABox&& _Other) noexcept = delete;
	
	void SetIsItem(const bool& _IsItem)
	{
		IsItem = _IsItem;
	}

	void SetIsDelete(const bool& _IsDelete)
	{
		IsDelete = _IsDelete;
	}
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����
	// ���� ������, �ݸ���
	UImageRenderer* Renderer = nullptr; // Ŀ�� ������ (�̹���)
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

