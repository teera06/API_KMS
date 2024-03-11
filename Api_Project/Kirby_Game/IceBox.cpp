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
		Renderer->SetTransform({ {0,-40}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	}

	// �ݸ���
	{
		Collision = CreateCollision(ECollisionOrder::IceBox);
		Collision->SetTransform({ { 0,-35},{140,140} });
		Collision->SetColType(ECollisionType::Rect);
	}

	Renderer->CreateAnimation("IceBox", "item.png", 1, 1, true);
	Renderer->ChangeAnimation("IceBox");
}

void AIceBox::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	// �ݸ��� 
	
	GravityVector += GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime); // �߷��� ��� ��������.

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	std::vector<UCollision*> Result;
	if (ColorR == Color8Bit(255, 0, 0, 0) || true == Collision->CollisionCheck(ECollisionOrder::IceBox, Result)) // ColMapImage���� �������� ��ġ�ϴ� ���
	{
		GravityVector = FVector::Zero; // �߷��� ���� 0����
	}

	AddActorLocation(GravityVector);

	
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


