#include "Kirby_HpBar.h"
#include <EngineCore/EngineCore.h>

AKirby_HpBar::AKirby_HpBar()
{
}

AKirby_HpBar::~AKirby_HpBar()
{
}



AKirby_HpBar* AKirby_HpBar::GetHPBar()
{
	return MainHPBar;
}

AKirby_HpBar* AKirby_HpBar::MainHPBar = nullptr;



void AKirby_HpBar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//AddActorLocation(FVector::Right*100.0f * _DeltaTime);
}

void AKirby_HpBar::BeginPlay()
{
	AActor::BeginPlay();
	{
		HpRenderer = CreateImageRenderer(ERenderOrder::HPBar); // 이미지 랜더 생성
		HpRenderer->SetImage("HpHUD.png"); // 이미지 Set
		HpRenderer->SetTransform({ {0,0}, {64 * 6, 64 * 4} }); // 랜더의 위치 크기 
	}
}
