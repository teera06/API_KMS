#pragma once
class AMonster_Fire
{
public:
	// constrcuter destructer
	AMonster_Fire(); // ����Ʈ ������
	~AMonster_Fire(); // ����Ʈ �Ҹ���

	// delete Function
	AMonster_Fire(const AMonster_Fire& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Fire(AMonster_Fire&& _Other) noexcept = delete; 
	AMonster_Fire& operator=(const AMonster_Fire& _Other) = delete; // ����Ʈ ���� ������
	AMonster_Fire& operator=(AMonster_Fire&& _Other) noexcept = delete;

protected:

private:
};

