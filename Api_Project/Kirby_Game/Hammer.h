#pragma once
#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class AHammer : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AHammer(); // ����Ʈ ������
	~AHammer(); // ����Ʈ �Ҹ���

	// delete Function
	AHammer(const AHammer& _Other) = delete; // ����Ʈ ���� ������
	AHammer(AHammer&& _Other) noexcept = delete; 
	AHammer& operator=(const AHammer& _Other) = delete; // ����Ʈ ���� ������
	AHammer& operator=(AHammer&& _Other) noexcept = delete;

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	// ���� ������, �ݸ���
	UImageRenderer* Renderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* Collision = nullptr;

	void GroundUp();
};

