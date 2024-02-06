#pragma once
#include <string>
#include <string_view>
#include "ModeEnum.h"
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

	std::string_view GetNamechange()
	{
		return Namechange;
	}

	static UWindowImage* ColMapImage;

protected:
	
	std::string GetAnimationName(std::string_view _Name);
	std::string CurAnimationName = "None";
	ActorState State = ActorState::None;
	EActorDir DirState = EActorDir::Right;
private:
	std::string Namechange = "Base_"; // 애니메이션 이름 변경해주기
};

