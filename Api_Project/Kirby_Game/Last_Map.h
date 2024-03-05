#pragma once
#include <EngineCore/Actor.h> // ���
#include<EngineCore/EngineCore.h> // GEngine

class ALast_Map : public AActor
{
public:
	// constrcuter destructer
	ALast_Map(); // ����Ʈ ������
	~ALast_Map(); // ����Ʈ �Ҹ���

	// delete Function
	ALast_Map(const ALast_Map& _Other) = delete; // ����Ʈ ���� ������
	ALast_Map(ALast_Map&& _Other) noexcept = delete; 
	ALast_Map& operator=(const ALast_Map& _Other) = delete; // ����Ʈ ���� ������
	ALast_Map& operator=(ALast_Map&& _Other) noexcept = delete;

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

