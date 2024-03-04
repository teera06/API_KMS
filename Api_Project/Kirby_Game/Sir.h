#pragma once
#include <EngineCore\Actor.h>
#include "ActorCommon.h"

#include "Kirby_Player.h"

class ASir :public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	ASir(); // ����Ʈ ������
	~ASir(); // ����Ʈ �Ҹ���

	// delete Function
	ASir(const ASir& _Other) = delete; // ����Ʈ ���� ������
	ASir(ASir&& _Other) noexcept = delete; 
	ASir& operator=(const ASir& _Other) = delete; // ����Ʈ ���� ������
	ASir& operator=(ASir&& _Other) noexcept = delete;

	void SetOwner(ESirOwner _Owner) // Ŀ��, ���� ����ڰ� �������� Ȯ��
	{
		Owner = _Owner;
	}

	void SetStartPos(const FVector& _StartPos)
	{
		StartPos = _StartPos;
	}

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	UImageRenderer* SirRenderer = nullptr;
	UCollision* SirCollision = nullptr;

	ESirOwner Owner = ESirOwner::None;

	FVector StartPos = FVector::Zero;
	FVector StartDir = FVector::Right;
	float RangeX = 300.0f; // �̵� ����

	void AniCreate(); // �ִϸ��̼� ����
	void SkillDir(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
};

