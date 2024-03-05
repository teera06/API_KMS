#include "Last_Map.h"

#include "ModeEnum.h" // Enum ������

#include "ActorCommon.h" // ActorCommon::ColMapImage = Image; -> �ȼ� �浹�� �� �̹��� ����

Last_Map::Last_Map()
{
}

Last_Map::~Last_Map()
{
}

void Last_Map::SetMapImage(std::string_view _MapImageName)
{
	MapRenderer->SetImage(_MapImageName); // �̹��� Set
	UWindowImage* Image = MapRenderer->GetImage(); // Set�� �̹��� ���� �ް�
	FVector ImageScale = Image->GetScale(); // �̹��� ũ�⸦ ����
	MapRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
	// �̹����� X�� Y�� ������ ��ġ�� �̹��� ũ�⸸ ũ�⸸ŭ ������
}

void Last_Map::SetColMapImage(std::string_view _MapImageName)
{
	MapColRenderer->SetImage(_MapImageName);
	UWindowImage* Image = MapColRenderer->GetImage();
	UActorCommon::ColMapImage = Image; // �ȼ� �浹�� �� ����
	FVector ImageScale = Image->GetScale();
	MapColRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void Last_Map::SwitchDebug()
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

void Last_Map::BeginPlay()
{
	AActor::BeginPlay();

	MapRenderer = CreateImageRenderer(ERenderOrder::Last_Map); // �̹��� ���� ����
	MapColRenderer = CreateImageRenderer(ERenderOrder::Last_Map); // �̹��� ���� ����
	MapRenderer->ActiveOff();
}

void Last_Map::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown('O'))
	{
		SwitchDebug();
	}
}
