#pragma once
class BossHpBar
{
public:
	// constrcuter destructer
	BossHpBar(); // ����Ʈ ������
	~BossHpBar(); // ����Ʈ �Ҹ���

	// delete Function
	BossHpBar(const BossHpBar& _Other) = delete; // ����Ʈ ���� ������
	BossHpBar(BossHpBar&& _Other) noexcept = delete; 
	BossHpBar& operator=(const BossHpBar& _Other) = delete; // ����Ʈ ���� ������
	BossHpBar& operator=(BossHpBar&& _Other) noexcept = delete;

protected:

private:
};

