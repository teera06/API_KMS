#include "TitleActor.h"

#include "ModeEnum.h"

ATitleActor::ATitleActor()
{
}

ATitleActor::~ATitleActor()
{
}

void ATitleActor::BeginPlay()
{
	AActor::BeginPlay();

	TitleRenderer = CreateImageRenderer(ERenderOrder::TitleMap); // �̹��� ���� ����
	TitleRenderer->SetImage("Mapback.png"); // �̹��� Set
	TitleRenderer->SetTransform({ {0,0}, {1900,1100} }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 

	LogRenderer = CreateImageRenderer(ERenderOrder::Log); // �̹��� ���� ����
	LogRenderer->SetImage("Log.png"); // �̹��� Set
	LogRenderer->SetTransform({ { 0,50 }, windowScale });

	StartRenderer = CreateImageRenderer(ERenderOrder::Log); // �̹��� ���� ����
	StartRenderer->SetImage("Text.png"); // �̹��� Set
	StartRenderer->SetTransform({ { 200,250 }, {64*10, 64*8} });
	
	// �ִϸ��̼� ���� �� ����
	// ��� �ִϸ��̼�
	TitleRenderer->CreateAnimation("Mapback", "Mapback.png", 0, 4, 3.0f, true);
	TitleRenderer->ChangeAnimation("Mapback");

	// Ready �ִϸ��̼�
	StartRenderer->CreateAnimation("Ready", "Text.png", 0, 10, 0.5f, false);
	StartRenderer->ChangeAnimation("Ready");
}

void ATitleActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
