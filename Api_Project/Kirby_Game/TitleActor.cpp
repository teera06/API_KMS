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
	
	TitleRenderer = CreateImageRenderer(-10); // �̹��� ���� ����
	TitleRenderer->SetImage("Log.bmp"); // �̹��� Set
	TitleRenderer->SetTransColor({ 255,255,255,0 });
	TitleRenderer->SetTransform({ {0,0}, windowScale }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 
	TitleRenderer->SetImageCuttingTransform({ {0,0}, windowScale.Half2D()}); // ���۰� SetImageCuttingTransform �������� �׷���
	
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
