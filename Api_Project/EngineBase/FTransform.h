#pragma once
#include "EngineMath.h"

class FTransform
{
public:
	// constrcuter destructer
	FTransform(); // 디폴트 생성자
	~FTransform(); // 디폴트 소멸자

	// delete Function
	FTransform(const FTransform& _Other) = delete; // 디폴트 복사 생성자
	FTransform(FTransform&& _Other) noexcept = delete; 
	FTransform& operator=(const FTransform& _Other) = delete; // 디폴트 대입 연산자
	FTransform& operator=(FTransform&& _Other) noexcept = delete;
public:
	void  SetScale(FVector _Vector)
	{
		Scale = _Vector;
	}
	FVector GetScale()
	{
		return Scale;
	}

	void SetPosition(FVector _Vector)
	{
		Position = _Vector;
	}

	FVector GetPosition()
	{
		return Position;
	}
protected:

private:
	FVector Scale;
	FVector Position;
};

