#include "Log.h"
#include <EnginePlatform\EngineInput.h> // ���콺 ���� ��ư ���� ��� ���� ü����
#include "ModeEnum.h"

ALog::ALog()
{
}

ALog::~ALog()
{
}

void ALog::BeginPlay()
{
	AActor::BeginPlay();

	LogRenderer = CreateImageRenderer(ERenderOrder::Log); // �̹��� ���� ����
	LogRenderer->SetImage("Log.png"); // �̹��� Set
	LogRenderer->SetTransform({ {0,0}, {windowScale} }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 

	//TitleRenderer->SetImageCuttingTransform({ {0,0}, {450,339} }); // ���۰� SetImageCuttingTransform �������� �׷���
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�
}

void ALog::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown(VK_LBUTTON))
	{
		Destroy(0.0f);
	}
}
