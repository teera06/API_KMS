#include "ActorCommon.h"

UWindowImage* ActorCommon::ColMapImage = nullptr;
ActorCommon::ActorCommon()
{
}

ActorCommon::~ActorCommon()
{
}

std::string ActorCommon::GetAnimationName(std::string_view _Name)
{
	std::string DirName = "";

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}

	CurAnimationName = _Name;

	return std::string(GetNamechange()) + std::string(_Name) + DirName;
}
