#pragma once
#include <EngineCore\ImageRenderer.h>
#include "ModeEnum.h"

// ����, Ŀ��� ���, ���� ���X 
class UActorCommon
{
public:
	// constrcuter destructer
	UActorCommon(); // ����Ʈ ������
	~UActorCommon(); // ����Ʈ �Ҹ���

	// delete Function
	UActorCommon(const UActorCommon& _Other) = delete; // ����Ʈ ���� ������
	UActorCommon(UActorCommon&& _Other) noexcept = delete;
	UActorCommon& operator=(const UActorCommon& _Other) = delete; // ����Ʈ ���� ������
	UActorCommon& operator=(UActorCommon&& _Other) noexcept = delete;

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

	void SetAtt(const int& _Att)
	{
		Att = _Att;
	}

	
	inline int GetAtt()const
	{
		return Att;
	}

	static void SetEatState(const bool& _EatState)
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
	FVector MonsterDirNormal = FVector::Zero; // �÷��̾� �߰� ����

	int scale = 0; // ĳ���͵� �̹��� ũ�� -> ������ ���� �Լ��� ���� �򰥸���  �ֱ⿡ �׳� ������ ��
private:
	float Gravity = 700.0f;
	FVector GravityValue = FVector::Zero;
	FVector Dir = FVector::Zero;
	
	// Ŀ��, ���� ���� ����
	
	// static ����
	static std::string ModeName; // Kirby ��庰 �ִϸ��̼� �̸� ü����

	int Att = 0;
};

