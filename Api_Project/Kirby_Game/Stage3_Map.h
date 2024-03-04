#pragma once
#include <EngineCore/Actor.h> // ���
#include<EngineCore/EngineCore.h> // GEngine

class AStage3_Map : public AActor
{
public:
	// constrcuter destructer
	AStage3_Map(); // ����Ʈ ������
	~AStage3_Map(); // ����Ʈ �Ҹ���

	// delete Function
	AStage3_Map(const AStage3_Map& _Other) = delete; // ����Ʈ ���� ������
	AStage3_Map(AStage3_Map&& _Other) noexcept = delete; 
	AStage3_Map& operator=(const AStage3_Map& _Other) = delete; // ����Ʈ ���� ������
	AStage3_Map& operator=(AStage3_Map&& _Other) noexcept = delete;
	
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

