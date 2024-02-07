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
	MonsterRenderer->SetImage("kirby_Right.png"); // �̹��� Set
	MonsterRenderer->SetTransform({ {0,0}, {210, 210} }); // ������ ��ġ ũ�� 

}

void AMonster_Base::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime));
}
