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
	//HpAddRenderer->SetSortType(EImageSortType::Left);
	HpAddRenderer->SetImage("BossHp.png");
}

void ABossHpBar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	

	SetActorLocation({ GetWorld()->GetCameraPos().iX() + 880, GetWorld()->GetCameraPos().iY() + 650 });


	if (MainPlayer->GetStageCheck() == 3 && false==IsHpZero)
	{
		if (SubBoss->GetHp() <= 0)
		{
			HpAddRenderer->SetTransform({ {-1,12}, {2*194, 350} }); // 랜더의 위치 크기 80
			IsHpZero = true;
			Destroy(1.0f);
		}
		else if (SubBoss->GetHp() == 40)
		{
			HpAddRenderer->SetTransform({ {34,12}, {2 * 118, 350} }); // 랜더의 위치 크기 80
		}
		else if (SubBoss->GetHp() == 80)
		{
			HpAddRenderer->SetTransform({ {68,12}, {2 * 42, 350} }); // 랜더의 위치 크기 80
		}
		else if(SubBoss->GetHp() == 100)
		{
			HpAddRenderer->SetTransform({ {-20,12}, {0, 350} }); // 랜더의 위치 크기 80
		}
	}
	else if (MainPlayer->GetStageCheck() == 4 && false == IsHpZero)
	{
		int Hp = MainBoss->GetHp();

		if (MainBoss->GetHp() <= 0)
		{
			HpAddRenderer->SetTransform({ {-1,12}, {2 * 194, 350} }); // 랜더의 위치 크기 80
			IsHpZero = true;
			Destroy(1.0f);
		}
		else if (MainBoss->GetHp() == 40)
		{
			HpAddRenderer->SetTransform({ {34,12}, {2 * 118, 350} }); // 랜더의 위치 크기 80
		}
		else if (MainBoss->GetHp() == 80)
		{
			HpAddRenderer->SetTransform({ {68,12}, {2 * 42, 350} }); // 랜더의 위치 크기 80
		}
		else if (MainBoss->GetHp() == 100)
		{
			HpAddRenderer->SetTransform({ {-20,12}, {0, 350} }); // 랜더의 위치 크기 80
		}
	
	}

}
