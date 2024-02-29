#pragma once
#include <EngineCore/Actor.h> // ���
#include<EngineCore/EngineCore.h> // GEngine

class AStage2_Map : public AActor
{
public:
	// constrcuter destructer
	AStage2_Map(); // ����Ʈ ������
	~AStage2_Map(); // ����Ʈ �Ҹ���

	// delete Function
	AStage2_Map(const AStage2_Map& _Other) = delete; // ����Ʈ ���� ������
	AStage2_Map(AStage2_Map&& _Other) noexcept = delete; 
	AStage2_Map& operator=(const AStage2_Map& _Other) = delete; // ����Ʈ ���� ������
	AStage2_Map& operator=(AStage2_Map&& _Other) noexcept = delete;

	void SetMapImage(std::string_view _MapImageName);
	void SetColMapImage(std::string_view _MapImageName);

	void SwitchDebug();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	FVector windowScale = GEngine->MainWindow.GetWindowScale(); // ������â ũ��

	UImageRenderer* MapRenderer = nullptr; // ������
	UImageRenderer* MapColRenderer = nullptr; // �ݸ��� -> �ȼ� �浹
};

