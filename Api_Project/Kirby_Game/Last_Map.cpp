#include "Last_Map.h"

#include "ModeEnum.h" // Enum 모음집

#include "ActorCommon.h" // ActorCommon::ColMapImage = Image; -> 픽셀 충돌할 맵 이미지 설정

ALast_Map::ALast_Map()
{
}

ALast_Map::~ALast_Map()
{
}

void ALast_Map::SetMapImage(std::string_view _MapImageName)
{
	MapRenderer->SetImage(_MapImageName); // 이미지 Set
	UWindowImage* Image = MapRenderer->GetImage(); // Set한 이미지 값을 받고
	FVector ImageScale = Image->GetScale(); // 이미지 크기를 저장
	MapRenderer->SetTransform({ ImageScale.Half2D(), {ImageScale.iX(),ImageScale.iY()+200}});
	// 이미지의 X축 Y축 절반의 위치에 이미지 크기만 크기만큼 랜더링
}

void ALast_Map::SetColMapImage(std::string_view _MapImageName)
{
	MapColRenderer->SetImage(_MapImageName);
	UWindowImage* Image = MapColRenderer->GetImage();
	UActorCommon::ColMapImage = Image; // 픽셀 충돌할 맵 설정
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

	MapRenderer = CreateImageRenderer(ERenderOrder::Last_Map); // 이미지 랜더 생성
	MapColRenderer = CreateImageRenderer(ERenderOrder::Last_Map); // 이미지 랜더 생성
	MapRenderer->ActiveOff();

	
	//EventRenderer->SetImage("test.png");
	EventRenderer1 = CreateImageRenderer(ERenderOrder::Last_Map);
	
	EventRenderer1->SetTransform({ {600,300}, {1200,800} });
	EventRenderer1->CreateAnimation("EndingMap1", "EndingMap.png", 0, 6, 1.0f, false); // 걷기
	EventRenderer1->ActiveOff();

	EventRenderer2 = CreateImageRenderer(ERenderOrder::EventMap);

	EventRenderer2->SetTransform({ {600,300}, {1200,800} });
	EventRenderer2->CreateAnimation("EndingMap2", "EndingMap.png", 4, 6, 1.0f, false); // 걷기
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
