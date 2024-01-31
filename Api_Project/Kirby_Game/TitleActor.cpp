#include "TitleActor.h"
#include <EnginePlatform\EngineInput.h> // ���콺 ���� ��ư ���� ��� ���� ü����
#include <EngineCore/EngineCore.h> // Level change�� ���

ATitleActor::ATitleActor()
{
}

ATitleActor::~ATitleActor()
{
}

void ATitleActor::BeginPlay()
{
	AActor::BeginPlay();
	SetActorLocation({ 500, 500 }); // Actor�� ��ġ -> ����
	//SetActorScale({ 100, 100 }); // Acotor ũ��� ��� ���� 

	//{
		//BodyRenderer = CreateImageRenderer(0);
		//BodyRenderer->SetPosition({ 0, 30 });
		//BodyRenderer->SetScale({ 8, 80 });
	//}
	TitleRenderer = CreateImageRenderer(0);
	TitleRenderer->SetImage("test.png"); 
	//SetActorLocation({ 500, 500 }); // Actor�� ��ġ -> ����
	// Actor������ ��ġ�� ũ��, �̹���
	TitleRenderer->SetPosition({ 100, 100 });
	//TitleRenderer->SetTransform({ {0,0}, {500, 500} });
	//TitleRenderer->SetImageCuttingTransform({ {0,0}, {300, 300} });
	TitleRenderer->SetScale({ 100,100 });
	
		
	

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
