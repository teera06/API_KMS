#pragma once
#include<EngineCore/EngineCore.h> // GEngine
#include <EngineCore\Actor.h> // 액터 상속

class ATitleActor : public AActor
{
public:

	// constrcuter destructer
	ATitleActor(); // 디폴트 생성자
	~ATitleActor(); // 디폴트 소멸자

	// delete Function
	ATitleActor(const ATitleActor& _Other) = delete; // 디폴트 복사 생성자
	ATitleActor(ATitleActor&& _Other) noexcept = delete; 
	ATitleActor& operator=(const ATitleActor& _Other) = delete; // 디폴트 대입 연산자
	ATitleActor& operator=(ATitleActor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	// 이미지 랜더
	UImageRenderer* TitleRenderer = nullptr;
	UImageRenderer* LogRenderer = nullptr;
	UImageRenderer* StartRenderer = nullptr;

	// 윈도우 크기
	FVector windowScale = GEngine->MainWindow.GetWindowScale();
};

