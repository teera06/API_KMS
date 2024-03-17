#pragma once
#include <EngineCore/Actor.h> // ���

// ���� �켱 ��� ���
class AStage1_MAP : public AActor
{
public:
	// constrcuter destructer
	AStage1_MAP(); // ����Ʈ ������
	~AStage1_MAP(); // ����Ʈ �Ҹ���

	// delete Function
	AStage1_MAP(const AStage1_MAP& _Other) = delete; // ����Ʈ ���� ������
	AStage1_MAP(AStage1_MAP&& _Other) noexcept = delete; 
	AStage1_MAP& operator=(const AStage1_MAP& _Other) = delete; // ����Ʈ ���� ������
	AStage1_MAP& operator=(AStage1_MAP&& _Other) noexcept = delete;

	void SetMapImage(std::string_view _MapImageName); // �� �̹��� Set
	void SetColMapImage(std::string_view _MapImageName); // �ȼ� �浹 �� �̹��� Set

	void SwitchDebug();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* MapRenderer = nullptr; // ������
	UImageRenderer* MapColRenderer = nullptr; // �ݸ��� -> �ȼ� �浹
};

