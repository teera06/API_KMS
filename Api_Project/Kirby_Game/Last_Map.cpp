#include "Last_Map.h"

#include "ModeEnum.h" // Enum ������

#include "ActorCommon.h" // ActorCommon::ColMapImage = Image; -> �ȼ� �浹�� �� �̹��� ����

ALast_Map::ALast_Map()
{
}

ALast_Map::~ALast_Map()
{
}

void ALast_Map::SetMapImage(std::string_view _MapImageName)
{
	MapRenderer->SetImage(_MapImageName); // �̹��� Set
	UWindowImage* Image = MapRenderer->GetImage(); // Set�� �̹��� ���� �ް�
	FVector ImageScale = Image->GetScale(); // �̹��� ũ�⸦ ����
	MapRenderer->SetTransform({ ImageScale.Half2D(), {ImageScale.iX(),ImageScale.iY()+200}});
	// �̹����� X�� Y�� ������ ��ġ�� �̹��� ũ�⸸ ũ�⸸ŭ ������
}

void ALast_Map::SetColMapImage(std::string_view _MapImageName)
{
	MapColRenderer->SetImage(_MapImageName);
	UWindowImage* Image = MapColRenderer->GetImage();
	UActorCommon::ColMapImage = Image; // �ȼ� �浹�� �� ����
	FVector ImageScale = Image->GetScale();
	MapColRenderer->SetTransform({ ImageScale.Half2D(), {ImageScale.iX(),ImageScale.iY() + 200} });
}

void ALast_Map::SwitchDebug()
{
	if (true == MapRenderer->IsActive())
	{
		MapRenderer->ActiveOff();
		MapColRenderer->ActiveOn();
	}
	else
	{
		MapRenderer->ActiveOn();
		MapColRenderer->ActiveOff();
	}
}

void ALast_Map::BeginPlay()
{
	AActor::BeginPlay();

	MapRenderer = CreateImageRenderer(ERenderOrder::Last_Map); // �̹��� ���� ����
	MapColRenderer = CreateImageRenderer(ERenderOrder::Last_Map); // �̹��� ���� ����
	MapRenderer->ActiveOff();

	
	//EventRenderer->SetImage("test.png");
	EventRenderer1 = CreateImageRenderer(ERenderOrder::Last_Map);
	
	EventRenderer1->SetTransform({ {600,300}, {1200,800} });
	EventRenderer1->CreateAnimation("EndingMap1", "EndingMap.png", 0, 6, 1.0f, false); // �ȱ�
	EventRenderer1->ActiveOff();

	EventRenderer2 = CreateImageRenderer(ERenderOrder::EventMap);

	EventRenderer2->SetTransform({ {600,300}, {1200,800} });
	EventRenderer2->CreateAnimation("EndingMap2", "EndingMap.png", 4, 6, 1.0f, false); // �ȱ�
	EventRenderer2->ActiveOff();
}

void ALast_Map::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown('O'))
	{
		SwitchDebug();
	}
}
