#include "Box.h"

ABox::ABox()
{
}

ABox::~ABox()
{
}

void ABox::BeginPlay()
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
		CollisionTop = CreateCollision(ECollisionOrder::BoxTop);
		CollisionTop->SetTransform({ { 0,-100},{100,20} });
		CollisionTop->SetColType(ECollisionType::Rect);

		CollisionBody = CreateCollision(ECollisionOrder::Box);
		CollisionBody->SetTransform({ { 0,-35},{140,100} });
		CollisionBody->SetColType(ECollisionType::Rect);

		CollisionItem = CreateCollision(ECollisionOrder::Item);
		CollisionItem->SetTransform({ { 0,0},{50,50} });
		CollisionItem->SetColType(ECollisionType::Rect);

		CollisionItem->ActiveOff();
	}

	Renderer->CreateAnimation("Box", "item.png", 2, 2, true);
	Renderer->CreateAnimation("Item", "item.png", 0, 0, true);
	Renderer->ChangeAnimation("Box");
}

void ABox::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	// �ݸ��� 

	if (true == IsItem && true == IsDelete)
	{
		ItemDrop();
	}
	else if (false == IsItem && true == IsDelete)
	{
		Destroy();
	}

	if (true == CollisionItem->IsActive())
	{
		ItemCollisiongather();
	}

	Collisiongather(_DeltaTime);


	GroundUp();
}

void ABox::GroundUp()
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

void ABox::Collisiongather(float _DeltaTime)
{
	GravityVector += GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime); // �߷��� ��� ��������.

	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::RedA);
	std::vector<UCollision*> Result;
	if (ColorR == Color8Bit(255, 0, 0, 0) || true == CollisionBody->CollisionCheck(ECollisionOrder::IceBoxTop, Result, GravityVector)) // ColMapImage���� �������� ��ġ�ϴ� ���
	{
		GravityVector = FVector::Zero; // �߷��� ���� 0����
	}

	AddActorLocation(GravityVector);
}

void ABox::ItemCollisiongather()
{
	std::vector<UCollision*> Result;
	if (true == CollisionItem->CollisionCheck(ECollisionOrder::kirby, Result, GravityVector)) // ColMapImage���� �������� ��ġ�ϴ� ���
	{
		MainPlayer->SetHp(100);
		Destroy();
	}
}

void ABox::ItemDrop()
{
	scale = 2;
	Renderer->ChangeAnimation("Item");
	Renderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 

	CollisionTop->ActiveOff();
	CollisionBody->ActiveOff();
	CollisionItem->ActiveOn();
}
