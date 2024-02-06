#pragma once
#include <string>
#include <string_view>
#include "ModeEnum.h"
#include <EngineCore\ImageRenderer.h>

class ActorCommon
{
public:
	// constrcuter destructer
	ActorCommon(); // ����Ʈ ������
	~ActorCommon(); // ����Ʈ �Ҹ���

	// delete Function
	ActorCommon(const ActorCommon& _Other) = delete; // ����Ʈ ���� ������
	ActorCommon(ActorCommon&& _Other) noexcept = delete; 
	ActorCommon& operator=(const ActorCommon& _Other) = delete; // ����Ʈ ���� ������
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
	std::string Namechange = "Base_"; // �ִϸ��̼� �̸� �������ֱ�
};

