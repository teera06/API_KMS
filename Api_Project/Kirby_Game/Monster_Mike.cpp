#include "Monster_Mike.h"

Monster_Mike::Monster_Mike()
{
}

Monster_Mike::~Monster_Mike()
{
}

void Monster_Mike::IceState()
{
	scale = 2;
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	IsIce = true;
}

void Monster_Mike::BeginPlay()
{
	AActor::BeginPlay();

	scale = 3; // ��� ũ��
	// ������
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		MonsterRenderer->SetImage("Dee_Right.png"); // �̹��� Set
		MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	}

	// �ݸ���
	{
		MonsterCollision = CreateCollision(ECollisionOrder::Monster);
		MonsterCollision->SetScale({ 60, 60 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	// �ִϸ��̼� �����
	AniCreate();

	MonsterRenderer->ChangeAnimation("Move_Left");

}

void Monster_Mike::Tick(float _DeltaTime)
{
}

void Monster_Mike::MoveUpdate(float _DeltaTime)
{
}

void Monster_Mike::BaseMove(float _DeltaTime)
{
}

void Monster_Mike::AniCreate()
{
}

void Monster_Mike::IceToMonster(float _DeltaTime)
{
}

void Monster_Mike::Collisiongather(float _DeltaTime)
{
}

void Monster_Mike::CalDir()
{
}

void Monster_Mike::CalResult(float _DeltaTime)
{
}

void Monster_Mike::GroundUp()
{
}
