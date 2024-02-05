#pragma once
#include <EngineCore\Level.h>
#include <EngineCore/EngineCore.h>

class UStage1_Level:public ULevel
{
public:
	// constrcuter destructer
	UStage1_Level(); // 디폴트 생성자
	~UStage1_Level(); // 디폴트 소멸자

	// delete Function
	UStage1_Level(const UStage1_Level& _Other) = delete; // 디폴트 복사 생성자
	UStage1_Level(UStage1_Level&& _Other) noexcept = delete; 
	UStage1_Level& operator=(const UStage1_Level& _Other) = delete; // 디폴트 대입 연산자
	UStage1_Level& operator=(UStage1_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	FVector windowScale = GEngine->MainWindow.GetWindowScale();
};

