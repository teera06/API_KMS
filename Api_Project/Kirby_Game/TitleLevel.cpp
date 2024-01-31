#include "TitleLevel.h"
#include <EnginePlatform\EngineInput.h>
#include "Stage1_Level.h"
#include <EngineCore/EngineCore.h>
UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	if (true == EngineInput::IsPress(VK_LBUTTON))
	{
		GEngine->ChangeLevel("Stage1_Level");
	}// ¿ÞÂÊ °È±â
}
