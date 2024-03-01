#pragma once
#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"

class AMonster_Sir : public AActor, public UActorCommon
{
public:
	// constrcuter destructer
	AMonster_Sir(); // 디폴트 생성자
	~AMonster_Sir(); // 디폴트 소멸자

	// delete Function
	AMonster_Sir(const AMonster_Sir& _Other) = delete; // 디폴트 복사 생성자
	AMonster_Sir(AMonster_Sir&& _Other) noexcept = delete; 
	AMonster_Sir& operator=(const AMonster_Sir& _Other) = delete; // 디폴트 대입 연산자
	AMonster_Sir& operator=(AMonster_Sir&& _Other) noexcept = delete;

protected:

private:
	void MoveUpdate(float _DeltaTime);
};

