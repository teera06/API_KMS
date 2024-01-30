#pragma once
#include <EngineCore\Actor.h>
#include "ModeEnum.h"

class AKirby_Player : public AActor
{
public:
	// constrcuter destructer
	AKirby_Player(); // ����Ʈ ������
	~AKirby_Player(); // ����Ʈ �Ҹ���

	// delete Function
	AKirby_Player(const AKirby_Player& _Other) = delete; // ����Ʈ ���� ������
	AKirby_Player(AKirby_Player&& _Other) noexcept = delete;
	AKirby_Player& operator=(const AKirby_Player& _Other) = delete; // ����Ʈ ���� ������
	AKirby_Player& operator=(AKirby_Player&& _Other) noexcept = delete;

	void InputTick(float _DeltaTime); // �⺻ �Է�Ű
	void ModeInputTick(); // ��庰 �Է�Ű

	void BaseKirby();
	void FireKirby();

	inline void SetMode(AMode _KirbyMode) // Ŀ�� ��� ü���� �Ҷ� ���
	{
		KirbyMode = _KirbyMode;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr;

	int RLpoint = 0; // ����(����, ������ ���� ��ȯ) üũ -> �߻� ���� 
	int JumpKey = 0; // ����Ű�� �������� �Ҽ� �ִ°� -> ���ߺξ�
	float WalkSpeed = 100.0f; // �ȴ� �ӵ�
	float RunSpeed = 200.0f; // �ٴ� �ӵ�

	AMode KirbyMode = AMode::Base; // Kirby ��� ������
	FVector LRCheck = { 100.0f, 0.0f, 0.0f, 0.0f }; // �⺻ Ŀ�� ���
	int Hp=100;
};

