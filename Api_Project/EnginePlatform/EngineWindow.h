#pragma once
class EngineWindow
{
public:
	// constrcuter destructer
	EngineWindow(); // ����Ʈ ������
	~EngineWindow(); // ����Ʈ �Ҹ���

	// delete Function
	EngineWindow(const EngineWindow& _Other) = delete; // ����Ʈ ���� ������
	EngineWindow(EngineWindow&& _Other) noexcept = delete; 
	EngineWindow& operator=(const EngineWindow& _Other) = delete; // ����Ʈ ���� ������
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

protected:

private:
};

