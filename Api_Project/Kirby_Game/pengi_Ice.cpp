#include "pengi_Ice.h"

Apengi_Ice::Apengi_Ice()
{
}

Apengi_Ice::~Apengi_Ice()
{
}

void Apengi_Ice::BeginPlay()
{
	AActor::BeginPlay();
	{
		PengiRenderer = CreateImageRenderer(ERenderOrder::Monster); // 이미지 랜더 생성
		PengiRenderer->SetImage("pengi_Right.png"); // 이미지 Set
		PengiRenderer->SetTransform({ {0,0}, {330, 330} }); // 랜더의 위치 크기 
	}

	AniCreate();
	PengiRenderer->ChangeAnimation("Pengi_Right");
}

void Apengi_Ice::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime));
}

void Apengi_Ice::AniCreate()
{
	// 기본 걷는 모션
	PengiRenderer->CreateAnimation("Pengi_Right", "Pengi_Right.png", 1, 4, 0.3f, true); // 걷기
	PengiRenderer->CreateAnimation("Pengi_Left", "Pengi_Left.png", 1, 4, 0.3f, true); // 걷기
}
