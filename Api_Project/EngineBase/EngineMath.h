#pragma once

struct  float4
{
public:
	float X;
	float Y;
	float Z;
	float W;
};

using FVector = float4;

class EngineMath
{
public:
	// constrcuter destructer
	EngineMath(); // 디폴트 생성자
	~EngineMath(); // 디폴트 소멸자

	// delete Function
	EngineMath(const EngineMath& _Other) = delete; // 디폴트 복사 생성자
	EngineMath(EngineMath&& _Other) noexcept = delete; 
	EngineMath& operator=(const EngineMath& _Other) = delete; // 디폴트 대입 연산자
	EngineMath& operator=(EngineMath&& _Other) noexcept = delete;

protected:

private:
};

