#pragma once
#include <EngineCore\Level.h>

class UStage1_Level:public ULevel
{
public:
	// constrcuter destructer
	UStage1_Level(); // ����Ʈ ������
	~UStage1_Level(); // ����Ʈ �Ҹ���

	// delete Function
	UStage1_Level(const UStage1_Level& _Other) = delete; // ����Ʈ ���� ������
	UStage1_Level(UStage1_Level&& _Other) noexcept = delete; 
	UStage1_Level& operator=(const UStage1_Level& _Other) = delete; // ����Ʈ ���� ������
	UStage1_Level& operator=(UStage1_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
private:
};
