#include "IceBox.h"

AIceBox::AIceBox()
{
}

AIceBox::~AIceBox()
{
}

void AIceBox::BeginPlay()
{
	AActor::BeginPlay();

	scale = 5; // ��� ũ��
	// ������
	{
		Renderer = CreateImageRenderer(ERenderOrder::Object); // �̹��� ���� ����
		Renderer->SetImage("item.png"); // �̹��� Set
		Renderer->SetTransform({ {0,40}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	}

	// �ݸ���
	{
		Collision = CreateCollision(ECollisionOrder::IceBox);
		Collision->SetTransform({ { 0,10},{130,130} });
		Collision->SetColType(ECollisionType::Rect);
	}

	Renderer->CreateAnimation("IceBox", "item.png", 1, 1, true);
	Renderer->ChangeAnimation("IceBox");
}

void AIceBox::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY() + 80, _DeltaTime)); // �߷� �ۿ�
	GroundUp();
}

void AIceBox::GroundUp()
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

