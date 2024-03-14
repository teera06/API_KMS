#include "Sir.h"

#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"
#include "Box.h"

ASir::ASir()
{
}

ASir::~ASir()
{
}

void ASir::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (Owner == ESirOwner::kirby)
	{
		SSirtime -= _DeltaTime;
		if (SSirtime < 0)
		{
			UEngineSound::SoundPlay("Sir.wav").SetVolume(0.6f);
			SSirtime = 2.0f;
		}
	}
	else if(Owner==ESirOwner::SirMonster){
		SSirtime -= _DeltaTime;
		if (SSirtime < 0)
		{
			UEngineSound::SoundPlay("Sir.wav").SetVolume(0.1f);
			SSirtime = 2.0f;
		}
	}

	if (GetDir().iX() != FVector::Zero.iX())
	{
		CalDir();
		SkillDir(_DeltaTime);


		Collisiongather(_DeltaTime);
	}
}

void ASir::BeginPlay()
{
	AActor::BeginPlay();
	{
		SirRenderer = CreateImageRenderer(ERenderOrder::Sir); // �̹��� ���� ����
		SirRenderer->SetImage("Sir_Right.png"); // �̹��� Set
		SirRenderer->SetTransform({ {0,0}, {64 * 3, 64 * 3} }); // ������ ��ġ ũ�� 
		SirRenderer->SetActive(true, 0.1f);
	}
	{
		SirCollision = CreateCollision(ECollisionOrder::SirAttack);
		SirCollision->SetScale({ 100,70 });
		SirCollision->SetColType(ECollisionType::CirCle);
		SirCollision->SetActive(true, 0.2f);
	}

	AniCreate();
}

void ASir::AniCreate()
{
	SirRenderer->CreateAnimation("Sir_Right", "Sir_Right.png", 95,98, 0.05f, true);
	SirRenderer->CreateAnimation("Sir_Left", "Sir_Left.png", 95,98, 0.05f, true);
}

void ASir::CalDir()
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���͸� ���� ������ ����

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 
}

void ASir::SkillDir(float _DeltaTime)
{
	FVector CurX = GetActorLocation() * FVector::Right;
	FVector RangeXL = StartPos + (FVector::Left * RangeX); // �θ޶��� ���� ������ �̵� ���� ��� (�������� ���� ���)
	FVector RangeXR = StartPos + (FVector::Right * RangeX); // (���������� ���� ���)

	if (GetDir().iX() == FVector::Left.iX()) // ���� ����
	{
		if (false == skillOn) // ��ų�� ������� ���� ��쿡�� 
		{
			skillOn = true;
			StartDir = FVector::Left; // �θ޶� �̵� ����
		}
		LRCheck = true; // �θ޶��� ���ʿ��� ���������� �̵� -> True=Right
		DelX = FVector::Right*MainPlayer->GetActorLocation(); // �÷��̾��� X�� ��ġ�� ����
		SirRenderer->ChangeAnimation("Sir_Right");
	}
	else // ������ ����
	{
		if (false == skillOn)
		{
			skillOn = true;
			StartDir = FVector::Right;
		}
		LRCheck = false; // �θ޶��� �����ʿ��� �������� �̵� -> false=Left
		DelX = FVector::Right * MainPlayer->GetActorLocation();
		SirRenderer->ChangeAnimation("Sir_Left");
	}

	if (RangeXR.iX() <= CurX.iX() && GetDir().iX() == FVector::Right.iX())  // ���������� ������ 
	{
		StartDir = StartDir * FVector::Left; // ���ƿ��� ������ ����
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 1000.0f); 
		return;
	}
	
	if (RangeXL.iX() >= CurX.iX() && GetDir().iX() == FVector::Left.iX()) // �������� ������ 
	{
		StartDir = StartDir * FVector::Left; // ���ƿ��� ������ �ݴ� ������ ������
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 1000.0f); 
		return;
	}
	Move = StartDir * 500.0f;
	AddActorLocation(Move*_DeltaTime);
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
			StartDir = StartDir * FVector::Left;
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
			StartDir = StartDir * FVector::Left;
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
			StartDir = StartDir * FVector::Left;
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
			StartDir = StartDir * FVector::Left;
		}
		else if (true == SirCollision->CollisionCheck(ECollisionOrder::MikeMonster, Result, Move*0.01f)
			|| true == SirCollision->CollisionCheck(ECollisionOrder::SubBoss, Result, Move* 0.01f)
			|| true == SirCollision->CollisionCheck(ECollisionOrder::MainBoss, Result, Move* 0.01f)
			|| true == SirCollision->CollisionCheck(ECollisionOrder::IceBox, Result, Move* 0.01f))
		{
			StartDir = StartDir * FVector::Left;
        }
		else if (true == SirCollision->CollisionCheck(ECollisionOrder::Box, Result))
		{
			// �̷������� ��븦 ����Ҽ� �ִ�.
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			ABox* item = dynamic_cast<ABox*>(Ptr);

			if (nullptr == item)
			{
				MsgBoxAssert("�����߰���....");
			}

			item->SetIsDelete(true);
			StartDir = StartDir * FVector::Left;
		}
		
		
		
		// �θ޶��� ���� ���ϰ� ������ ũ�� �����
		FVector XL = DelX + FVector::Left * 500.0f; // ���� ���� �÷��̾� �ν� �þ� X��
		FVector XR = DelX + FVector::Right * 500.0f; // ���� ������ �÷��̾� �ν� �þ� X��

		if (true==LRCheck && XR.iX()<GetActorLocation().iX()) // ���ƿ��� ������ ������ -> �θ޶��� ������ �������� ������ �������� Ŀ���� ����
		{
			MainPlayer->SetSirUse(false); 
			Destroy();
		}
		else if (false==LRCheck &&  XL.iX()>GetActorLocation().iX()) // ���ƿ��� ������ ���� -> �θ޶��� ���� �������� ������ �������� ���� �� ����
		{
			MainPlayer->SetSirUse(false);
			Destroy();
		}
		
		// Ŀ�� �޾Ƴ���
		if (true == SirCollision->CollisionCheck(ECollisionOrder::kirby, Result))
		{
			MainPlayer->SetSirUse(false);
			Destroy();
				
		}

		// �ȼ� �浹
		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 20, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			StartDir = StartDir * FVector::Left;
			
		}
	}
	else if (Owner == ESirOwner::SirMonster)
	{
		if (false == SirMonsterDelete)
		{
			Destroy(3.0f);
			SirMonsterDelete = true;
		}

		if (true == SirCollision->CollisionCheck(ECollisionOrder::kirby, Result))
		{
			MainPlayer->GetKirbyRender()->SetAlpha(0.5f);
			MainPlayer->Sethitstate(true); // �÷��̾� �浹 üũ
			MainPlayer->SetHitDir(GetDir());
			MainPlayer->GetKirbyCollision()->ActiveOff();
			MainPlayer->AddHP(GetAtt());
			MainPlayer->HitStart(); // hit ���� ��ŸƮ
			StartDir = StartDir * FVector::Left;
		}
		else if (true == SirCollision->CollisionCheck(ECollisionOrder::SirMonster, Result))
		{
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster_Sir* Monster = dynamic_cast<AMonster_Sir*>(Ptr);

			Monster->SetSirUse(false);
			Destroy();
		}

		// �ȼ� �浹
		Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 20, Color8Bit::RedA);

		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			StartDir = StartDir * FVector::Left;
		}
	}
}
