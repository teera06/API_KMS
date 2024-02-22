#include "Ice.h"

#include "ModeEnum.h"
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Kirby_Player.h"

AIce::AIce()
{
}

AIce::~AIce()
{
}

void AIce::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (GetDir().iX() == FVector::Left.iX())
	{
		IceRenderer->ChangeAnimation("Ice_Right");
	}
	else
	{
		IceRenderer->ChangeAnimation("Ice_Left");
	}

	IceCollision->SetPosition({ GetDir().iX() * 120,0 });
	IceRenderer->SetPosition({ GetDir().iX() * 125,-5 });


	std::vector<UCollision*> Result;
	if (true == IceCollision->CollisionCheck(ECollisionOrder::Monster, Result))
	{
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("�����߰���....");
		}
		IceCollision->Destroy(0.1f);
		Monster->IceState();
	}
	else if (true == IceCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
	{
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);

		if (nullptr == Monster)
		{
			MsgBoxAssert("�����߰���....");
		}
		IceCollision->Destroy(0.1f);
		Monster->IceState();
	}

	IceRenderer->Destroy(0.1f);
}

void AIce::BeginPlay()
{
	AActor::BeginPlay();
	{
		IceRenderer = CreateImageRenderer(ERenderOrder::Ice); // �̹��� ���� ����
		IceRenderer->SetImage("Ice_Right.png"); // �̹��� Set
		IceRenderer->SetActive(true, 0.45f);
		IceRenderer->SetTransform({ {0,0}, {128*3, 128*2} }); // ������ ��ġ ũ�� 
	}
	{
		IceCollision = CreateCollision(ECollisionOrder::IceAttack);
		IceCollision->SetScale({ 100,70 });
		IceCollision->SetColType(ECollisionType::Rect);
	}

	IceRenderer->CreateAnimation("Ice_Right", "Ice_Right.png", {104,105,106,107,109,110,111}, 0.05f, true);
	IceRenderer->CreateAnimation("Ice_Left", "Ice_Left.png", { 104,105,106,107,109,110,111 }, 0.05f, true);
	IceRenderer->ChangeAnimation("Ice_Right");

	Destroy(1.0f);
}