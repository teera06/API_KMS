#pragma once
class SubBoss
{
public:
	// constrcuter destructer
	SubBoss(); // ����Ʈ ������
	~SubBoss(); // ����Ʈ �Ҹ���

	// delete Function
	SubBoss(const SubBoss& _Other) = delete; // ����Ʈ ���� ������
	SubBoss(SubBoss&& _Other) noexcept = delete; 
	SubBoss& operator=(const SubBoss& _Other) = delete; // ����Ʈ ���� ������
	SubBoss& operator=(SubBoss&& _Other) noexcept = delete;

protected:

private:
};

