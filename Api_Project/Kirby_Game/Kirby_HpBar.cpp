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
		HpAddRenderer->SetTransform({ {36,15}, {2 * 192, 64 * 5} }); // 랜더의 위치 크기 
	}
	else if(Hp<20 && Hp>0){
		HpAddRenderer->SetTransform({ {50,15}, {2 * 162, 64 * 5} }); // 랜더의 위치 크기 80
	}
	else if (Hp < 40 && Hp >= 20)
	{
		HpAddRenderer->SetTransform({ {64,15}, {2 * 132, 64 * 5} }); // 랜더의 위치 크기 60 
	}
	else if (Hp == 40)
	{
		HpAddRenderer->SetTransform({ {70,15}, {2 * 118, 64 * 5} }); // 랜더의 위치 크기 80
	}
	else if (Hp== 50)
	{
		HpAddRenderer->SetTransform({ {79,15}, {2 * 98, 64 * 5} }); // 랜더의 위치 크기 80
	}
	else if (Hp == 60)
	{
		HpAddRenderer->SetTransform({ {86,15}, {2 * 82, 64 * 5} }); // 랜더의 위치 크기 80
	}
	else if (Hp ==70)
	{
		HpAddRenderer->SetTransform({ {95,15}, {2 * 62, 64 * 5} }); // 랜더의 위치 크기 80
	}
	else if (Hp==80)
	{
		HpAddRenderer->SetTransform({ {104,15}, {2 * 42, 64 * 5} }); // 랜더의 위치 크기 80
	}
	else if (Hp==90)
	{
		HpAddRenderer->SetTransform({ {112,15}, {2 * 22, 64 * 5} }); // 랜더의 위치 크기 80
	}
	else if(Hp==100)
	{
		HpAddRenderer->SetTransform({ {0,15}, {0, 64 * 5} }); // 랜더의 위치 크기 80
	}

	//else {
		//HpAddRenderer->SetTransform({ {0,15}, {64 * 0, 64 * 5} }); // 랜더의 위치 크기 
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
	
	HpRenderer = CreateImageRenderer(ERenderOrder::HPBar); // 이미지 랜더 생성
	HpRenderer->SetImage("HpHUD.png"); // 이미지 Set
	HpRenderer->SetTransform({ {0,0}, {64 * 6, 64 * 5} }); // 랜더의 위치 크기 

	HpAddRenderer = CreateImageRenderer(ERenderOrder::HPgauge);
	HpAddRenderer->SetImage("GaugeHUD.png");

	StateRenderer= CreateImageRenderer(ERenderOrder::State);
	StateRenderer->SetImage("changeHUD.png"); // 이미지 Set
	StateRenderer->SetTransform({ {-90,0}, {64 * 5, 64 * 5} }); // 랜더의 위치 크기 

	

	StateRenderer->CreateAnimation("Base_", "changeHUD.png", 0, 0,true); // 오른쪽 서 있기
	StateRenderer->CreateAnimation("Fire_", "changeHUD.png", 1, 1, true);
	StateRenderer->CreateAnimation("Ice_", "changeHUD.png", 2, 2, true);
	StateRenderer->CreateAnimation("Hammer_", "changeHUD.png", 3, 3, true);
	StateRenderer->CreateAnimation("Sir_", "changeHUD.png", 4, 4, true);
	StateRenderer->CreateAnimation("Mike_", "changeHUD.png", 5, 5, true);
}
