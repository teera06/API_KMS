#pragma once
#include <EngineCore\Level.h> // ���
#include <EnginePlatform\EngineSound.h>

class Stage2_Level :public ULevel
{
public:
	// constrcuter destructer
	Stage2_Level(); // ����Ʈ ������
	~Stage2_Level(); // ����Ʈ �Ҹ���

	// delete Function
	Stage2_Level(const Stage2_Level& _Other) = delete; // ����Ʈ ���� ������
	Stage2_Level(Stage2_Level&& _Other) noexcept = delete; 
	Stage2_Level& operator=(const Stage2_Level& _Other) = delete; // ����Ʈ ���� ������
	Stage2_Level& operator=(Stage2_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
};

