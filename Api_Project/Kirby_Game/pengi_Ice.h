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
	
	FVector DirMonster = FVector::Left;
	FVector IceMove = FVector::Zero; // ���� �̵� ���� ���� 
	void AniCreate();
	void BaseMove(float _DeltaTime);
	const float sight = 250.0f; // ���� �þ�
	bool IsIce = false; // �� ���� ���� bool�� ����
	int checkX = 0; // ���� �浹�Ҷ� X�� ����
	float MoveSpeed = 30.0f; // ���� ���� ���ǵ�
	const float IceSpeed = 200.0f; // ����(����� ��) �̵� ���ǵ�
};

