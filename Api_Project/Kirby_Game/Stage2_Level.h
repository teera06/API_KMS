#pragma once
#include <EngineCore\Level.h> // 상속
#include <EnginePlatform\EngineSound.h>

class Stage2_Level :public ULevel
{
public:
	// constrcuter destructer
	Stage2_Level(); // 디폴트 생성자
	~Stage2_Level(); // 디폴트 소멸자

	// delete Function
	Stage2_Level(const Stage2_Level& _Other) = delete; // 디폴트 복사 생성자
	Stage2_Level(Stage2_Level&& _Other) noexcept = delete; 
	Stage2_Level& operator=(const Stage2_Level& _Other) = delete; // 디폴트 대입 연산자
	Stage2_Level& operator=(Stage2_Level&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
};

