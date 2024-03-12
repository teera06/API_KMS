#include "EndActor.h"
#include <EnginePlatform\EngineInput.h> // ���콺 ���� ��ư ���� ��� ���� ü����
#include "ModeEnum.h"
AEndActor::AEndActor()
{
}

AEndActor::~AEndActor()
{
}

void AEndActor::BeginPlay()
{
	AActor::BeginPlay();

	EndRenderer = CreateImageRenderer(ERenderOrder::TitleMap); // �̹��� ���� ����
	EndRenderer->SetImage("Mapback.png"); // �̹��� Set
	EndRenderer->SetTransform({ {0,0}, {1900,1100} }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 

	KirbyRenderer = CreateImageRenderer(ERenderOrder::Log); // �̹��� ���� ����
	KirbyRenderer->SetImage("Kirby_Right.png"); // �̹��� Set
	KirbyRenderer->SetTransform({ { 0,200 }, {64 * 3,64 * 3} });
	KirbyRenderer->CreateAnimation("Fly_Right", "kirby_Right.png", 58, 65, 0.1f, true);
	
	//TitleRenderer->SetImageCuttingTransform({ {0,0}, {450,339} }); // ���۰� SetImageCuttingTransform �������� �׷���
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�

	EndRenderer->CreateAnimation("Mapback", "Mapback.png", 0, 4, 3.0f, true); // ������ �� �ֱ�
	EndRenderer->ChangeAnimation("Mapback");
	KirbyRenderer->ChangeAnimation("Fly_Right");
}

void AEndActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
