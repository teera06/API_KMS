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
	EngineMath(); // ����Ʈ ������
	~EngineMath(); // ����Ʈ �Ҹ���

	// delete Function
	EngineMath(const EngineMath& _Other) = delete; // ����Ʈ ���� ������
	EngineMath(EngineMath&& _Other) noexcept = delete; 
	EngineMath& operator=(const EngineMath& _Other) = delete; // ����Ʈ ���� ������
	EngineMath& operator=(EngineMath&& _Other) noexcept = delete;

protected:

private:
};

