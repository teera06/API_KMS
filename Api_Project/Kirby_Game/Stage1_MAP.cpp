#include "Stage1_MAP.h"
#include "ModeEnum.h"
#include "ActorCommon.h"

AStage1_MAP::AStage1_MAP()
{
}

AStage1_MAP::~AStage1_MAP()
{
}

void AStage1_MAP::BeginPlay()
{
	AActor::BeginPlay();

	MapRenderer = CreateImageRenderer(RenderOrder::Stage1_Map); // �̹��� ���� ����
	MapColRenderer = CreateImageRenderer(RenderOrder::Stage1_Map); // �̹��� ���� ����
	MapColRenderer->SetActive(false);
	//MapRenderer->SetImage("Stage1map.bmp"); // �̹��� Set
	//MapRenderer->SetTransColor({ 255,255, 255, 0 });
	//MapRenderer->SetTransform({ {0,0}, windowScale }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 
	//MapRenderer->SetImageCuttingTransform({ {0,0}, {461,123} }); // ���۰� SetImageCuttingTransform �������� �׷���
	// GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform); -> ImageRenderer
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans); -> ���� �ڵ�
}

void AStage1_MAP::Tick(float _DeltaTime)
{
}

void AStage1_MAP::SetMapImage(std::string_view _MapImageName)
{
	MapRenderer->SetImage(_MapImageName);
	UWindowImage* Image = MapRenderer->GetImage();
	FVector ImageScale = Image->GetScale();
	MapRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
	
	
}

void AStage1_MAP::SetColMapImage(std::string_view _MapImageName)
{
	MapColRenderer->SetImage(_MapImageName);
	UWindowImage* Image = MapColRenderer->GetImage();
	ActorCommon::ColMapImage = Image;
	FVector ImageScale = Image->GetScale();
	MapColRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void AStage1_MAP::SwitchDebug()
{
	if (true == MapRenderer->IsActive())
	{
		MapRenderer->SetActive(false);
		MapColRenderer->SetActive(true);
	}
	else
	{
		MapRenderer->SetActive(true);
		MapColRenderer->SetActive(false);
	}
}
