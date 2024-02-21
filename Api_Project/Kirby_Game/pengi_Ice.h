#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"


class Apengi_Ice : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	Apengi_Ice(); // 디폴트 생성자
	~Apengi_Ice(); // 디폴트 소멸자

	// delete Function
	Apengi_Ice(const Apengi_Ice& _Other) = delete; // 디폴트 복사 생성자
	Apengi_Ice(Apengi_Ice&& _Other) noexcept = delete; 
	Apengi_Ice& operator=(const Apengi_Ice& _Other) = delete; // 디폴트 대입 연산자
	Apengi_Ice& operator=(Apengi_Ice&& _Other) noexcept = delete;
	void IceState();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* PengiRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* PengiCollision = nullptr;

	AKirby_Player* Player = AKirby_Player::GetMainPlayer();
	
	FVector Dir = FVector::Right;
	void AniCreate();
	void BaseMove(float _DeltaTime);
};

