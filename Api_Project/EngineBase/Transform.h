#pragma once
#include "EngineMath.h"

// ��� : EngineMath�� �̿��� -> ���� ��ġ, ũ�� ����
class FTransform
{
public:
	// constrcuter destructer
	FTransform();
	~FTransform();

	// delete Function
	//FTransform(const FTransform& _Other) = delete;
	//FTransform(FTransform&& _Other) noexcept = delete;
	//FTransform& operator=(const FTransform& _Other) = delete;
	//FTransform& operator=(FTransform&& _Other) noexcept = delete;

public:
	void SetScale(FVector _Value) // ũ�� Set
	{
		Scale = _Value;
	}
	FVector GetScale() // ũ�� Get
	{
		return Scale;
	}
	void SetPosition(FVector _Value) // ��ġ Set
	{
		Position = _Value;
	}
	void AddPosition(FVector _Value) // ��ġ �̵�
	{
		Position += _Value;
	}
	FVector GetPosition() // ��ġ Get
	{
		return Position;
	}

	//--------------------------------
	float Left()
	{
		return Position.X - Scale.hX();
	}
	float Right()
	{
		return Position.X + Scale.hX();
	}
	float Top()
	{
		return Position.Y - Scale.hY();
	}
	float Bottom()
	{
		return Position.Y + Scale.hY();
	}

	//-------------------------------------
	int iLeft()
	{
		return static_cast<int>(Left());
	}
	int iRight()
	{
		return static_cast<int>(Right());
	}
	int iTop()
	{
		return static_cast<int>(Top());
	}
	int iBottom()
	{
		return static_cast<int>(Bottom());
	}

protected:

private:
	FVector Scale; // ũ��
	FVector Position; // ��ġ
};

