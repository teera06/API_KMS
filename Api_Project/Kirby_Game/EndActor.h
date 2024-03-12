#pragma once
#include <EngineCore\Actor.h>
#include<EngineCore/EngineCore.h>

class AEndActor : public AActor
{
public:
	// constrcuter destructer
	AEndActor(); // 디폴트 생성자
	~AEndActor(); // 디폴트 소멸자

	// delete Function
	AEndActor(const AEndActor& _Other) = delete; // 디폴트 복사 생성자
	AEndActor(AEndActor&& _Other) noexcept = delete; 
	AEndActor& operator=(const AEndActor& _Other) = delete; // 디폴트 대입 연산자
	AEndActor& operator=(AEndActor&& _Other) noexcept = delete;

	UImageRenderer* Gettext1Renderer()
	{
		return text1Renderer;
	}

	UImageRenderer* Gettext2Renderer()
	{
		return text2Renderer;
	}

	UImageRenderer* GetKirbyRenderer()
	{
		return KirbyRenderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* EndRenderer = nullptr;
	UImageRenderer* KirbyRenderer = nullptr;
	UImageRenderer* text1Renderer = nullptr;
	UImageRenderer* text2Renderer = nullptr;
	FVector windowScale = GEngine->MainWindow.GetWindowScale();

};

