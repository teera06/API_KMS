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
	
	TitleRenderer = CreateImageRenderer(0); // �̹��� ���� ����
	TitleRenderer->SetImage("test.png"); // �̹��� Set
	SetActorLocation({ 500, 500 }); // Level ���� Actor ��ġ ���� 
	TitleRenderer->SetTransform({ {0,0}, {500, 500} }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 
	TitleRenderer->SetImageCuttingTransform({ {0,0}, {649, 311} }); // ���۰� SetImageCuttingTransform �������� �׷���
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�
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
