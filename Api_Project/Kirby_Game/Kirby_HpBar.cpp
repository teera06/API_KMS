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
		HpRenderer = CreateImageRenderer(ERenderOrder::HPBar); // �̹��� ���� ����
		HpRenderer->SetImage("HpHUD.png"); // �̹��� Set
		HpRenderer->SetTransform({ {0,0}, {64 * 6, 64 * 4} }); // ������ ��ġ ũ�� 
	}
}
