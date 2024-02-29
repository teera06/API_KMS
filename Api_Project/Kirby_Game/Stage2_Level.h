#pragma once
#include <EngineCore\Level.h> // ���
#include <EnginePlatform\EngineSound.h>

class UStage2_Level :public ULevel
{
public:
	// constrcuter destructer
	UStage2_Level(); // ����Ʈ ������
	~UStage2_Level(); // ����Ʈ �Ҹ���

	// delete Function
	UStage2_Level(const UStage2_Level& _Other) = delete; // ����Ʈ ���� ������
	UStage2_Level(UStage2_Level&& _Other) noexcept = delete; 
	UStage2_Level& operator=(const UStage2_Level& _Other) = delete; // ����Ʈ ���� ������
	UStage2_Level& operator=(UStage2_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
};

