#pragma once
#include <EngineBase\EngineDebug.h>

// 설명 :
class UTickObject
{

public:
	// constrcuter destructer
	UTickObject();
	virtual ~UTickObject();// 제일 위의 부모클래스 -> 가상 소멸자로 만듬

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
		// 내가 켜져있고         죽지도 않았다면
		return IsActiveValue && IsDestroyValue == false;
	}


	virtual void Destroy(float _DestroyTime = 0.0f) // 인자값을 안넣어주면 0.0f로 들어옴
	{
		IsDestroyUpdate = true;
		DestroyTime = _DestroyTime;
		if (0.0f >= _DestroyTime) // 인자값으로 받은 _DestroyTime가 0.0f보다 작거나 같을 때 실행
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
		if (false == IsDestroyUpdate) // false일 경우 그냥 리턴
		{
			return;
		}

		// true인 경우
		DestroyTime -= _DeltaTime; // Destroy()에서 Set 한 DestroyTime에 _DeltaTime 빼줌
		if (0.0f >= DestroyTime) // DestroyTime이 0보다 작거나 같아지면 실행
		{
			Destroy(0.0f); // 인자값 0.0f로 고정
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
	int Order = 0; // 순서
	bool IsDestroyUpdate = false; 
	float DestroyTime = 0.0f;
	bool IsActiveValue = true;
	bool IsDestroyValue = false;

};

