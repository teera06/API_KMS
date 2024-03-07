#pragma once
#include <EngineCore\Actor.h>

#include "Kirby_Player.h" // MainPlayer

class Bullet : public AActor
{
public:
	// constrcuter destructer
	Bullet(); // ����Ʈ ������
	~Bullet(); // ����Ʈ �Ҹ���

	// delete Function
	Bullet(const Bullet& _Other) = delete; // ����Ʈ ���� ������
	Bullet(Bullet&& _Other) noexcept = delete; 
	Bullet& operator=(const Bullet& _Other) = delete; // ����Ʈ ���� ������
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

protected:
	// TickObject (Level2) �������̵�
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AKirby_Player* MainPlayer = AKirby_Player::GetMainPlayer(); // ���ʹ� �÷��̾ �˰� �־����

	UImageRenderer* bulletRenderer = nullptr;
	UCollision* bulletCollision = nullptr;

	void AniCreate(); // �ִϸ��̼� ����

	void SkillDir(float _DeltaTime);
	void Collisiongather(float _DeltaTime);
};

