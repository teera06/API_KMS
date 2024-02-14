#include "TitleActor.h"
#include <EnginePlatform\EngineInput.h> // ���콺 ���� ��ư ���� ��� ���� ü����
#include "ModeEnum.h"

ATitleActor::ATitleActor()
{
}

ATitleActor::~ATitleActor()
{
	Destroy(0.0f);
}

void ATitleActor::BeginPlay()
{
	AActor::BeginPlay();
	
	TitleRenderer = CreateImageRenderer(ERenderOrder::TitleMap); // �̹��� ���� ����
	TitleRenderer->SetImage("Log.bmp"); // �̹��� Set
	TitleRenderer->SetTransColor({ 255,255,255,0 });
	TitleRenderer->SetTransform({ {0,0}, windowScale }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 
	
	//TitleRenderer->SetImageCuttingTransform({ {0,0}, {450,339} }); // ���۰� SetImageCuttingTransform �������� �׷���
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�
}

void ATitleActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		Destroy(0.0f);
	}
}
