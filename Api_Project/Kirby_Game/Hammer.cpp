#include "Hammer.h"

AHammer::AHammer()
{
}

AHammer::~AHammer()
{
}

void AHammer::BeginPlay()
{
	AActor::BeginPlay();

	scale = 5; // ��� ũ��
	// ������
	{
		Renderer = CreateImageRenderer(ERenderOrder::Hammer); // �̹��� ���� ����
		Renderer->SetImage("Hammer.png"); // �̹��� Set
		Renderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	}

	// �ݸ���
	{
		Collision = CreateCollision(ECollisionOrder::Hammer);
		Collision->SetScale({ 60, 60 });
		Collision->SetColType(ECollisionType::Rect);
	}
}

void AHammer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY()+50, _DeltaTime)); // �߷� �ۿ�
	GroundUp();
}

void AHammer::GroundUp()
{
	while (true)
	{
		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 1, Color8Bit::RedA);
		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			AddActorLocation(FVector::Up * 2);
		}
		else
		{
			break;
		}
	}
}
