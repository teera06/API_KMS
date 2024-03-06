#pragma once

#include <EngineCore\Actor.h>

#include "ActorCommon.h"

#include "Kirby_Player.h" // MainPlayer

class AMainBoss : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMainBoss(); // 디폴트 생성자
	~AMainBoss(); // 디폴트 소멸자

	// delete Function
	AMainBoss(const AMainBoss& _Other) = delete; // 디폴트 복사 생성자
	AMainBoss(AMainBoss&& _Other) noexcept = delete; 
	AMainBoss& operator=(const AMainBoss& _Other) = delete; // 디폴트 대입 연산자
	AMainBoss& operator=(AMainBoss&& _Other) noexcept = delete;

protected:

private:
};

