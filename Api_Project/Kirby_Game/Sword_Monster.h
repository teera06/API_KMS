#pragma once
#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class Sword_Monster : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	Sword_Monster(); // ����Ʈ ������
	~Sword_Monster(); // ����Ʈ �Ҹ���

	// delete Function
	Sword_Monster(const Sword_Monster& _Other) = delete; // ����Ʈ ���� ������
	Sword_Monster(Sword_Monster&& _Other) noexcept = delete; 
	Sword_Monster& operator=(const Sword_Monster& _Other) = delete; // ����Ʈ ���� ������
	Sword_Monster& operator=(Sword_Monster&& _Other) noexcept = delete;

protected:

private:
	void MoveUpdate(float _DeltaTime);
};

