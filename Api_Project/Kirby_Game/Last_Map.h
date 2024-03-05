#pragma once
#include <EngineCore/Actor.h> // 상속
#include<EngineCore/EngineCore.h> // GEngine

class Last_Map : public AActor
{
public:
	// constrcuter destructer
	Last_Map(); // 디폴트 생성자
	~Last_Map(); // 디폴트 소멸자

	// delete Function
	Last_Map(const Last_Map& _Other) = delete; // 디폴트 복사 생성자
	Last_Map(Last_Map&& _Other) noexcept = delete; 
	Last_Map& operator=(const Last_Map& _Other) = delete; // 디폴트 대입 연산자
	Last_Map& operator=(Last_Map&& _Other) noexcept = delete;

	void SetMapImage(std::string_view _MapImageName);
	void SetColMapImage(std::string_view _MapImageName);

	void SwitchDebug();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	FVector windowScale = GEngine->MainWindow.GetWindowScale(); // 윈도우창 크기

	UImageRenderer* MapRenderer = nullptr; // 렌더링
	UImageRenderer* MapColRenderer = nullptr; // 콜리전 -> 픽셀 충돌
};

