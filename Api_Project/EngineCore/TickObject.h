#pragma once
#include <EngineBase\EngineDebug.h>

// ���� :
class UTickObject
{

public:
	// constrcuter destructer
	UTickObject();
	virtual ~UTickObject();// ���� ���� �θ�Ŭ���� -> ���� �Ҹ��ڷ� ����

	// delete Function
	UTickObject(const UTickObject& _Other) = delete;
	UTickObject(UTickObject&& _Other) noexcept = delete;
	UTickObject& operator=(const UTickObject& _Other) = delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept = delete;

	void ActiveOn()
	{
		IsActiveValue = true;
	}

	void ActiveOff()
	{
		IsActiveValue = false;
	}

	void SetActive(bool _Active)
	{
		IsActiveValue = _Active;
	}

	bool IsActive()
	{
		// ���� �����ְ�         ������ �ʾҴٸ�
		return IsActiveValue && IsDestroyValue == false;
	}


	virtual void Destroy(float _DestroyTime = 0.0f) // ���ڰ��� �ȳ־��ָ� 0.0f�� ����
	{
		IsDestroyUpdate = true;
		DestroyTime = _DestroyTime;
		if (0.0f >= _DestroyTime) // ���ڰ����� ���� _DestroyTime�� 0.0f���� �۰ų� ���� �� ����
		{
			this->IsDestroyValue = true;
		}
	}

	int GetOrder() // Get 
	{
		return Order;
	}

	virtual void SetOrder(int _Order) // Set
	{
		Order = _Order;
	}

	virtual void DestroyUpdate(float _DeltaTime)
	{
		if (false == IsDestroyUpdate) // false�� ��� �׳� ����
		{
			return;
		}

		// true�� ���
		DestroyTime -= _DeltaTime; // Destroy()���� Set �� DestroyTime�� _DeltaTime ����
		if (0.0f >= DestroyTime) // DestroyTime�� 0���� �۰ų� �������� ����
		{
			Destroy(0.0f); // ���ڰ� 0.0f�� ����
		}
	}

	bool IsDestroy() //IsDestroyValue Get
	{
		return IsDestroyValue;
	}

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

protected:

private:
	int Order = 0; // ����
	bool IsDestroyUpdate = false; 
	float DestroyTime = 0.0f;
	bool IsActiveValue = true;
	bool IsDestroyValue = false;

};

