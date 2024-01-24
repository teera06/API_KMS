#pragma once
#include "EngineMath.h"

// 기능 : 오브젝트 (ex) 커비, 몬스터) 위치, 크기 설정
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
	// (1) 크기 -> Get, Set
	void SetScale(FVector _Value)
	{
		Scale = _Value;
	}
	FVector GetScale()
	{
		return Scale;
	}
	//-------------------------------------

	// (2) // 위치 -> Get, Set
	void SetPosition(FVector _Value)
	{
		Position = _Value;
	}
	FVector GetPosition()
	{
		return Position;
	}
	//----------------------------------------

	// float 위치 이동
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

	// float -> int 형변환 위치 이동 -> 실질적으로 사용할 것-> 이유 : 정수 사용을 선호
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
	FVector Scale; // 오브젝트 크기
	FVector Position; // 오브젝트 위치
};

