#include "Sir.h"

#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Monster_Fire.h"

ASir::ASir()
{
}

ASir::~ASir()
{
}

void ASir::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

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
	}

	AniCreate();
	//Destroy(0.5f);
}

void ASir::AniCreate()
{
	SirRenderer->CreateAnimation("Sir_Right", "Sir_Right.png", 95,98, 0.05f, true);
	SirRenderer->CreateAnimation("Sir_Left", "Sir_Left.png", 95,98, 0.05f, true);
	SirRenderer->ChangeAnimation("Sir_Right");
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

	//if (RangeXL.iX() >= CurX.iX() || RangeXR.iX() <= CurX.iX()) // �⺻ ���� �̵� ���� �¿� +-100 �� ���� ����� ��� -> ���� ��ȯ
	if (RangeXR.iX() <= CurX.iX() && GetDir().iX() == FVector::Right.iX()) // �⺻ ���� �̵� ���� �¿� +-100 �� ���� ����� ��� -> ���� ��ȯ
	{
		StartDir = StartDir * FVector::Left;
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 800.0f); // �ش� ���� ����� �Ʒ��� else���� ������ �� �ֱ⿡ �ٽ� ���������� �ű�� ����
		return;
	}
	
	if (RangeXL.iX() >= CurX.iX() && GetDir().iX() == FVector::Left.iX()) // �⺻ ���� �̵� ���� �¿� +-100 �� ���� ����� ��� -> ���� ��ȯ
	{
		StartDir = StartDir * FVector::Left;
		AddActorLocation(StartDir * FVector::Right * _DeltaTime * 800.0f); // �ش� ���� ����� �Ʒ��� else���� ������ �� �ֱ⿡ �ٽ� ���������� �ű�� ����
		return;
	}
	
	AddActorLocation(StartDir * 500.0f * _DeltaTime);
	

	//AddActorLocation(GetDir() * 500.0f * _DeltaTime);

	//SirCollision->SetPosition({ GetDir().iX() * 120,0 });
	//SirRenderer->SetPosition({ GetDir().iX() * 125,-5 });
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
			SirCollision->Destroy();
			Monster->IceState();
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
			SirCollision->Destroy();
			Monster->IceState();
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
			SirCollision->Destroy();
			Monster->IceState();
		}
	}
	else if (Owner == ESirOwner::SirMonster)
	{
		if (true == SirCollision->CollisionCheck(ECollisionOrder::kirby, Result))
		{

			MainPlayer->Sethitstate(true); // �÷��̾� �浹 üũ
			MainPlayer->SetHitDir(GetDir());
			MainPlayer->GetKirbyCollision()->ActiveOff();
			MainPlayer->AddHP(-20);
			MainPlayer->HitStart(); // hit ���� ��ŸƮ

			SirCollision->Destroy();
		}
	}

}
