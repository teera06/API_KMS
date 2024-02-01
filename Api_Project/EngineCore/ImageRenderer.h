#pragma once
#include "SceneComponent.h"
#include <EnginePlatform\WindowImage.h>

// 전방 선언 -> 헤더 사용 최소화
class UWindowImage;
// 설명 :
class UImageRenderer : public USceneComponent
{
public:
	// constrcuter destructer
	UImageRenderer();
	~UImageRenderer();

	// delete Function
	UImageRenderer(const UImageRenderer& _Other) = delete;
	UImageRenderer(UImageRenderer&& _Other) noexcept = delete;
	UImageRenderer& operator=(const UImageRenderer& _Other) = delete;
	UImageRenderer& operator=(UImageRenderer&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;
	void Render(float _DeltaTime);
	// 이미지를 세팅하는 역할만 하고
	void SetImage(std::string_view _Name); // 이미지 Set

	void SetTransform(const FTransform& _Value) // Actor 위 이미지의 위치, 크기 설정
	{
		USceneComponent::SetTransform(_Value);
	}

	void SetImageCuttingTransform(const FTransform& _Value) // 버퍼에서 그리는 함수 -> 이미지 잘라서 표현
	{
		ImageCuttingTransform = _Value;
	}

protected:
	void BeginPlay() override;

private:
	UWindowImage* Image; // Level1 WindowImage
	FTransform ImageCuttingTransform; // Level0 -> Transform
};

