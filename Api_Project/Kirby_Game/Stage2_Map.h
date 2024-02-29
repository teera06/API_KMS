#pragma once
#include <EngineCore/Actor.h> // ���
#include<EngineCore/EngineCore.h> // GEngine

class Stage2_Map : public AActor
{
public:
	// constrcuter destructer
	Stage2_Map(); // ����Ʈ ������
	~Stage2_Map(); // ����Ʈ �Ҹ���

	// delete Function
	Stage2_Map(const Stage2_Map& _Other) = delete; // ����Ʈ ���� ������
	Stage2_Map(Stage2_Map&& _Other) noexcept = delete; 
	Stage2_Map& operator=(const Stage2_Map& _Other) = delete; // ����Ʈ ���� ������
	Stage2_Map& operator=(Stage2_Map&& _Other) noexcept = delete;

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

