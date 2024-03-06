#pragma once

#include <EngineCore\Actor.h>

#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class AMainBoss : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMainBoss(); // ����Ʈ ������
	~AMainBoss(); // ����Ʈ �Ҹ���

	// delete Function
	AMainBoss(const AMainBoss& _Other) = delete; // ����Ʈ ���� ������
	AMainBoss(AMainBoss&& _Other) noexcept = delete; 
	AMainBoss& operator=(const AMainBoss& _Other) = delete; // ����Ʈ ���� ������
	AMainBoss& operator=(AMainBoss&& _Other) noexcept = delete;

protected:

private:
};

