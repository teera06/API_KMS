#pragma once
#include <EngineCore\Actor.h>

class ActorControl : public AActor
{
public:
	// constrcuter destructer
	ActorControl(); // ����Ʈ ������
	~ActorControl(); // ����Ʈ �Ҹ���

	// delete Function
	ActorControl(const ActorControl& _Other) = delete; // ����Ʈ ���� ������
	ActorControl(ActorControl&& _Other) noexcept = delete; 
	ActorControl& operator=(const ActorControl& _Other) = delete; // ����Ʈ ���� ������
	ActorControl& operator=(ActorControl&& _Other) noexcept = delete;

protected:

private:
};

