#pragma once
class EndActor
{
public:
	// constrcuter destructer
	EndActor(); // ����Ʈ ������
	~EndActor(); // ����Ʈ �Ҹ���

	// delete Function
	EndActor(const EndActor& _Other) = delete; // ����Ʈ ���� ������
	EndActor(EndActor&& _Other) noexcept = delete; 
	EndActor& operator=(const EndActor& _Other) = delete; // ����Ʈ ���� ������
	EndActor& operator=(EndActor&& _Other) noexcept = delete;

protected:

private:
};

