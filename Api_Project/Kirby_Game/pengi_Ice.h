#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"


class pengi_Ice : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	pengi_Ice(); // ����Ʈ ������
	~pengi_Ice(); // ����Ʈ �Ҹ���

	// delete Function
	pengi_Ice(const pengi_Ice& _Other) = delete; // ����Ʈ ���� ������
	pengi_Ice(pengi_Ice&& _Other) noexcept = delete; 
	pengi_Ice& operator=(const pengi_Ice& _Other) = delete; // ����Ʈ ���� ������
	pengi_Ice& operator=(pengi_Ice&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* PengiRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* PengiCollision = nullptr;

	void AniCreate();
};

