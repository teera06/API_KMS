#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"
#include "ActorCommon.h"
#include <EngineCore/Level.h>


class AKirby_HpBar :public AActor, public ActorCommon // ActorCommon(중력)
{
public:
	// constrcuter destructer
	AKirby_HpBar(); // 디폴트 생성자
	~AKirby_HpBar(); // 디폴트 소멸자

	// delete Function
	AKirby_HpBar(const AKirby_HpBar& _Other) = delete; // 디폴트 복사 생성자
	AKirby_HpBar(AKirby_HpBar&& _Other) noexcept = delete;
	AKirby_HpBar& operator=(const AKirby_HpBar& _Other) = delete; // 디폴트 대입 연산자
	AKirby_HpBar& operator=(AKirby_HpBar&& _Other) noexcept = delete;



protected:
	void Tick(float _DeltaTime) override;
	void BeginPlay() override;
private:
	UImageRenderer* HpRenderer = nullptr; // 커비 랜더링 (이미지)
	UImageRenderer* StateRenderer = nullptr; // 커비 랜더링 (이미지)

	FVector Move = FVector::Zero;
};

