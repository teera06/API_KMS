#pragma once
#include <EngineCore/Actor.h>
#include<EngineCore/EngineCore.h>

class AStage1_MAP : public AActor
{
public:

	FVector windowScale = GEngine->MainWindow.GetWindowScale();
	// constrcuter destructer
	AStage1_MAP(); // ����Ʈ ������
	~AStage1_MAP(); // ����Ʈ �Ҹ���

	// delete Function
	AStage1_MAP(const AStage1_MAP& _Other) = delete; // ����Ʈ ���� ������
	AStage1_MAP(AStage1_MAP&& _Other) noexcept = delete; 
	AStage1_MAP& operator=(const AStage1_MAP& _Other) = delete; // ����Ʈ ���� ������
	AStage1_MAP& operator=(AStage1_MAP&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* MapRenderer = nullptr;
};

