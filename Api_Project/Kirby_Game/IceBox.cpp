#include "IceBox.h"
#include "ActorCommon.h"

AIceBox::AIceBox()
{
}

AIceBox::~AIceBox()
{
}

void AIceBox::BeginPlay()
{
	AActor::BeginPlay();

	//scale = 5; // ��� ũ��
	// ������
	{
		Renderer = CreateImageRenderer(ERenderOrder::Object); // �̹��� ���� ����
		Renderer->SetImage("Hammer.png"); // �̹��� Set
		//Renderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	}

	// �ݸ���
	{
		Collision = CreateCollision(ECollisionOrder::Object);
		Collision->SetTransform({ { -10,20},{100,100} });
		Collision->SetColType(ECollisionType::Rect);
	}
}

void AIceBox::Tick(float _DeltaTime)
{

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


