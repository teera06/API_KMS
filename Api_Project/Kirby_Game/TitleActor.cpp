#include "TitleActor.h"
#include <EnginePlatform\EngineInput.h>
#include <EngineCore/EngineCore.h>

ATitleActor::ATitleActor()
{
}

ATitleActor::~ATitleActor()
{
}

void ATitleActor::BeginPlay()
{
	AActor::BeginPlay();
	SetActorLocation({ 500, 500 }); // Actor의 위치
	//SetActorScale({ 100, 100 }); // Acotor 크기는 상관 없음 

	//{
		//BodyRenderer = CreateImageRenderer(0);
		//BodyRenderer->SetPosition({ 0, 30 });
		//BodyRenderer->SetScale({ 8, 80 });
	//}

	{
		// Actor에서의 위치와 크기, 이미지
		TitleRenderer = CreateImageRenderer(0);
		TitleRenderer->SetPosition({ 0, 0 });
		TitleRenderer->SetImageToScale("test.png");
	}

}

void ATitleActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (true == EngineInput::IsDown(VK_LBUTTON))
	{
		GEngine->ChangeLevel("Stage1_Level");
		Destroy(0.0f);
	}
}
