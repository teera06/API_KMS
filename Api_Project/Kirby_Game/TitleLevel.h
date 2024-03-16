#pragma once

// Level1
#include <EnginePlatform\EngineSound.h>
// Level2
#include <EngineCore/EngineCore.h> // GEngine -> ������ â ũ�� Ȯ��
#include <EngineCore/Level.h> // ���� ���

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
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel)override; // ������ ������ ��
	void LevelEnd(ULevel* _NextLevel) override; // ������ ����� ��
private:
	UEngineSoundPlayer BGMPlayer; // ���� ���
	FVector windowscale = GEngine->MainWindow.GetWindowScale(); // ������â ũ�� Get

	static bool LoadCheck; // �̹���, ���� ���� �ε� Ȯ�� �� bool
};

