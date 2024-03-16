#pragma once
#include <EngineCore\EngineCore.h>

class UGame_Core : public UEngineCore // ���
{
public:
	
	// Ŭ���� ����Ʈ
	UGame_Core(); // ����Ʈ ������
	~UGame_Core(); // ����Ʈ �Ҹ���

	UGame_Core(const UGame_Core& _Other) = delete;
	UGame_Core(UGame_Core&& _Other) noexcept = delete;
	UGame_Core& operator=(const UGame_Core& _Other) = delete;
	UGame_Core& operator=(UGame_Core&& _Other) noexcept = delete;

protected:
	// �������̵� 
	void BeginPlay() override; // ����
	void Tick(float _DeltaTime) override; // ������Ʈ
	void End() override; // ����

private:

	// ������â ũ�� (X,Y)
	int windowX = 1000;
	int windowY = 700;

	// ������â ��ġ (X,Y)
	int positionX = 200;
	int positionY = 100;
};

