#pragma once
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



	static UWindowImage* ColMapImage;

protected:
	FVector GetGravity(int _X, int _Y,float _DeltaTime); // �߷� �κ� ���������� ���� �κ�

private:
	float Gravity = 500.0f;
	FVector GravityValue = FVector::Zero;
};

