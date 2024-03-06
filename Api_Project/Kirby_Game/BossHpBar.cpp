#include "BossHpBar.h"

BossHpBar::BossHpBar()
{
}

BossHpBar::~BossHpBar()
{

}

void BossHpBar::BeginPlay()
{
	AActor::BeginPlay();

	HpRenderer = CreateImageRenderer(ERenderOrder::HPBar); // 이미지 랜더 생성
	HpRenderer->SetImage("HpHUD.png"); // 이미지 Set
	HpRenderer->SetTransform({ {0,0}, {64 * 6, 64 * 5} }); // 랜더의 위치 크기 

	HpAddRenderer = CreateImageRenderer(ERenderOrder::HPgauge);
	HpAddRenderer->SetImage("GaugeHUD.png");
}

void BossHpBar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
