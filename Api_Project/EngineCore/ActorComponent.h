#pragma once
#include "TickObject.h"

// ���� ����
class AActor;
// ���� : ���Ϳ��� �޸� �ΰ�����̶�� ���丸 �����ϴ� ������Ʈ
//        ���� ���Ϳ��� ���� ����̴�.
class UActorComponent : public UTickObject
{
	friend AActor; // AActor���� private���� ����

public:
	// constrcuter destructer
	UActorComponent();
	~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	AActor* GetOwner() // Get
	{
		return Owner;
	}

protected:

private:
	AActor* Owner = nullptr;

	void SetOwner(AActor* _Owner) // Set
	{
		Owner = _Owner;
	}


};

