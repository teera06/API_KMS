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

	HpRenderer = CreateImageRenderer(ERenderOrder::HPBar); // �̹��� ���� ����
	HpRenderer->SetImage("BossHUD.png"); // �̹��� Set
	HpRenderer->SetTransform({ {0,0}, {64 * 6, 64 * 5} }); // ������ ��ġ ũ�� 

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
			HpAddRenderer->SetTransform({ {-100,12}, {500, 350} }); // ������ ��ġ ũ�� 80
			Destroy();
		}else if(Hp ==80)
		{

			HpAddRenderer->SetTransform({ {-20,12}, {2 * 42, 350} }); // ������ ��ġ ũ�� 80
		}else if (Hp == 40)
		{

			HpAddRenderer->SetTransform({ {-40,12}, {200, 350} }); // ������ ��ġ ũ�� 80
		}
		else
		{
			HpAddRenderer->SetTransform({ {-20,12}, {0, 350} }); // ������ ��ġ ũ�� 80
		}
	}
	else if (MainPlayer->GetStageCheck() == 4)
	{
		int Hp = MainBoss->GetHp();

		if (Hp == 0)
		{
			HpAddRenderer->SetTransform({ {-100,12}, {500, 350} }); // ������ ��ġ ũ�� 80
			Destroy(0.1f);
		}
		else if (Hp == 80)
		{

			HpAddRenderer->SetTransform({ {-20,12}, {2 * 42, 350} }); // ������ ��ġ ũ�� 80
		}
		else if (Hp == 40)
		{

			HpAddRenderer->SetTransform({ {-40,12}, {200, 350} }); // ������ ��ġ ũ�� 80
		}
		else
		{
			HpAddRenderer->SetTransform({ {-20,12}, {0, 350} }); // ������ ��ġ ũ�� 80
		}
	
	}

}
