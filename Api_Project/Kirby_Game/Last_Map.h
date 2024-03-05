#pragma once
#include <EngineCore/Actor.h> // ���
#include<EngineCore/EngineCore.h> // GEngine

class Last_Map : public AActor
{
public:
	// constrcuter destructer
	Last_Map(); // ����Ʈ ������
	~Last_Map(); // ����Ʈ �Ҹ���

	// delete Function
	Last_Map(const Last_Map& _Other) = delete; // ����Ʈ ���� ������
	Last_Map(Last_Map&& _Other) noexcept = delete; 
	Last_Map& operator=(const Last_Map& _Other) = delete; // ����Ʈ ���� ������
	Last_Map& operator=(Last_Map&& _Other) noexcept = delete;

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

