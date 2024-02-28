#include "pengi_Ice.h"
#include "ModeEnum.h"
#include "Monster_Base.h"
#include "Ice.h"

#include <EngineCore/EngineCore.h> // GetWorld ��� -> Level ���� �̿�
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
		MonsterCollision->SetScale({ 60, 60 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	AniCreate();
	MonsterRenderer->ChangeAnimation("Idle_Left");
}

void Apengi_Ice::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	GroundUp();
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
	MonsterRenderer->CreateAnimation("Att_Right", "Pengi_Right.png", 4, 6, 0.15f, false);
	MonsterRenderer->CreateAnimation("Att_Left", "Pengi_Left.png",4, 6, 0.15f, false);

	MonsterRenderer->CreateAnimation("die_Right", "Pengi_Left.png", 7, 8, 0.3f, true); // ���� 
	MonsterRenderer->CreateAnimation("die_Left", "Pengi_Right.png", 7, 8, 0.3f, true); // ���� 
	MonsterRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false); // ����
}

void Apengi_Ice::IceToMonster(float _DeltaTime)
{
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::Monster, Result)) // ���� ���� ���¿��� �÷��̾�� �浹
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster_Base* Monster = dynamic_cast<AMonster_Base*>(Ptr);

		// ����ڵ�

		if (nullptr == Monster)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}

		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		Destroy();
	}
	else if (true == MonsterCollision->CollisionCheck(ECollisionOrder::iceMonster, Result))
	{
		//MonsterRenderer->SetAlpha(0.5f+nf);
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		Apengi_Ice* Monster = dynamic_cast<Apengi_Ice*>(Ptr);

		// ����ڵ�

		if (nullptr == Monster)
		{
			MsgBoxAssert("���ͺ��̽� �÷��̾� �ν� ����");
		}

		Monster->GetMonsterRenderer()->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
		DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
		Monster->SetIsDie(true);
		Monster->SetDiePos(DiePos);
		Monster->Destroy(0.3f);
		Destroy();
	}
}

void Apengi_Ice::Collisiongather(float _DeltaTime)
{
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
			if (MonsterDirNormal.iX() == -1) // ���Ͱ� �÷��̾ ���ϴ� ������ �ݴ� �������� ���� �ۿ�
			{
				MonsterRenderer->ChangeAnimation("die_Left"); // �״� �ִϸ��̼�

			}
			else {
				MonsterRenderer->ChangeAnimation("die_Right"); // �״� �ִϸ��̼�
			}
			DiePos = MonsterDirNormal * -200.0f * _DeltaTime * FVector::Right; // �����鼭 �̵��ϴ� ��ġ ���
			IsDie = true; // ���� üũ
		}
	}
	else if ((true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == true)) { // ���� ���·� Ŀ��� �浹 �ϴ� ���
		// ���� ���� �϶� ������ ���
		if (MonsterDirNormal.iX() == -1) // ���Ͱ� �÷��̾ ���ϴ� ������ �ݴ� �������� ���� �ۿ�
		{
			WallX = 20;
			IceMove = FVector::Right * IceSpeed * _DeltaTime;

		}
		else {
			WallX = -20;
			IceMove = FVector::Left * IceSpeed * _DeltaTime;
		}
	}
}

void Apengi_Ice::CalResult(float _DeltaTime)
{
	if (true == IsIce)
	{
		IceToMonster(_DeltaTime);
	}
	// ���� ���¿��� ���� �浹�� �ٷ� ���� -> ���� ����Ʈ ������ ���
	Color8Bit ColorR = UActorCommon::ColMapImage->GetColor(GetActorLocation().iX() + WallX, GetActorLocation().iY() - 30, Color8Bit::RedA);
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

void Apengi_Ice::CalDir(float _DeltaTime)
{
	FVector PlayerPos = MainPlayer->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector MosterXL = MonsterPos + FVector::Left * sight; // ���� ���� �÷��̾� �ν� �þ� X��
	FVector MosterXR = MonsterPos + FVector::Right * sight; // ���� ������ �÷��̾� �ν� �þ� X��

	FVector AttXL = MonsterPos + FVector::Left * AttRange; // ���� ���� �÷��̾� �ν� �þ� X��
	FVector AttXR = MonsterPos + FVector::Right * AttRange; // ���� ������ �÷��̾� �ν� �þ� X��

	FVector PlayerX = PlayerPos * FVector::Right; // �÷��̾� ��ġ X��

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 

	MovePos = FVector::Zero; // �÷��̾� �߰� �� �̵�

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

	// �÷��̾ ���� ����
	if (AttXL.iX() < PlayerX.iX() && AttXR.iX() > PlayerX.iX() && MainPlayer->GetActorLocation().iY()>=GetActorLocation().iY()-30) // ���� �þ߿� ������ ��� X�� ���� ����, ������
	{
		IsAtt = true;
	}
}

void Apengi_Ice::IceAtt()
{
	AIce* NewIce = GetWorld()->SpawnActor<AIce>();
	NewIce->SetOwner(EIceOwner::iceMonster);
	if (MonsterDirNormal.iX() == -1 && IsIce == false) // ���� ����
	{
		MonsterRenderer->ChangeAnimation("Att_Left");
		NewIce->SetDir(FVector::Left);
	}
	else if (MonsterDirNormal.iX() == 1 && IsIce == false) { // ������ ����
		MonsterRenderer->ChangeAnimation("Att_Right");
		NewIce->SetDir(FVector::Right);
	}

	//NewIce->SetActive(true, 0.06f);
	if (true == MonsterRenderer->IsCurAnimationEnd())
	{
		NewIce->SetActorLocation(this->GetActorLocation());
		IsAtt = false;
		skillcooldowntime = 6.0f;
	}
}

void Apengi_Ice::GroundUp()
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

void Apengi_Ice::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // �߷� �ۿ�

	skillcooldowntime -= _DeltaTime;
	if (true == IsAtt && skillcooldowntime<0.0f)
	{
		MovePos = FVector::Zero;
		IceAtt();
	}
	else {
		CalDir(_DeltaTime);
		Collisiongather(_DeltaTime);
		CalResult(_DeltaTime);
	}
}




