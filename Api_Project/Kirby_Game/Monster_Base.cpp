#include "Monster_Base.h"

AMonster_Base::AMonster_Base()
{
}

AMonster_Base::~AMonster_Base()
{
}

void AMonster_Base::BeginPlay()
{
	AActor::BeginPlay();

	// �÷��̾� 100, 100 => Actor
	// ��ü? 100, 100 - 50 => Renderer
	// ��ü? 100, 100 + 50 => Renderer

	//{
		//BodyRenderer = CreateImageRenderer(0);
		//BodyRenderer->SetPosition({ 0, 30 });
		//BodyRenderer->SetScale({ 8, 80 });
	//}

	MonsterRenderer = CreateImageRenderer(RenderOrder::Monster); // �̹��� ���� ����
	MonsterRenderer->SetImage("Monster_Right.png"); // �̹��� Set
	MonsterRenderer->SetTransform({ {0,0}, {310, 310} }); // ������ ��ġ ũ�� 

	AniCreate();

	for (int i = 0; i < 10; i++)
	{
		MonsterRenderer->ChangeAnimation("Monster_RIght");
	}
	MonsterRenderer->ChangeAnimation("Monster_Left");
}

void AMonster_Base::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime));
}

void AMonster_Base::AniCreate()
{
	// �⺻ �ȴ� ���
	MonsterRenderer->CreateAnimation("Monster_Right", "Monster_Right.png", 0, 4, 0.15f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("Monster_Left", "Monster_Left.png", 0, 4, 0.15f, true); // �ȱ�
}
