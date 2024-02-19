#include "pengi_Ice.h"

Apengi_Ice::Apengi_Ice()
{
}

Apengi_Ice::~Apengi_Ice()
{
}

void Apengi_Ice::BeginPlay()
{
	AActor::BeginPlay();
	{
		PengiRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		PengiRenderer->SetImage("pengi_Right.png"); // �̹��� Set
		PengiRenderer->SetTransform({ {0,0}, {330, 330} }); // ������ ��ġ ũ�� 
	}

	{
		PengiCollision = CreateCollision(ECollisionOrder::iceMonster);
		PengiCollision->SetScale({ 70, 70 });
		PengiCollision->SetColType(ECollisionType::Rect);
	}

	AniCreate();
	PengiRenderer->ChangeAnimation("Pengi_Right");
}

void Apengi_Ice::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime));

	std::vector<UCollision*> Result;
	if (true == PengiCollision->CollisionCheck(ECollisionOrder::kirby, Result))
	{
		
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		//AActor* Ptr = Collision->GetOwner();
		//AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("�����߰���....");
		}
		Destroy();
	}
}

void Apengi_Ice::AniCreate()
{
	// �⺻ �ȴ� ���
	PengiRenderer->CreateAnimation("Pengi_Right", "Pengi_Right.png", 1, 4, 0.3f, true); // �ȱ�
	PengiRenderer->CreateAnimation("Pengi_Left", "Pengi_Left.png", 1, 4, 0.3f, true); // �ȱ�
}
