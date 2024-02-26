#include "TitleActor.h"
#include <EnginePlatform\EngineInput.h> // ���콺 ���� ��ư ���� ��� ���� ü����
#include "ModeEnum.h"

ATitleActor::ATitleActor()
{
}

ATitleActor::~ATitleActor()
{
}

void ATitleActor::BeginPlay()
{
	AActor::BeginPlay();

	TitleRenderer = CreateImageRenderer(ERenderOrder::TitleMap); // �̹��� ���� ����
	TitleRenderer->SetImage("Mapback.png"); // �̹��� Set
	TitleRenderer->SetTransform({ {0,0}, {1900,1100} }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 

	LogRenderer = CreateImageRenderer(ERenderOrder::Log); // �̹��� ���� ����
	LogRenderer->SetImage("Log.png"); // �̹��� Set
	LogRenderer->SetTransform({ { 0,0 }, windowScale });
	//TitleRenderer->SetImageCuttingTransform({ {0,0}, {450,339} }); // ���۰� SetImageCuttingTransform �������� �׷���
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�

	TitleRenderer->CreateAnimation("Mapback", "Mapback.png", 0, 4, 3.0f, true); // ������ �� �ֱ�
	TitleRenderer->ChangeAnimation("Mapback");
}

void ATitleActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		Destroy();
	}
}
