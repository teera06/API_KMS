#pragma once
#include <EngineCore/Actor.h>
#include "ModeEnum.h"
#include "ActorCommon.h"
#include <EngineCore/Level.h>


class Kirby_HpBar :public AActor, public ActorCommon // ActorCommon(중력)
{
public:
	// constrcuter destructer
	Kirby_HpBar(); // 디폴트 생성자
	~Kirby_HpBar(); // 디폴트 소멸자

	// delete Function
	Kirby_HpBar(const Kirby_HpBar& _Other) = delete; // 디폴트 복사 생성자
	Kirby_HpBar(Kirby_HpBar&& _Other) noexcept = delete; 
	Kirby_HpBar& operator=(const Kirby_HpBar& _Other) = delete; // 디폴트 대입 연산자
	Kirby_HpBar& operator=(Kirby_HpBar&& _Other) noexcept = delete;

protected:

private:
	UImageRenderer* HpRenderer = nullptr; // 커비 랜더링 (이미지)
};

