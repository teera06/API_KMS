#pragma once
#include "EngineMath.h"

class FTransform
{
public:
	// constrcuter destructer
	FTransform(); // ����Ʈ ������
	~FTransform(); // ����Ʈ �Ҹ���

	// delete Function
	FTransform(const FTransform& _Other) = delete; // ����Ʈ ���� ������
	FTransform(FTransform&& _Other) noexcept = delete; 
	FTransform& operator=(const FTransform& _Other) = delete; // ����Ʈ ���� ������
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

