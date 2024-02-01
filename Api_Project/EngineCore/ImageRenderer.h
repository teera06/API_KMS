#pragma once
#include "SceneComponent.h"
#include <EnginePlatform\WindowImage.h>

// ���� ���� -> ��� ��� �ּ�ȭ
class UWindowImage;
// ���� :
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
	// �̹����� �����ϴ� ���Ҹ� �ϰ�
	void SetImage(std::string_view _Name); // �̹��� Set

	void SetTransform(const FTransform& _Value) // Actor �� �̹����� ��ġ, ũ�� ����
	{
		USceneComponent::SetTransform(_Value);
	}

	void SetImageCuttingTransform(const FTransform& _Value) // ���ۿ��� �׸��� �Լ� -> �̹��� �߶� ǥ��
	{
		ImageCuttingTransform = _Value;
	}

protected:
	void BeginPlay() override;

private:
	UWindowImage* Image; // Level1 WindowImage
	FTransform ImageCuttingTransform; // Level0 -> Transform
};

