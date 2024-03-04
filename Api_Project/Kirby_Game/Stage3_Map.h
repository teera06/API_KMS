#pragma once
#include <EngineCore/Actor.h> // ���
#include<EngineCore/EngineCore.h> // GEngine

class Stage3_Map : public AActor
{
public:
	// constrcuter destructer
	Stage3_Map(); // ����Ʈ ������
	~Stage3_Map(); // ����Ʈ �Ҹ���

	// delete Function
	Stage3_Map(const Stage3_Map& _Other) = delete; // ����Ʈ ���� ������
	Stage3_Map(Stage3_Map&& _Other) noexcept = delete; 
	Stage3_Map& operator=(const Stage3_Map& _Other) = delete; // ����Ʈ ���� ������
	Stage3_Map& operator=(Stage3_Map&& _Other) noexcept = delete;
	
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

