#include "pengi_Ice.h"
#include "ModeEnum.h"

Apengi_Ice::Apengi_Ice()
{
}

Apengi_Ice::~Apengi_Ice()
{
}

void Apengi_Ice::IceState()
{
	scale = 2;
	PengiRenderer->ChangeAnimation("MonsterIce");
	PengiRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	IsIce = true;
}

void Apengi_Ice::BeginPlay()
{
	AActor::BeginPlay();

	scale = 5;
	{
		PengiRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		PengiRenderer->SetImage("pengi_Right.png"); // �̹��� Set
		PengiRenderer->SetTransform({ {0,0}, {64*scale, 64*scale} }); // ������ ��ġ ũ�� 
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
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // �߷� �ۿ�

	FVector PlayerPos = Player->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector MosterXL = MonsterPos + FVector::Left * sight; // ���� ���� �÷��̾� �ν� �þ� X��
	FVector MosterXR = MonsterPos + FVector::Right * sight; // ���� ������ �÷��̾� �ν� �þ� X��

	FVector PlayerX = PlayerPos * FVector::Right; // �÷��̾� ��ġ X��

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 

	FVector MovePos = FVector::Zero;


	if (MosterXL.iX() < PlayerX.iX() && MosterXR.iX() > PlayerX.iX()) // ���� �þ߿� ������ ��� X�� ���� ����, ������
	{
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // ���� ����
		{
			PengiRenderer->ChangeAnimation("Pengi_Left");
			checkX = -30;
		}
		else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // ������ ����
			PengiRenderer->ChangeAnimation("Pengi_Right");
			checkX = 30;
		}
		MoveSpeed = 50.0f;
		MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // ���Ͱ� �÷��̾��� Y�൵ �ν��� �� ������ FVector::Right �� ���� X�ุ �߰�
	}
	else { // �÷��̾ ���� �þ� ���� ��� ���� �ൿ����
		BaseMove(_DeltaTime);
	}


	// �ݸ��� 
	std::vector<UCollision*> Result;
	if (true == PengiCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == false)
	{
		PengiRenderer->SetAlpha(0.5f);
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("�����߰���....");
		}
		Destroy();
	}
	else if ((true == PengiCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == true)) {
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("�����߰���....");
		}

		if (MonsterDirNormal.iX() == -1)
		{

			IceMove = FVector::Right * IceSpeed * _DeltaTime;

		}
		else {

			IceMove = FVector::Left * IceSpeed * _DeltaTime;
		}
	}


	Color8Bit ColorR = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + checkX, GetActorLocation().iY() - 30, Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		if (true == IsIce)
		{
			IceMove = FVector::Zero;
			Destroy();
		}
		else {
			MovePos = FVector::Zero;
		}

	}

	if (IsIce == false)
	{
		AddActorLocation(MovePos);
	}
	else {
		AddActorLocation(IceMove);
	}
}

void Apengi_Ice::AniCreate()
{
	PengiRenderer->CreateAnimation("Idel_Right", "Pengi_Right.png", 0, 0, 0.3f, true); // �ȱ�
	PengiRenderer->CreateAnimation("Idel_Left", "Pengi_Left.png", 0, 0, 0.3f, true); // �ȱ�
	// �⺻ �ȴ� ���
	PengiRenderer->CreateAnimation("Pengi_Right", "Pengi_Right.png", 1, 3, 0.3f, true); // �ȱ�
	PengiRenderer->CreateAnimation("Pengi_Left", "Pengi_Left.png", 1, 3, 0.3f, true); // �ȱ�
	PengiRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false);
}

void Apengi_Ice::BaseMove(float _DeltaTime)
{
	FVector Move = FVector::Zero;

	--Value;
	if (0 >= Value)
	{
		DirMonster.X *= -1;
		Value = TurnValue;
	}
	else
	{
		if (DirMonster.iX() == -1 && IsIce == false)
		{
			PengiRenderer->ChangeAnimation("Pengi_Left");
			checkX = -30;
		}
		else if (DirMonster.iX() == 1 && IsIce == false) {
			PengiRenderer->ChangeAnimation("Pengi_Right");
			checkX = 30;
		}
		Color8Bit ColorR = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + checkX, GetActorLocation().iY() - 30, Color8Bit::RedA);
		if (ColorR == Color8Bit(255, 0, 0, 0))
		{
			if (true == IsIce)
			{
				IceMove = FVector::Zero;
				Destroy();
			}
		}
		else {
			MoveSpeed = 30.0f;
			Move += DirMonster * _DeltaTime * MoveSpeed;
		}

		if (true == IsIce)
		{
			Move = FVector::Zero;
		}
		AddActorLocation(Move);
	}
}