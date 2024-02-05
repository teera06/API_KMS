#pragma once
#include <EngineCore/Actor.h>
#include<EngineCore/EngineCore.h>

class AStage1_MAP : public AActor
{
public:

	FVector windowScale = GEngine->MainWindow.GetWindowScale();
	// constrcuter destructer
	AStage1_MAP(); // 디폴트 생성자
	~AStage1_MAP(); // 디폴트 소멸자

	// delete Function
	AStage1_MAP(const AStage1_MAP& _Other) = delete; // 디폴트 복사 생성자
	AStage1_MAP(AStage1_MAP&& _Other) noexcept = delete; 
	AStage1_MAP& operator=(const AStage1_MAP& _Other) = delete; // 디폴트 대입 연산자
	AStage1_MAP& operator=(AStage1_MAP&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* MapRenderer = nullptr;
};

