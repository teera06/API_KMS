#include "SubBoss.h"

ASubBoss::ASubBoss()
{
}

ASubBoss::~ASubBoss()
{
}

void ASubBoss::BeginPlay()
{
	AActor::BeginPlay();

	scale = 6;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		MonsterRenderer->SetImage("Tock_Right.png"); // �̹��� Set
		MonsterRenderer->SetTransform({ {0,0}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::SubBoss);
		MonsterCollision->SetTransform({ {0,-20}, {120, 120} });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	{
		AttCollision = CreateCollision(ECollisionOrder::SubBossAtt);
		AttCollision->SetTransform({ {0,-20}, {200, 120} });
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
	if (false == IsDie) // Destroy(0.3f); -> ���Ǿ��� ��� move������Ʈ �Ǹ鼭 0.3f�� �Ȱ��� ���� (�ѹ��� �����ؾ���)
	{
		MoveUpdate(_DeltaTime);
	}
	else { // IsDIe�� true�̸� MoveUpdate�� ���� ������ �ȵ� -> Destroy(0.3f) �۵�
		//AddActorLocation(DiePos); // �����鼭 �̵�
	}
}

void ASubBoss::CalDir(float _DeltaTime)
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector AttXL = MonsterPos + FVector::Left * AttRange; // ���� ���� �÷��̾� �ν� �þ� X��
	FVector AttXR = MonsterPos + FVector::Right * AttRange; // ���� ������ �÷��̾� �ν� �þ� X��

	FVector PlayerX = PlayerPos * FVector::Right; // �÷��̾� ��ġ X��

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 

	MovePos = FVector::Zero; // �÷��̾� �߰� �� �̵�

	if (MonsterDirNormal.iX() == -1) // ���� ����
	{
		MonsterRenderer->ChangeAnimation("Move_Left");
		WallX = -20;
	}
	else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // ������ ����
		MonsterRenderer->ChangeAnimation("Move_Right");
		WallX = 20;
	}
	MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // ���Ͱ� �÷��̾��� Y�൵ �ν��� �� ������ FVector::Right �� ���� X�ุ �߰�

	// �÷��̾ ���� ����
	if (AttXL.iX() < PlayerX.iX() && AttXR.iX() > PlayerX.iX() && MainPlayer->GetActorLocation().iY() >= GetActorLocation().iY() - 30) // ���� �þ߿� ������ ��� X�� ���� ����, ������
	{
		IsAtt = true;
	}
}

void ASubBoss::Att()
{

}

void ASubBoss::Collisiongather(float _DeltaTime)
{

}

void ASubBoss::CalResult(float _DeltaTime)
{
	
	if (true == IsDie) // ������
	{
		Destroy(0.3f); // 0.3f �ڿ� ����
	}
	else {
		
		AddActorLocation(MovePos);
		
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
	if (true == IsAtt && skillcooldowntime < 0.0f)
	{
		MovePos = FVector::Zero;
		Att();
	}
	else {
		CalDir(_DeltaTime);
		Collisiongather(_DeltaTime);
		CalResult(_DeltaTime);
	}
}

void ASubBoss::AniCreate()
{
	MonsterRenderer->CreateAnimation("Move_Right", "Tock_Right.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Move_Left", "Tock_Left.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Att_Right", "Tock_Right.png", 4, 6, 0.15f, false);
	MonsterRenderer->CreateAnimation("Att_Left", "Tock_Left.png", 4, 6, 0.15f, false);

	MonsterRenderer->CreateAnimation("die_Right", "Tock_Left.png", 11, 13, 0.3f, true); // ���� 
	MonsterRenderer->CreateAnimation("die_Left", "Tock_Right.png",11, 13, 0.3f, true); // ���� 
	
	//MonsterRenderer->CreateAnimation("Effect", "Effects.png", 29, 30, 0.1f, true); // �״� �ִϸ��̼�
}
