#pragma once
class EngineSound
{
public:
	// constrcuter destructer
	EngineSound(); // ����Ʈ ������
	~EngineSound(); // ����Ʈ �Ҹ���

	// delete Function
	EngineSound(const EngineSound& _Other) = delete; // ����Ʈ ���� ������
	EngineSound(EngineSound&& _Other) noexcept = delete; 
	EngineSound& operator=(const EngineSound& _Other) = delete; // ����Ʈ ���� ������
	EngineSound& operator=(EngineSound&& _Other) noexcept = delete;

protected:

private:
};

