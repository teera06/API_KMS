#pragma once
#include <EngineCore\Actor.h>

enum class Mode
{
	Base,
	Fire,

};

class Kirby_Player : public AActor
{
public:
	// constrcuter destructer
	Kirby_Player(); // ����Ʈ ������
	~Kirby_Player(); // ����Ʈ �Ҹ���

	// delete Function
	Kirby_Player(const Kirby_Player& _Other) = delete; // ����Ʈ ���� ������
	Kirby_Player(Kirby_Player&& _Other) noexcept = delete; 
	Kirby_Player& operator=(const Kirby_Player& _Other) = delete; // ����Ʈ ���� ������
	Kirby_Player& operator=(Kirby_Player&& _Other) noexcept = delete;

	void InputTick(float _DeltaTime);

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

	Mode KirbyMode = Mode::Base;
};

