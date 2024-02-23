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

	if (ModeName== "Base_")
	{
		StateRenderer->ChangeAnimation("Base_");
	}
	else if(ModeName=="Ice_")
	{
		StateRenderer->ChangeAnimation("Ice_");
	}
}

void AKirby_HpBar::BeginPlay()
{
	AActor::BeginPlay();
	
	HpRenderer = CreateImageRenderer(ERenderOrder::HPBar); // 이미지 랜더 생성
	HpRenderer->SetImage("HpHUD.png"); // 이미지 Set
	HpRenderer->SetTransform({ {0,0}, {64 * 6, 64 * 5} }); // 랜더의 위치 크기 

	StateRenderer= CreateImageRenderer(ERenderOrder::State);
	StateRenderer->SetImage("changeHUD.png"); // 이미지 Set
	StateRenderer->SetTransform({ {-90,0}, {64 * 5, 64 * 5} }); // 랜더의 위치 크기 

	StateRenderer->CreateAnimation("Base_", "changeHUD.png", 0, 0,true); // 오른쪽 서 있기
	StateRenderer->CreateAnimation("Fire_", "changeHUD.png", 1, 1, true);
	StateRenderer->CreateAnimation("Ice_", "changeHUD.png", 2, 2, true);
	StateRenderer->CreateAnimation("Hamer_", "changeHUD.png", 3, 3, true);
	StateRenderer->CreateAnimation("Sword_", "changeHUD.png", 4, 4, true);
	StateRenderer->CreateAnimation("Mike_", "changeHUD.png", 55, 5, true);

	//StateRenderer->ChangeAnimation("Base_");
}
