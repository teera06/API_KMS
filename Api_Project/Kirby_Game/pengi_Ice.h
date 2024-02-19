#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"


class pengi_Ice : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	pengi_Ice(); // 디폴트 생성자
	~pengi_Ice(); // 디폴트 소멸자

	// delete Function
	pengi_Ice(const pengi_Ice& _Other) = delete; // 디폴트 복사 생성자
	pengi_Ice(pengi_Ice&& _Other) noexcept = delete; 
	pengi_Ice& operator=(const pengi_Ice& _Other) = delete; // 디폴트 대입 연산자
	pengi_Ice& operator=(pengi_Ice&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* PengiRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* PengiCollision = nullptr;

	void AniCreate();
};

