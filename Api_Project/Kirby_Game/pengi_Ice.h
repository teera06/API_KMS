#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"


class Apengi_Ice : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	Apengi_Ice(); // ����Ʈ ������
	~Apengi_Ice(); // ����Ʈ �Ҹ���

	// delete Function
	Apengi_Ice(const Apengi_Ice& _Other) = delete; // ����Ʈ ���� ������
	Apengi_Ice(Apengi_Ice&& _Other) noexcept = delete; 
	Apengi_Ice& operator=(const Apengi_Ice& _Other) = delete; // ����Ʈ ���� ������
	Apengi_Ice& operator=(Apengi_Ice&& _Other) noexcept = delete;
	void IceState();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* PengiRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* PengiCollision = nullptr;

	AKirby_Player* Player = AKirby_Player::GetMainPlayer();
	
	FVector Dir = FVector::Right;
	void AniCreate();
	void BaseMove(float _DeltaTime);
};

