#include "Sir.h"

#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"

ASir::ASir()
{
}

ASir::~ASir()
{
}

void ASir::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	CalDir();
	SkillDir(_DeltaTime);


	Collisiongather(_DeltaTime);


	//SirRenderer->Destroy(0.1f);
}

void ASir::BeginPlay()
{
	AActor::BeginPlay();
	{
		SirRenderer = CreateImageRenderer(ERenderOrder::Ice); // �̹��� ���� ����
		SirRenderer->SetImage("Sir_Right.png"); // �̹��� Set
		SirRenderer->SetTransform({ {0,0}, {64 * 3, 64 * 3} }); // ������ ��ġ ũ�� 
	}
	{
		SirCollision = CreateCollision(ECollisionOrder::SirAttack);
		SirCollision->SetScale({ 100,70 });
		SirCollision->SetColType(ECollisionType::CirCle);
		SirCollision->SetActive(true, 0.3f);
	}

	AniCreate();
}

void ASir::AniCreate()
{
	SirRenderer->CreateAnimation("Sir_Right", "Sir_Right.png", 95,98, 0.05f, true);
	SirRenderer->CreateAnimation("Sir_Left", "Sir_Left.png", 95,98, 0.05f, true);
	SirRenderer->ChangeAnimation("Sir_Right");
}

void ASir::CalDir()
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 
}

void ASir::SkillDir(float _DeltaTime)
{
	FVector Move = FVector::Zero;
	FVector CurX = GetActorLocation() * FVector::Right;
	FVector RangeXL = StartPos + (FVector::Left * RangeX);
	FVector RangeXR = StartPos + (FVector::Right * RangeX);
	//StartDir = GetDir();
	if (GetDir().iX() == FVector::Left.iX())
	{
		if (false == skillOn)
		{
			skillOn = true;
			StartDir = FVector::Left;
		}
		SirRenderer->ChangeAnimation("Sir_Right");
	}
	else
	{
		if (false == skillOn)
		{
			skillOn = true;
			StartDir = FVector::Right;
		}
		SirRenderer->ChangeAnimation("Sir_Left");
	}

	if (RangeXR.iX() <= CurX.iX() && GetDir().iX() == FVector::Right.iX()) // �⺻ ���� �̵� ���� �¿� +-100 �� ���� ����� ��� -> ���� ��ȯ
	{
		StartDir = StartDir * FVector::Left;
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 1000.0f); // �ش� ���� ����� �Ʒ��� else���� ������ �� �ֱ⿡ �ٽ� ���������� �ű�� ����
		return;
	}
	
	if (RangeXL.iX() >= CurX.iX() && GetDir().iX() == FVector::Left.iX()) // �⺻ ���� �̵� ���� �¿� +-100 �� ���� ����� ��� -> ���� ��ȯ
	{
		StartDir = StartDir * FVector::Left;
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 1000.0f); // �ش� ���� ����� �Ʒ��� else���� ������ �� �ֱ⿡ �ٽ� ���������� �ű�� ����
		return;
	}
	
	AddActorLocation(StartDir * 500.0f * _DeltaTime);
}

void ASir::Collisiongather(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (Owner == ESirOwner::kirby)
	{
		if (true == SirCollision->CollisionCheck(ECollisionOrder::Monster, Result))
		{
			// �̷������� ��븦 ����Ҽ� �ִ�.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);


			if (nullptr == Monster)
			{
				MsgBoxAssert("�����߰���....");
			}

			if (MonsterDirNormal.iX() == -1) // ���Ͱ� �÷��̾ ���ϴ� ������ �ݴ� �������� ���� �ۿ�
			{
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Left"); // �״� �ִϸ��̼�

			}
			else {
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
			}
			FVector DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
			Monster->SetIsDie(true);
			Monster->SetDiePos(DiePos);
			Monster->Destroy(0.3f);
		}
		else if (true == SirCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
		{
			// �̷������� ��븦 ����Ҽ� �ִ�.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);


			if (nullptr == Monster)
			{
				MsgBoxAssert("�����߰���....");
			}

			if (MonsterDirNormal.iX() == -1) // ���Ͱ� �÷��̾ ���ϴ� ������ �ݴ� �������� ���� �ۿ�
			{
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Left"); // �״� �ִϸ��̼�

			}
			else {
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
			}
			FVector DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
			Monster->SetIsDie(true);
			Monster->SetDiePos(DiePos);
			Monster->Destroy(0.3f);
		}
		else if (true == SirCollision->CollisionCheck(ECollisionOrder::FireMonster, Result))
		{
			// �̷������� ��븦 ����Ҽ� �ִ�.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Fire* Monster = dynamic_cast<AMonster_Fire*>(Ptr);


			if (nullptr == Monster)
			{
				MsgBoxAssert("�����߰���....");
			}

			if (MonsterDirNormal.iX() == -1) // ���Ͱ� �÷��̾ ���ϴ� ������ �ݴ� �������� ���� �ۿ�
			{
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Left"); // �״� �ִϸ��̼�

			}
			else {
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
			}
			FVector DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
			Monster->SetIsDie(true);
			Monster->SetDiePos(DiePos);
			Monster->Destroy(0.3f);
		}else if (true == SirCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
		{
			// �̷������� ��븦 ����Ҽ� �ִ�.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Sir* Monster = dynamic_cast<AMonster_Sir*>(Ptr);


			if (nullptr == Monster)
			{
				MsgBoxAssert("�����߰���....");
			}

			if (MonsterDirNormal.iX() == -1) // ���Ͱ� �÷��̾ ���ϴ� ������ �ݴ� �������� ���� �ۿ�
			{
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Left"); // �״� �ִϸ��̼�

			}
			else {
				Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
			}
			FVector DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
			Monster->SetIsDie(true);
			Monster->SetDiePos(DiePos);
			Monster->Destroy(0.3f);
		}
		
		
		
		if (true == SirCollision->CollisionCheck(ECollisionOrder::kirby, Result))
		{
			MainPlayer->SetSirUse(false);
			Destroy();
				
		}



		// �ȼ� �浹
		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 20, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			MainPlayer->SetSirUse(false);
			Destroy();
			
		}
	}
	else if (Owner == ESirOwner::SirMonster)
	{
		if (true == SirCollision->CollisionCheck(ECollisionOrder::kirby, Result))
		{
			MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
			MainPlayer->Sethitstate(true); // �÷��̾� �浹 üũ
			MainPlayer->SetHitDir(GetDir());
			MainPlayer->GetKirbyCollision()->ActiveOff();
			MainPlayer->AddHP(-20);
			MainPlayer->HitStart(); // hit ���� ��ŸƮ
		}
		else if (true == SirCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
		{
			Destroy();
		}

		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 20, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			Destroy();
		}
	}

}
