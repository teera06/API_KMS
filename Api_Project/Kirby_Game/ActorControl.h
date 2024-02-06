#pragma once
#include <EngineCore\Actor.h>

class ActorControl : public AActor
{
public:
	// constrcuter destructer
	ActorControl(); // 디폴트 생성자
	~ActorControl(); // 디폴트 소멸자

	// delete Function
	ActorControl(const ActorControl& _Other) = delete; // 디폴트 복사 생성자
	ActorControl(ActorControl&& _Other) noexcept = delete; 
	ActorControl& operator=(const ActorControl& _Other) = delete; // 디폴트 대입 연산자
	ActorControl& operator=(ActorControl&& _Other) noexcept = delete;

protected:

private:
};

