#pragma once
class EngineString
{
public:
	// constrcuter destructer
	EngineString(); // ����Ʈ ������
	~EngineString(); // ����Ʈ �Ҹ���

	// delete Function
	EngineString(const EngineString& _Other) = delete; // ����Ʈ ���� ������
	EngineString(EngineString&& _Other) noexcept = delete; 
	EngineString& operator=(const EngineString& _Other) = delete; // ����Ʈ ���� ������
	EngineString& operator=(EngineString&& _Other) noexcept = delete;

protected:

private:
};

