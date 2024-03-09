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

	ESirOwner Owner = ESirOwner::None; // ���� �������� -> Ŀ�� Or ����

	FVector StartPos = FVector::Zero; // �θ޶��� ���� ������ �̵� ���� ��� (�������� ���� ���) ����
	FVector StartDir = FVector::Right; // �θ޶��� �̵� ����

	FVector DelX = FVector::Zero; // Ŀ�� �޾Ƴ��� ���ϴ� ��� ��� -> ���� ����� ���� �÷��̾� ��ġ ���� ��
	
	float RangeX = 450.0f; // ������ ������ �̵� ����

	bool skillOn = false; // ��ų On/Off ����
	bool LRCheck = false; // false::Left, true=right -> �θ޶��� ���ƿ��� ����
	bool SirMonsterDelete = false;

	void AniCreate(); // �ִϸ��̼� ����

	void CalDir();
	void SkillDir(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
};

