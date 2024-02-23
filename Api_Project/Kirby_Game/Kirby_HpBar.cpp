#include "Kirby_HpBar.h"
#include <EngineCore/EngineCore.h>

AKirby_HpBar::AKirby_HpBar()
{
}

AKirby_HpBar::~AKirby_HpBar()
{
}



void AKirby_HpBar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	SetActorLocation({ GetWorld()->GetCameraPos().iX()+140, GetWorld()->GetCameraPos().iY()+660 });
}

void AKirby_HpBar::BeginPlay()
{
	AActor::BeginPlay();
	
	HpRenderer = CreateImageRenderer(ERenderOrder::HPBar); // 이미지 랜더 생성
	HpRenderer->SetImage("HpHUD.png"); // 이미지 Set
	HpRenderer->SetTransform({ {0,0}, {64 * 6, 64 * 4} }); // 랜더의 위치 크기 
	
}
