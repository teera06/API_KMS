#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"
#include "ActorCommon.h"
#include <EngineCore/Level.h>


class AKirby_HpBar :public AActor, public ActorCommon // ActorCommon(�߷�)
{
public:
	// constrcuter destructer
	AKirby_HpBar(); // ����Ʈ ������
	~AKirby_HpBar(); // ����Ʈ �Ҹ���

	// delete Function
	AKirby_HpBar(const AKirby_HpBar& _Other) = delete; // ����Ʈ ���� ������
	AKirby_HpBar(AKirby_HpBar&& _Other) noexcept = delete;
	AKirby_HpBar& operator=(const AKirby_HpBar& _Other) = delete; // ����Ʈ ���� ������
	AKirby_HpBar& operator=(AKirby_HpBar&& _Other) noexcept = delete;



protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	UImageRenderer* HpRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UImageRenderer* StateRenderer = nullptr; // Ŀ�� ������ (�̹���)

	FVector Move = FVector::Zero;
};

