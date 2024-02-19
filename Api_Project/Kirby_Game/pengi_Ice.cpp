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
		PengiRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		PengiRenderer->SetImage("pengi_Right.png"); // �̹��� Set
		PengiRenderer->SetTransform({ {0,0}, {330, 330} }); // ������ ��ġ ũ�� 
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
	// �⺻ �ȴ� ���
	PengiRenderer->CreateAnimation("Pengi_Right", "Pengi_Right.png", 1, 4, 0.3f, true); // �ȱ�
	PengiRenderer->CreateAnimation("Pengi_Left", "Pengi_Left.png", 1, 4, 0.3f, true); // �ȱ�
}
