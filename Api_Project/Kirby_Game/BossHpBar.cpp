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
	HpAddRenderer->SetImage("BossHp.png");
}

void ABossHpBar::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	SetActorLocation({ GetWorld()->GetCameraPos().iX() + 880, GetWorld()->GetCameraPos().iY() + 650 });
	if (MainPlayer->GetStageCheck() == 3)
	{
		int Hp = SubBoss->GetHp();
		
		if (Hp == 0)
		{
			Destroy();
		}
		else if (Hp < 20 && Hp>0) {
			HpAddRenderer->SetTransform({ {-50,0}, {100 * 162, 300} }); // 랜더의 위치 크기 80
		}
		else if (Hp < 40 && Hp >= 20)
		{
			HpAddRenderer->SetTransform({ {-50,0}, {2 * 132,300 } }); // 랜더의 위치 크기 60 
		}
		else if (Hp < 60 && Hp >= 40)
		{
			HpAddRenderer->SetTransform({ {-50,0}, {2 * 102, 300} }); // 랜더의 위치 크기 80
		}
		else if (Hp < 80 && Hp >= 60)
		{
			HpAddRenderer->SetTransform({ {-128,12}, {2 * 72, 350} }); // 랜더의 위치 크기 80
		}
		else if (Hp < 100 && Hp >= 80)
		{
			HpAddRenderer->SetTransform({ {-50,0}, {2 * 42, 350} }); // 랜더의 위치 크기 80
		}
		else
		{
			HpAddRenderer->SetTransform({ {-50,0}, {0, 64 * 5} }); // 랜더의 위치 크기 80
		}
	}
	else if (MainPlayer->GetStageCheck() == 4)
	{
		return;// 추후 추가
	}

}
