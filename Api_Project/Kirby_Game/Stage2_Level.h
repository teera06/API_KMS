#pragma once
#include <EngineCore\Level.h> // 상속
#include <EnginePlatform\EngineSound.h>

class UStage2_Level :public ULevel
{
public:
	// constrcuter destructer
	UStage2_Level(); // 디폴트 생성자
	~UStage2_Level(); // 디폴트 소멸자

	// delete Function
	UStage2_Level(const UStage2_Level& _Other) = delete; // 디폴트 복사 생성자
	UStage2_Level(UStage2_Level&& _Other) noexcept = delete; 
	UStage2_Level& operator=(const UStage2_Level& _Other) = delete; // 디폴트 대입 연산자
	UStage2_Level& operator=(UStage2_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
};

