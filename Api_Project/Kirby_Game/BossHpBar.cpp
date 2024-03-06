#include "BossHpBar.h"

ABossHpBar::ABossHpBar()
{
}

ABossHpBar::~ABossHpBar()
{

}

void ABossHpBar::BeginPlay()
{
	AActor::BeginPlay();

	HpRenderer = CreateImageRenderer(ERenderOrder::HPBar); // 이미지 랜더 생성
	HpRenderer->SetImage("BossHUD.png"); // 이미지 Set
	HpRenderer->SetTransform({ {0,0}, {64 * 6, 64 * 5} }); // 랜더의 위치 크기 

	HpAddRenderer = CreateImageRenderer(ERenderOrder::HPgauge);
	HpAddRenderer->SetSortType(EImageSortType::Left);
	HpAddRenderer->SetImage("GaugeHUD.png");
}

void ABossHpBar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	int Hp = MainPlayer->GetHp();

	SetActorLocation({ GetWorld()->GetCameraPos().iX()+880, GetWorld()->GetCameraPos().iY() + 650 });
}
