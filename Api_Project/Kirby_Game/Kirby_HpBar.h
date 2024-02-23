#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"
#include "ActorCommon.h"
#include <EngineCore/Level.h>


class Kirby_HpBar :public AActor, public ActorCommon // ActorCommon(�߷�)
{
public:
	// constrcuter destructer
	Kirby_HpBar(); // ����Ʈ ������
	~Kirby_HpBar(); // ����Ʈ �Ҹ���

	// delete Function
	Kirby_HpBar(const Kirby_HpBar& _Other) = delete; // ����Ʈ ���� ������
	Kirby_HpBar(Kirby_HpBar&& _Other) noexcept = delete; 
	Kirby_HpBar& operator=(const Kirby_HpBar& _Other) = delete; // ����Ʈ ���� ������
	Kirby_HpBar& operator=(Kirby_HpBar&& _Other) noexcept = delete;

protected:

private:
	UImageRenderer* HpRenderer = nullptr; // Ŀ�� ������ (�̹���)
};

