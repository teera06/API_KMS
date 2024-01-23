#include "EngineCore.h"
#include <Windows.h>

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
}

// 한번만 실행
void EngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (true == EngineInit)
	{
		return;
	}

	EngineWindow::Init(_HINSTANCE);
	MainWindow.Open();

	EngineInit = true;
}

void EngineCore::EngineStart()
{

}

void EngineCore::EngineUpdate()
{

}

void EngineCore::EngineEnd()
{

}