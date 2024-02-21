#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class AMonster_Base : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	AMonster_Base(); // ����Ʈ ������
	~AMonster_Base(); // ����Ʈ �Ҹ���

	// delete Function
	AMonster_Base(const AMonster_Base& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Base(AMonster_Base&& _Other) noexcept = delete; 
	AMonster_Base& operator=(const AMonster_Base& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Base& operator=(AMonster_Base&& _Other) noexcept = delete;

	void IceState();
protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* MonsterRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* MonsterCollision=nullptr;

	AKirby_Player* Player = AKirby_Player::GetMainPlayer();

	FVector Dir = FVector::Right;
	void AniCreate();
	
	void BaseMove(float _DeltaTime);

};

