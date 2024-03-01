#pragma once
#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class AMonster_Sir : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMonster_Sir(); // ����Ʈ ������
	~AMonster_Sir(); // ����Ʈ �Ҹ���

	// delete Function
	AMonster_Sir(const AMonster_Sir& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Sir(AMonster_Sir&& _Other) noexcept = delete; 
	AMonster_Sir& operator=(const AMonster_Sir& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Sir& operator=(AMonster_Sir&& _Other) noexcept = delete;

protected:

private:
	void MoveUpdate(float _DeltaTime);
};

