#include "SubBoss.h"

#include <EngineBase\EngineRandom.h>
#include <EngineCore/EngineCore.h> // GetWorld ��� -> Level ���� �̿�

#include "Monster_Mike.h"

ASubBoss* ASubBoss::MainSubBoss = nullptr;

ASubBoss* ASubBoss::GetMainSubBoss()
{
	return MainSubBoss;
}

ASubBoss::ASubBoss()
{
}

ASubBoss::~ASubBoss()
{
}

void ASubBoss::BeginPlay()
{
	AActor::BeginPlay();

	MainSubBoss = this; // �ٸ� Ŭ������ ����ϱ� ���� ������ �ִ´�.
	scale = 6;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		MonsterRenderer->SetImage("Tock_Right.png"); // �̹��� Set
		MonsterRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	}

	{
		AttRenderer = CreateImageRenderer(ERenderOrder::Sound); // �̹��� ���� ����
		AttRenderer->SetImage("Tock_Right.png"); // �̹��� Set
		AttRenderer->SetTransform({ {0,0}, {64 * 12, 64 * 12} }); // ������ ��ġ ũ�� 

		AttRenderer->ActiveOff();
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::SubBoss);
		MonsterCollision->SetTransform({ {0,-20}, {120, 120} });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	{
		AttCollision = CreateCollision(ECollisionOrder::SubBossAtt);
		AttCollision->SetTransform({ {0,-100}, {800, 500} });
		AttCollision->SetColType(ECollisionType::Rect);
		AttCollision->ActiveOff();
	}

	AniCreate();
	MonsterRenderer->ChangeAnimation("Move_Left");
}

void ASubBoss::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();

	if (Hp == 0) // ������
	{
		MonsterRenderer->ChangeAnimation("die_Right");

		if (true == MonsterRenderer->IsCurAnimationEnd())
		{
			Destroy(); // 0.3f �ڿ� ����
		}
	}
	else {
		if (false == Ishit) // Destroy(0.3f); -> ���Ǿ��� ��� move������Ʈ �Ǹ鼭 0.3f�� �Ȱ��� ���� (�ѹ��� �����ؾ���)
		{
			MoveUpdate(_DeltaTime);
		}
		else { 
			hitEvent();
		}
	}
}

void ASubBoss::CalDir(float _DeltaTime)
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 

	MovePos = FVector::Zero; // �÷��̾� �߰� �� �̵�

	if (MonsterDirNormal.iX() == -1 or MonsterDirNormal.iX() == 0) // ���� ����
	{
		MonsterRenderer->ChangeAnimation("Move_Left");
		WallX = -20;
	}
	else if (MonsterDirNormal.iX() == 1) { // ������ ����
		MonsterRenderer->ChangeAnimation("Move_Right");
		WallX = 20;
	}
	MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // ���Ͱ� �÷��̾��� Y�൵ �ν��� �� ������ FVector::Right �� ���� X�ุ �߰�
}

void ASubBoss::Att1(float _DeltaTime)
{
	AttRenderer->ActiveOn();
	AttCollision->ActiveOn();
	AttRenderer->ChangeAnimation("AttEffect");

	if (MonsterDirNormal.iX() == -1 || MonsterDirNormal.iX() == 0) // ���� ����
	{
		MonsterRenderer->ChangeAnimation("Att_Left");
	}
	else if (MonsterDirNormal.iX() == 1) { // ������ ����
		MonsterRenderer->ChangeAnimation("Att_Right");
	}
	AttCollisiongather(_DeltaTime);
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 2);
		AttCollision->ActiveOff();
		IsAtt = false;
		skillcooldowntime = 4.0f;
	}

	return;
}

void ASubBoss::Att2()
{
	if (MonsterDirNormal.iX() == -1) // ���� ����
	{
		MonsterRenderer->ChangeAnimation("Att2_Left");
	}
	else if (MonsterDirNormal.iX() == 1) { // ������ ����
		MonsterRenderer->ChangeAnimation("Att2_Right");
	}
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		RandomAtt = UEngineRandom::MainRandom.RandomInt(1, 2);
		if (MonsterDirNormal.iX() == -1) // ���� ����
		{
			GetWorld()->SpawnActor<AMonster_Mike>()->SetActorLocation({ GetActorLocation().iX()-100,200 });
		}
		else if (MonsterDirNormal.iX() == 1) { // ������ ����
			GetWorld()->SpawnActor<AMonster_Mike>()->SetActorLocation({ GetActorLocation().iX()+100,200 });
		}
		IsAtt = false;
		skillcooldowntime = 4.0f;
	}
	return;
}

void ASubBoss::AttCollisiongather(float _DeltaTime)
{
	// �ݸ��� 
	std::vector<UCollision*> Result;
	if (true == AttCollision->CollisionCheck(ECollisionOrder::kirby, Result)) // ���� ���� ���¿��� �÷��̾�� �浹
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		// ����ڵ�
		if (nullptr == Player)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}

	
		Player->Sethitstate(true); // �÷��̾� �浹 üũ
		Player->SetHitDir(MonsterDirNormal * FVector::Right);
		Player->GetKirbyRender()->SetAlpha(0.5f);
		Player->GetKirbyCollision()->ActiveOff();
		Player->AddHP(-20);
		Player->HitStart(); // hit ���� ��ŸƮ
			
		//IsDie = true; // ���� üũ
		
	}
}

void ASubBoss::Collisiongather(float _DeltaTime)
{
	// �ݸ��� 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result)) // ���� ���� ���¿��� �÷��̾�� �浹
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		// ����ڵ�
		if (nullptr == Player)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}


		Player->Sethitstate(true); // �÷��̾� �浹 üũ
		Player->SetHitDir(MonsterDirNormal * FVector::Right);
		Player->GetKirbyRender()->SetAlpha(0.5f);
		Player->GetKirbyCollision()->ActiveOff();
		Player->AddHP(-20);
		Player->HitStart(); // hit ���� ��ŸƮ

		//IsDie = true; // ���� üũ

	}
}

void ASubBoss::CalResult(float _DeltaTime)
{
	AddActorLocation(MovePos);
}

void ASubBoss::hitEvent()
{
	if (MonsterDirNormal.iX() == -1) // ���Ͱ� �÷��̾ ���ϴ� ������ �ݴ� �������� ���� �ۿ�
	{
		MonsterRenderer->ChangeAnimation("hit_Left"); // �״� �ִϸ��̼�
	}
	else {
		MonsterRenderer->ChangeAnimation("hit_Right"); // �״� �ִϸ��̼�
	}

	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		Ishit = false; 
		MonsterRenderer->SetAlpha(1.0f);
	}
}

void ASubBoss::GroundUp()
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

void ASubBoss::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // �߷� �ۿ�

	skillcooldowntime -= _DeltaTime;
	if (skillcooldowntime < 0.0f)
	{

		MovePos = FVector::Zero;

		if (RandomAtt == 1)
		{
			Att1(_DeltaTime);
		}
		
		if (RandomAtt == 2 or RandomAtt == 0)
		{
			Att2();
		}
	}
	else {
		AttRenderer->ActiveOff();
		CalDir(_DeltaTime);
		Collisiongather(_DeltaTime);
		CalResult(_DeltaTime);
	}
}

void ASubBoss::AniCreate()
{
	MonsterRenderer->CreateAnimation("Move_Right", "Tock_Right.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Move_Left", "Tock_Left.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Att_Right", "Tock_Right.png", 4, 6, 0.5f, false);
	MonsterRenderer->CreateAnimation("Att_Left", "Tock_Left.png", 4, 6, 0.5f, false);
	MonsterRenderer->CreateAnimation("Att2_Right", "Tock_Right.png", {4, 5, 10}, 0.5f, false);
	MonsterRenderer->CreateAnimation("Att2_Left", "Tock_Left.png", {4,5,10}, 0.5f, false);

	AttRenderer->CreateAnimation("AttEffect", "Tock_Right.png", { 16,17,18,19,20,14 },0.1f, true);

	MonsterRenderer->CreateAnimation("hit_Right", "Tock_Right.png", {10,1}, 0.5f, true); // ��Ʈ
	MonsterRenderer->CreateAnimation("hit_Left", "Tock_Left.png", {10,1}, 0.5f, true); // ��Ʈ 
	MonsterRenderer->CreateAnimation("die_Right", "Tock_Left.png", {11,13,12}, 0.5f, true); // ���� 
	MonsterRenderer->CreateAnimation("die_Left", "Tock_Right.png",{11, 13, 12}, 0.5f, true); // ���� 
}
