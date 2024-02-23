#include "Monster_Base.h"
#include "ModeEnum.h"
#include <EngineCore/EngineCore.h>

AMonster_Base::AMonster_Base()
{
}

AMonster_Base::~AMonster_Base()
{
}

void AMonster_Base::IceState()
{
	scale = 2;
	MonsterRenderer->ChangeAnimation("MonsterIce");
	MonsterRenderer->SetTransform({ {0,1}, {64*scale, 64*scale} }); // ������ ��ġ ũ�� 
	IsIce = true;
}

void AMonster_Base::BeginPlay()
{
	AActor::BeginPlay();
	scale = 3;
	{
		MonsterRenderer = CreateImageRenderer(ERenderOrder::Monster); // �̹��� ���� ����
		MonsterRenderer->SetImage("Dee_Right.png"); // �̹��� Set
		MonsterRenderer->SetTransform({ {0,1}, {64* scale, 64* scale} }); // ������ ��ġ ũ�� 
	}

	{
		MonsterCollision = CreateCollision(ECollisionOrder::Monster);
		MonsterCollision->SetScale({ 70, 70 });
		MonsterCollision->SetColType(ECollisionType::Rect);
	}

	AniCreate();

	MonsterRenderer->ChangeAnimation("Monster_Left");
}

void AMonster_Base::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	if (false == diecheck)
	{
		MoveUpdate(_DeltaTime);
	}
	else {
		AddActorLocation(DiePos);
	
	}
	
	
}

void AMonster_Base::MoveUpdate(float _DeltaTime)
{
	AddActorLocation(GetGravity(GetActorLocation().iX(), GetActorLocation().iY(), _DeltaTime)); // �߷� �ۿ�
	FVector PlayerPos = Player->GetActorLocation();  // �÷��̾� ��ġ
	FVector MonsterPos = GetActorLocation(); // ���� ��ġ

	FVector MosterXL = MonsterPos + FVector::Left * sight; // ���� ���� �÷��̾� �ν� �þ� X��
	FVector MosterXR = MonsterPos + FVector::Right * sight; // ���� ������ �÷��̾� �ν� �þ� X��

	FVector PlayerX = PlayerPos * FVector::Right; // �÷��̾� ��ġ X��

	FVector MonsterDir = PlayerPos - MonsterPos; // �÷��̾� ��ġ - ���� ��ġ = ���� ex) ���Ͱ� �÷��̾�� ���ϴ� ����
	MonsterDirNormal = MonsterDir.Normalize2DReturn();  // �ش簪�� ����ȭ 

	FVector MovePos = FVector::Zero;
	
	// �ݸ��� 
	std::vector<UCollision*> Result;
	if (true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == false)
	{
		
			
		//MonsterRenderer->SetAlpha(0.5f+nf);
		
		// �̷������� ��븦 ����Ҽ� �ִ�.
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AKirby_Player* Player = dynamic_cast<AKirby_Player*>(Ptr);

		if (nullptr == Player)
		{
			MsgBoxAssert("�����߰���....");
		}

		if (true == GetBaseOnOff())
		{
			Destroy();
		}
		else {
			//Player->GetKirbyRender()->SetAlpha(0.5f);
			//FVector Move = MonsterDirNormal * 500.0f * _DeltaTime *FVector::Right;
			//Player->AddActorLocation(Move);
			//GetWorld()->AddCameraPos(Move);
			MonsterRenderer->ChangeAnimation("die_Right");
			DiePos=MonsterDirNormal * -200.0f * _DeltaTime*FVector::Right;
			diecheck = true;
		}
	}
	else if ((true == MonsterCollision->CollisionCheck(ECollisionOrder::kirby, Result) && IsIce == true)) {
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

	if (true==diecheck)
	{
		MovePos = FVector::Zero;
		Destroy(0.3f);
	}
	else {
		BaseMove(_DeltaTime);

		if (IsIce == false)
		{
			AddActorLocation(MovePos);
		}
		else {
			AddActorLocation(IceMove);
		}
	}
}

void AMonster_Base::AniCreate()
{
	// �⺻ �ȴ� ���

	MonsterRenderer->CreateAnimation("Monster_Right", "Dee_Right.png", 0, 4, 0.1f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("Monster_Left", "Dee_Left.png", 0, 4, 0.1f, true); // �ȱ�
	MonsterRenderer->CreateAnimation("MonsterIce", "Ice_Right.png", 108, 108, false);
	MonsterRenderer->CreateAnimation("die_Right", "Dee_Right.png", 5, 5,0.2f, false);
}

void AMonster_Base::BaseMove(float _DeltaTime)
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
			MonsterRenderer->ChangeAnimation("Monster_Left");
			checkX = -30;
		}
		else if(DirMonster.iX() == 1 && IsIce == false){
			MonsterRenderer->ChangeAnimation("Monster_Right");
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
			else {
				DirMonster.X *= -1;
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




