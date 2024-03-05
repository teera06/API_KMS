#pragma once
// ���
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class SubBoss : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	SubBoss(); // ����Ʈ ������
	~SubBoss(); // ����Ʈ �Ҹ���

	// delete Function
	SubBoss(const SubBoss& _Other) = delete; // ����Ʈ ���� ������
	SubBoss(SubBoss&& _Other) noexcept = delete; 
	SubBoss& operator=(const SubBoss& _Other) = delete; // ����Ʈ ���� ������
	SubBoss& operator=(SubBoss&& _Other) noexcept = delete;

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	// ���� ������, �ݸ���
	UImageRenderer* MonsterRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* MonsterCollision = nullptr;

	void CalDir();

	void GroundUp();
};

