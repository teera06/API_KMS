#include "ActorCommon.h"

UWindowImage* ActorCommon::ColMapImage = nullptr;
bool ActorCommon::EatState = false;
EAMode ActorCommon::KirbyMode = EAMode::Base; // Kirby 모드
std::string ActorCommon::ModeName = "Base_"; // Kirby 모드별 애니메이션 이름 체인지

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

