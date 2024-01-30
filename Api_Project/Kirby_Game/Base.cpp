#include "Base.h"
#include <Windows.h>
#include <EngineCore\EngineCore.h>

ABase::ABase()
{
}

ABase::~ABase()
{
}

void ABase::Tick(float _DeltaTime)
{
	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform Trans = GetTransform();
	Rectangle(WindowDC, Trans.iLeft(), Trans.iTop(), Trans.iRight(), Trans.iBottom());
}

void ABase::BeginPlay()
{
	{
		UImageRenderer* Renderer = CreateImageRenderer(0);
		Renderer->SetPosition({ 0,0 });
		Renderer->SetScale({ 50, 50 });
	}
}
