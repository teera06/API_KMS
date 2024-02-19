
#pragma once
#include <EngineCore\Actor.h>
#include<EngineCore/EngineCore.h>

class ALog : public AActor
{
public:
	// constrcuter destructer
	ALog(); // 디폴트 생성자
	~ALog(); // 디폴트 소멸자

	// delete Function
	ALog(const ALog& _Other) = delete; // 디폴트 복사 생성자
	ALog(ALog&& _Other) noexcept = delete; 
	ALog& operator=(const ALog& _Other) = delete; // 디폴트 대입 연산자
	ALog& operator=(ALog&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* TitleRenderer = nullptr;
	FVector windowScale = GEngine->MainWindow.GetWindowScale();
};

