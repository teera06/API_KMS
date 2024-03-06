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

	HpRenderer = CreateImageRenderer(ERenderOrder::HPBar); // �̹��� ���� ����
	HpRenderer->SetImage("HpHUD.png"); // �̹��� Set
	HpRenderer->SetTransform({ {0,0}, {64 * 6, 64 * 5} }); // ������ ��ġ ũ�� 

	HpAddRenderer = CreateImageRenderer(ERenderOrder::HPgauge);
	HpAddRenderer->SetImage("GaugeHUD.png");
}

void BossHpBar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
