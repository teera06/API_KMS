#pragma once
#include <EngineCore\Actor.h>
#include "ModeEnum.h"
#include <string>
#include <string_view>

// ���� ���Ƿ� üũ�ϱ� -> �����丵
enum class PlayState
{
	Idle,
	Move,
	Jump,
	Attack,

};


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

	void Leftwalk(float _DeltaTime);
	void Rightwalk(float _DeltaTime);
	void RLrun(float _DeltaTime);


	void BaseKirby();
	void FireKirby();

	std::string_view GetNamechange()
	{
		return Namechange;
	}

	void SetNamechange(std::string_view _Namechange)
	{
		Namechange = _Namechange;
	}

	inline void SetMode(AMode _KirbyMode) // Ŀ�� ��� ü���� �Ҷ� ���
	{
		KirbyMode = _KirbyMode;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	//float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr;
	
	int RLpoint = 0; // ����(����, ������ ���� ��ȯ) üũ -> �߻� ���� 
	int JumpKey = 0; // ����Ű�� �������� �Ҽ� �ִ°� -> ���ߺξ�

	// �¿� �޸��� ani�� ����Ǳ� ���� ����
	bool rRunanicheck = false;
	bool lRunanicheck = false;
	bool AttMotion = false; // ���� ����� Ŀ��� �̵� �Ұ�
	bool flyMotion = false; // ���� ��� üũ
	bool SeetMotion = false;


	float WalkSpeed = 100.0f; // �ȴ� �ӵ�
	float RunSpeed = 200.0f; // �ٴ� �ӵ�

	void GravityCheck(float _DeltaTime);

	void InputTick(float _DeltaTime); // �⺻ �Է�Ű
	void ModeInputTick(); // ��庰 �Է�Ű

	AMode KirbyMode = AMode::Base; // Kirby ��� ������
	std::string Namechange = "Base_"; // �ִϸ��̼� �̸� �������ֱ�
	FVector LRCheck = { 100.0f, 0.0f, 0.0f, 0.0f }; // �⺻ Ŀ�� ���
	int Hp=100;
};

