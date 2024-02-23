#pragma once
#include <EngineCore\ImageRenderer.h>
#include "ModeEnum.h"

// ����, Ŀ��� ���, ���� ���X 
class ActorCommon
{
public:
	// constrcuter destructer
	ActorCommon(); // ����Ʈ ������
	~ActorCommon(); // ����Ʈ �Ҹ���

	// delete Function
	ActorCommon(const ActorCommon& _Other) = delete; // ����Ʈ ���� ������
	ActorCommon(ActorCommon&& _Other) noexcept = delete;
	ActorCommon& operator=(const ActorCommon& _Other) = delete; // ����Ʈ ���� ������
	ActorCommon& operator=(ActorCommon&& _Other) noexcept = delete;

	static UWindowImage* ColMapImage; // �켱 �ʸ� ���

	void SetDir(const FVector& _Dir)
	{
		Dir = _Dir;
	}

	FVector GetDir()
	{
		return Dir;
	}

protected:
	FVector GetGravity(int _X, int _Y,float _DeltaTime); // �߷� �κ� ���������� ���� �κ�

	void SetAtt(const int _Att)
	{
		Att = _Att;
	}
	void SetHp(const int _Hp)
	{
		Hp = _Hp;
	}
	
	inline int GetAtt()
	{
		return Att;
	}

	inline int GetHp()
	{
		return Hp;
	}

	static void SetEatState(const bool _EatState)
	{
		EatState = _EatState;
	}

	static std::string_view GetModeName() // Get �̸�ü����
	{
		return ModeName;
	}

	static void SetModeName(std::string_view _ModeName) // Set �̸� ü����
	{
		ModeName = _ModeName;
	}

	static void SetMode(EAMode _KirbyMode) // Ŀ�� ��� ü���� �Ҷ� ���
	{
		KirbyMode = _KirbyMode;
	}
	static bool EatState;
	static EAMode KirbyMode; // Kirby ���

	// �켱 Set, Get���� ������ ������ ���ϱ�
	FVector IceMove = FVector::Zero; // ���� �̵� ���� ���� 
	FVector MonsterDirNormal = FVector::Zero; // �÷��̾� �߰� ����

	// �Ʒ����� Set, Get �����α� ���߰��� ������
	int checkX = 0; // ���� �浹�Ҷ� X�� ����
	bool IsIce = false; // �� ���� ���� bool�� ����


	// �ɹ� ���� ���� �� ��
	const float sight = 250.0f; // ���� �þ�
	float MoveSpeed = 30.0f; // ���� ���� ���ǵ�
	const float IceSpeed = 200.0f; // ����(����� ��) �̵� ���ǵ�
	const int TurnValue = 300; // ���� �ൿ ����
	int Value = TurnValue; // ���� �ൿ ����

	int scale = 0; // ĳ���͵� �̹��� ũ�� -> ������ ���� �Լ��� ���� �򰥸���  �ֱ⿡ �׳� ������ ��
private:
	float Gravity = 700.0f;
	FVector GravityValue = FVector::Zero;
	FVector Dir = FVector::Zero;
	
	// Ŀ��, ���� ���� ����
	
	// static ����
	static std::string ModeName; // Kirby ��庰 �ִϸ��̼� �̸� ü����

	int Hp = 0;
	int Att = 0;
};

