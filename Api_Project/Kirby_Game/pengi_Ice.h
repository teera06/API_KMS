#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

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
	void SetBaseOnOff(const bool& _BaseOn)
	{
		BaseOn = _BaseOn;
	}

	bool GetBaseOnOff() const
	{
		return BaseOn;
	}

	UImageRenderer* GetMonsterRenderer()
	{
		return MonsterRenderer;
	}

	void SetIsDie(const bool& _IsDie)
	{
		IsDie = _IsDie;
	}

	void SetDiePos(const FVector& _DiePos)
	{
		DiePos = _DiePos;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer();

	UImageRenderer* MonsterRenderer = nullptr; // Ŀ�� ������ (�̹���)
	UCollision* MonsterCollision = nullptr;

	FVector StartDir = FVector::Left; // ���� �ʹ� �̵� ����

	FVector IceMove = FVector::Zero; // ���� �̵� 
	FVector DiePos = FVector::Zero; // ���� �̵�

	void MoveUpdate(float _DeltaTime); // ���� ���� ������ ����
	
	void AniCreate(); // �ִϸ��̼� ����

	void IceToMonster(float _DeltaTime);

	bool BaseOn = false; // Ŀ�񿡰� ��� ���� �� Ȯ�� 
	bool IsDie = false; // ���� ���� ���� Ȯ��
	bool IsIce = false; // ���� �������� Ȯ��

	int WallX = 0; // ���� �浹�Ҷ� X�� ����

	float MoveSpeed = 30.0f; // ���� ���ǵ�
	const float IceSpeed = 350.0f; // ����(����� ��) �̵� ���ǵ�
	const float sight = 250.0f; // ���� �þ�
	
};

