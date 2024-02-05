#include "Stage1_MAP.h"

AStage1_MAP::AStage1_MAP()
{
}

AStage1_MAP::~AStage1_MAP()
{
}

void AStage1_MAP::BeginPlay()
{
	AActor::BeginPlay();

	MapRenderer = CreateImageRenderer(-9); // �̹��� ���� ����
	MapRenderer->SetImage("Stage1map.bmp"); // �̹��� Set
	MapRenderer->SetTransColor({ 255,255, 255, 0 });
	MapRenderer->SetTransform({ {0,0}, windowScale }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 
	MapRenderer->SetImageCuttingTransform({ {0,0}, windowScale.Half2D()}); // ���۰� SetImageCuttingTransform �������� �׷���
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�
}

void AStage1_MAP::Tick(float _DeltaTime)
{
}
