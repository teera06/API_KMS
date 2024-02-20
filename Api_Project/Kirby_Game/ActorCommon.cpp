#include "ActorCommon.h"

UWindowImage* ActorCommon::ColMapImage = nullptr;
bool ActorCommon::EatState = false;
EAMode ActorCommon::KirbyMode = EAMode::Base; // Kirby ���
std::string ActorCommon::ModeName = "Base_"; // Kirby ��庰 �ִϸ��̼� �̸� ü����

ActorCommon::ActorCommon()
{
}

ActorCommon::~ActorCommon()
{
}



FVector ActorCommon::GetGravity(int _X, int _Y, float _DeltaTime)
{
	Color8Bit Color = ActorCommon::ColMapImage->GetColor(_X, _Y, Color8Bit::RedA);
	if (Color != Color8Bit(255, 0, 0, 0))
	{
		GravityValue = FVector::Down * _DeltaTime * Gravity;
	}
	else {
		GravityValue = FVector::Zero;
	}

	return GravityValue;
}

