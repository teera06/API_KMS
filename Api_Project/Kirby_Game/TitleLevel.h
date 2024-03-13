#pragma once

#include <EngineCore/EngineCore.h>
#include <EngineCore/Level.h>
#include <EnginePlatform\EngineSound.h>

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

	void LevelStart(ULevel* _PrevLevel)override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	UEngineSoundPlayer BGMPlayer;
	FVector windowscale = GEngine->MainWindow.GetWindowScale(); // ������â ũ�� Get

	static bool LoadCheck;
};

