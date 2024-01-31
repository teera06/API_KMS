#pragma once
#include <EngineCore\Actor.h>

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
	UImageRenderer* TitleRenderer = nullptr;
};

