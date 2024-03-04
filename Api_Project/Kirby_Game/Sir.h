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

protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	UImageRenderer* SirRenderer = nullptr;
	UCollision* SirCollision = nullptr;

	EIceOwner Owner = EIceOwner::None;

	void AniCreate(); // �ִϸ��̼� ����
	void SkillDir();
	void Collisiongather(float _DeltaTime);
};

