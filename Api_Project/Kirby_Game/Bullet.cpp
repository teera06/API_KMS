#include "Bullet.h"

ABullet::ABullet()
{
}

ABullet::~ABullet()
{
}

void ABullet::BeginPlay()
{

	AActor::BeginPlay();
	{
		bulletRenderer = CreateImageRenderer(ERenderOrder::Bullet); // �̹��� ���� ����
		bulletRenderer->SetImage("King_Right.png"); // �̹��� Set
		bulletRenderer->SetTransform({ {0,0}, {64 * 3, 64 * 3} }); // ������ ��ġ ũ�� 
		bulletRenderer -> SetActive(true, 0.1f);
	}
	{
		bulletCollision = CreateCollision(ECollisionOrder::MainBossAtt);
		bulletCollision->SetScale({ 100,70 });
		bulletCollision->SetColType(ECollisionType::CirCle);
		bulletCollision->SetActive(true, 0.1f);
	}

	AniCreate();
}

void ABullet::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
	SkillDir(_DeltaTime);
	Collisiongather(_DeltaTime);
}

void ABullet::AniCreate()
{
	bulletRenderer->CreateAnimation("Bullet_Right", "king_Right.png", 61, 66, 0.02f, false);
	bulletRenderer->CreateAnimation("Bullet_Left", "King_Left.png", 61, 66, 0.02f, false);
}

void ABullet::SkillDir(float _DeltaTime)
{
	if (GetDir().iX() == FVector::Left.iX()) // ���� ����
	{
		bulletRenderer->ChangeAnimation("Bullet_Left");
		AddActorLocation(GetDir() * Speed * _DeltaTime);
	}
	else // ������ ����
	{
		bulletRenderer->ChangeAnimation("Bullet_Right");
		AddActorLocation(GetDir() * Speed * _DeltaTime);
	}
}

void ABullet::Collisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == bulletCollision->CollisionCheck(ECollisionOrder::kirby, Result))
	{
		MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
		MainPlayer->Sethitstate(true); // �÷��̾� �浹 üũ
		MainPlayer->SetHitDir(GetDir());
		MainPlayer->GetKirbyCollision()->ActiveOff();
		MainPlayer->AddHP(-20);
		//MainPlayer->HitStart(); // hit ���� ��ŸƮ
		Destroy();
	}
	
	// �ȼ� �浹
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 20, Color8Bit::RedA);

	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		Destroy();
	}
}