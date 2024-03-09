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

	int Hp = MainPlayer->GetHp();
	
	SetActorLocation({ GetWorld()->GetCameraPos().iX()+145, GetWorld()->GetCameraPos().iY()+650 });

	if (Hp == 0)
	{
		HpAddRenderer->SetTransform({ {36,15}, {2 * 192, 64 * 5} }); // ������ ��ġ ũ�� 
	}
	else if(Hp<20 && Hp>0){
		HpAddRenderer->SetTransform({ {50,15}, {2 * 162, 64 * 5} }); // ������ ��ġ ũ�� 80
	}
	else if (Hp < 40 && Hp >= 20)
	{
		HpAddRenderer->SetTransform({ {64,15}, {2 * 132, 64 * 5} }); // ������ ��ġ ũ�� 60 
	}
	else if (Hp == 40)
	{
		HpAddRenderer->SetTransform({ {70,15}, {2 * 118, 64 * 5} }); // ������ ��ġ ũ�� 80
	}
	else if (Hp== 50)
	{
		HpAddRenderer->SetTransform({ {79,15}, {2 * 98, 64 * 5} }); // ������ ��ġ ũ�� 80
	}
	else if (Hp == 60)
	{
		HpAddRenderer->SetTransform({ {86,15}, {2 * 82, 64 * 5} }); // ������ ��ġ ũ�� 80
	}
	else if (Hp ==70)
	{
		HpAddRenderer->SetTransform({ {95,15}, {2 * 62, 64 * 5} }); // ������ ��ġ ũ�� 80
	}
	else if (Hp==80)
	{
		HpAddRenderer->SetTransform({ {104,15}, {2 * 42, 64 * 5} }); // ������ ��ġ ũ�� 80
	}
	else if (Hp==90)
	{
		HpAddRenderer->SetTransform({ {112,15}, {2 * 22, 64 * 5} }); // ������ ��ġ ũ�� 80
	}
	else if(Hp==100)
	{
		HpAddRenderer->SetTransform({ {0,15}, {0, 64 * 5} }); // ������ ��ġ ũ�� 80
	}

	//else {
		//HpAddRenderer->SetTransform({ {0,15}, {64 * 0, 64 * 5} }); // ������ ��ġ ũ�� 
	//}

	if (std::string(GetModeName())== "Base_")
	{
		StateRenderer->ChangeAnimation("Base_");
	}
	else if(std::string(GetModeName()) =="Ice_")
	{
		StateRenderer->ChangeAnimation("Ice_");
	}
	else if (std::string(GetModeName()) == "Fire_")
	{
		StateRenderer->ChangeAnimation("Fire_");
	}
	else if (std::string(GetModeName()) == "Sir_")
	{
		StateRenderer->ChangeAnimation("Sir_");
		if (false == MainPlayer->GetSirUse())
		{
			StateRenderer->ActiveOn();
		}
		else {
			StateRenderer->ActiveOff();
		}
	}
	else if (std::string(GetModeName()) == "Mike_")
	{
		StateRenderer->ChangeAnimation("Mike_");
	}
	else if (std::string(GetModeName()) == "Hammer_")
	{
		StateRenderer->ChangeAnimation("Hammer_");
	}
}

void AKirby_HpBar::BeginPlay()
{
	AActor::BeginPlay();
	
	HpRenderer = CreateImageRenderer(ERenderOrder::HPBar); // �̹��� ���� ����
	HpRenderer->SetImage("HpHUD.png"); // �̹��� Set
	HpRenderer->SetTransform({ {0,0}, {64 * 6, 64 * 5} }); // ������ ��ġ ũ�� 

	HpAddRenderer = CreateImageRenderer(ERenderOrder::HPgauge);
	HpAddRenderer->SetImage("GaugeHUD.png");

	StateRenderer= CreateImageRenderer(ERenderOrder::State);
	StateRenderer->SetImage("changeHUD.png"); // �̹��� Set
	StateRenderer->SetTransform({ {-90,0}, {64 * 5, 64 * 5} }); // ������ ��ġ ũ�� 

	

	StateRenderer->CreateAnimation("Base_", "changeHUD.png", 0, 0,true); // ������ �� �ֱ�
	StateRenderer->CreateAnimation("Fire_", "changeHUD.png", 1, 1, true);
	StateRenderer->CreateAnimation("Ice_", "changeHUD.png", 2, 2, true);
	StateRenderer->CreateAnimation("Hammer_", "changeHUD.png", 3, 3, true);
	StateRenderer->CreateAnimation("Sir_", "changeHUD.png", 4, 4, true);
	StateRenderer->CreateAnimation("Mike_", "changeHUD.png", 5, 5, true);
}
