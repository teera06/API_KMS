#pragma once
#include <EngineCore\ImageRenderer.h>

class ActorCommon
{
public:
	// constrcuter destructer
	ActorCommon(); // 디폴트 생성자
	~ActorCommon(); // 디폴트 소멸자

	// delete Function
	ActorCommon(const ActorCommon& _Other) = delete; // 디폴트 복사 생성자
	ActorCommon(ActorCommon&& _Other) noexcept = delete;
	ActorCommon& operator=(const ActorCommon& _Other) = delete; // 디폴트 대입 연산자
	ActorCommon& operator=(ActorCommon&& _Other) noexcept = delete;



	static UWindowImage* ColMapImage;

protected:
	FVector GetGravity(int _X, int _Y,float _DeltaTime); // 중력 부분 공통적으로 쓰일 부분

private:
	float Gravity = 500.0f;
	FVector GravityValue = FVector::Zero;
};

