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
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64 * scale, 64 * scale} }); // ������ ��ġ ũ�� 
	IsIce = true;
}

void Apengi_Ice::BeginPlay()
{
	AActor::BeginPlay();

	scale = 5;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		MonsterRenderer->SetImage("pengi_Right.png"); // �̹��� Set
		MonsterRenderer->SetTransform({ {0,0}, {64*scale, 64*scale} }); // ������ ��ġ ũ�� 
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::iceMonster);
		MonsterCollision->SetScale({ 70, 70 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	AniCreate();
	MonsterRenderer->ChangeAnimation("Idle_Left");
}

void Apengi_Ice::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (false == IsDie) // Destroy(0.3f); -> ���Ǿ��� ��� move������Ʈ �Ǹ鼭 0.3f�� �Ȱ��� ���� (�ѹ��� �����ؾ���)
	{
		MoveUpdate(_DeltaTime);
	}
	else { // IsDIe�� true�̸� MoveUpdate�� ���� ������ �ȵ� -> Destroy(0.3f) �۵�
		AddActorLocation(DiePos); // �����鼭 �̵�
	}
}

void Apengi_Ice::AniCreate()
{
	MonsterRenderer->CreateAnimation("Idle_Right", "Pengi_Right.png", 0, 0, 0.3f, true);  
	MonsterRenderer->CreateAnimation("Idle_Left", "Pengi_Left.png", 0, 0, 0.3f, true); 
	MonsterRenderer->CreateAnimation("Move_Right", "Pengi_Right.png", 1, 3, 0.3f, true); 
	MonsterRenderer->CreateAnimation("Move_Left", "Pengi_Left.png", 1, 3, 0.3f, true); 

	MonsterRenderer->CreateAnimation("die_Right", "Pengi_Left.png", 7, 8, 0.3f, true); // ���� 
	MonsterRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false); // ����
}

void Apengi_Ice::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // �߷� �ۿ�

	FVector PlayerPos = MainPlayer->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector MosterXL = MonsterPos + FVector::Left * sight; // ���� ���� �÷��̾� �ν� �þ� X��
	FVector MosterXR = MonsterPos + FVector::Right * sight; // ���� ������ �÷��̾� �ν� �þ� X��

	FVector PlayerX = PlayerPos * FVector::Right; // �÷��̾� ��ġ X��

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 

	FVector MovePos = FVector::Zero; // �÷��̾� �߰� �� �̵�

	if (MosterXL.iX() < PlayerX.iX() && MosterXR.iX() > PlayerX.iX()) // ���� �þ߿� ������ ��� X�� ���� ����, ������
	{
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // ���� ����
		{
			MonsterRenderer->ChangeAnimation("Move_Left");
			WallX = -20;
		}
		else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // ������ ����
			MonsterRenderer->ChangeAnimation("Move_Right");
			WallX = 20;
		}
		MoveSpeed = 50.0f;
		MovePos += MonsterDirNormal * _DeltaTime * MoveSpeed * FVector::Right; // ���Ͱ� �÷��̾��� Y�൵ �ν��� �� ������ FVector::Right �� ���� X�ุ �߰�
	}
	else { // �÷��̾ ���� �þ� ���� ��� ���� �ൿ����
		if (MonsterDirNormal.iX() == -1 && IsIce == false) // ���� ����
		{
			MonsterRenderer->ChangeAnimation("Idle_Left");
			WallX = -20;

		}
		else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // ������ ����
			MonsterRenderer->ChangeAnimation("Idle_Right");
			WallX = 20;
		}
	}
	// �ݸ��� 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == false) // ���� ���� ���¿��� �÷��̾�� �浹
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);

		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		// ����ڵ�
		if (nullptr == Player)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}

		if (true == GetBaseOnOff()) // ����� ���� ���� �浹 -> ���ʹ� �÷��̾�� �浹�� ��� �ٷ� ����
		{
			Destroy();
		}
		else {// �Ϲ����� �÷��̿��� �浹
			Player->Sethitstate(true); // �÷��̾� �浹 üũ
			Player->AddHP(-20);
			Player->HitStart(); // hit ���� ��ŸƮ
			Player->GetKirbyRender()->SetAlpha(0.5f);
			Player->GetKirbyCollision()->ActiveOff();
			MonsterRenderer->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
			DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
			IsDie = true; // ���� üũ
		}
	}
	else if ((true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == true)) { // ���� ���·� Ŀ��� �浹 �ϴ� ���
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("�����߰���....");
		}

		// ���� ���� �϶� ������ ���
		if (MonsterDirNormal.iX() == -1) // ���Ͱ� �÷��̾ ���ϴ� ������ �ݴ� �������� ���� �ۿ�
		{

			IceMove = FVector::Right * IceSpeed * _DeltaTime;

		}
		else {

			IceMove = FVector::Left * IceSpeed * _DeltaTime;
		}
	}

	// ���� ���¿��� ���� �浹�� �ٷ� ���� -> ���� ����Ʈ ������ ���
	Color8Bit ColorR = ActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);
	if (ColorR == Color8Bit(255, 0, 0, 0))
	{
		if (true == IsIce)
		{
			IceMove = FVector::Zero;
			Destroy();
		}

		MovePos = FVector::Zero;
	}

	if (true == IsDie) // ������
	{
		Destroy(0.3f); // 0.3f �ڿ� ����
	}
	else {
		if (false == IsIce) // �װų�, �������°� �ƴϸ� �Ϲ� �ൿ
		{
			AddActorLocation(MovePos);
		}
		else {
			MovePos = FVector::Zero;
			AddActorLocation(IceMove);
		}
	}
}




