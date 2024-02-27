#include "ActorCommon.h"

UWindowImage* UActorCommon::ColMapImage = nullptr;
bool UActorCommon::EatState = false;
EAMode UActorCommon::KirbyMode = EAMode::Base; // Kirby ���
std::string UActorCommon::ModeName = "Base_"; // Kirby ��庰 �ִϸ��̼� �̸� ü����

UActorCommon::UActorCommon()
{
}

UActorCommon::~UActorCommon()
{
}

FVector UActorCommon::GetGravity(int _X, int _Y, float _DeltaTime)
{
	Color8Bit Color = UActorCommon::ColMapImage->GetColor(_X, _Y, Color8Bit::RedA);
	if (Color != Color8Bit(255, 0, 0, 0))
	{
		GravityValue = FVector::Down * _DeltaTime * Gravity;
	}
	else {
		GravityValue = FVector::Zero;
	}

	return GravityValue;
}


