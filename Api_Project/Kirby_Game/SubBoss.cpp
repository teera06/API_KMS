#include "SubBoss.h"

SubBoss::SubBoss()
{
}

SubBoss::~SubBoss()
{
}

void SubBoss::BeginPlay()
{

}

void SubBoss::Tick(float _DeltaTime)
{

}

void SubBoss::CalDir(float _DeltaTime)
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

void SubBoss::IceAtt()
{
}

void SubBoss::Collisiongather(float _DeltaTime)
{
}

void SubBoss::CalResult(float _DeltaTime)
{
}

void SubBoss::GroundUp()
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

void SubBoss::MoveUpdate(float _DeltaTime)
{
}

void SubBoss::AniCreate()
{
	MonsterRenderer->CreateAnimation("Move_Right", "Tock_Right.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Move_Left", "Tock_Left.png", 7, 9, 0.3f, true);
	MonsterRenderer->CreateAnimation("Att_Right", "Tock_Right.png", 4, 6, 0.15f, false);
	MonsterRenderer->CreateAnimation("Att_Left", "Tock_Left.png", 4, 6, 0.15f, false);

	MonsterRenderer->CreateAnimation("die_Right", "Tock_Left.png", 11, 13, 0.3f, true); // ���� 
	MonsterRenderer->CreateAnimation("die_Left", "Tock_Right.png",11, 13, 0.3f, true); // ���� 
	
	//MonsterRenderer->CreateAnimation("Effect", "Effects.png", 29, 30, 0.1f, true); // �״� �ִϸ��̼�
}
