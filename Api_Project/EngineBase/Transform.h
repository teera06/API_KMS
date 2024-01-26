#pragma once
#include "EngineMath.h"

// 기능 : EngineMath를 이용한 -> 최종 위치, 크기 설정
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
	void SetScale(FVector _Value) // 크기 Set
	{
		Scale = _Value;
	}
	FVector GetScale() // 크기 Get
	{
		return Scale;
	}
	void SetPosition(FVector _Value) // 위치 Set
	{
		Position = _Value;
	}
	void AddPosition(FVector _Value) // 위치 이동
	{
		Position += _Value;
	}
	FVector GetPosition() // 위치 Get
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
	FVector Scale; // 크기
	FVector Position; // 위치
};

