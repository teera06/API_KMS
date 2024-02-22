#pragma once
#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class Sword_Monster : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	Sword_Monster(); // 디폴트 생성자
	~Sword_Monster(); // 디폴트 소멸자

	// delete Function
	Sword_Monster(const Sword_Monster& _Other) = delete; // 디폴트 복사 생성자
	Sword_Monster(Sword_Monster&& _Other) noexcept = delete; 
	Sword_Monster& operator=(const Sword_Monster& _Other) = delete; // 디폴트 대입 연산자
	Sword_Monster& operator=(Sword_Monster&& _Other) noexcept = delete;

protected:

private:
	void MoveUpdate(float _DeltaTime);
};

