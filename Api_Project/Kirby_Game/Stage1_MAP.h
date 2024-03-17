#pragma once
#include <EngineCore/Actor.h> // 상속

// 맵은 우선 잠시 대기
class AStage1_MAP : public AActor
{
public:
	// constrcuter destructer
	AStage1_MAP(); // 디폴트 생성자
	~AStage1_MAP(); // 디폴트 소멸자

	// delete Function
	AStage1_MAP(const AStage1_MAP& _Other) = delete; // 디폴트 복사 생성자
	AStage1_MAP(AStage1_MAP&& _Other) noexcept = delete; 
	AStage1_MAP& operator=(const AStage1_MAP& _Other) = delete; // 디폴트 대입 연산자
	AStage1_MAP& operator=(AStage1_MAP&& _Other) noexcept = delete;

	void SetMapImage(std::string_view _MapImageName); // 맵 이미지 Set
	void SetColMapImage(std::string_view _MapImageName); // 픽셀 충돌 맵 이미지 Set

	void SwitchDebug();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* MapRenderer = nullptr; // 렌더링
	UImageRenderer* MapColRenderer = nullptr; // 콜리전 -> 픽셀 충돌
};

