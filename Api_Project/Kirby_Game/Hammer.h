#pragma once
class Hammer
{
public:
	// constrcuter destructer
	Hammer(); // ����Ʈ ������
	~Hammer(); // ����Ʈ �Ҹ���

	// delete Function
	Hammer(const Hammer& _Other) = delete; // ����Ʈ ���� ������
	Hammer(Hammer&& _Other) noexcept = delete; 
	Hammer& operator=(const Hammer& _Other) = delete; // ����Ʈ ���� ������
	Hammer& operator=(Hammer&& _Other) noexcept = delete;

protected:

private:
};

