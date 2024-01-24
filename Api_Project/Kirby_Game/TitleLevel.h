#pragma once
#include <EngineCore/Level.h>

class UTitleLevel : public ULevel
{
public:
	// constrcuter destructer
	UTitleLevel(); // ����Ʈ ������
	~UTitleLevel(); // ����Ʈ �Ҹ���

	// delete Function
	UTitleLevel(const UTitleLevel& _Other) = delete; // ����Ʈ ���� ������
	UTitleLevel(UTitleLevel&& _Other) noexcept = delete; 
	UTitleLevel& operator=(const UTitleLevel& _Other) = delete; // ����Ʈ ���� ������
	UTitleLevel& operator=(UTitleLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
private:
};

