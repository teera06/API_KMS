#pragma once
#include <EngineCore\Actor.h>
#include<EngineCore/EngineCore.h>

class EndActor : public AActor
{
public:
	// constrcuter destructer
	EndActor(); // 디폴트 생성자
	~EndActor(); // 디폴트 소멸자

	// delete Function
	EndActor(const EndActor& _Other) = delete; // 디폴트 복사 생성자
	EndActor(EndActor&& _Other) noexcept = delete; 
	EndActor& operator=(const EndActor& _Other) = delete; // 디폴트 대입 연산자
	EndActor& operator=(EndActor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* EndRenderer = nullptr;
	FVector windowScale = GEngine->MainWindow.GetWindowScale();

};

