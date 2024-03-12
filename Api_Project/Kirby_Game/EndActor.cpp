#include "EndActor.h"
#include <EnginePlatform\EngineInput.h> // ���콺 ���� ��ư ���� ��� ���� ü����
#include "ModeEnum.h"
AEndActor::AEndActor()
{
}

AEndActor::~AEndActor()
{
}

void AEndActor::BeginPlay()
{
	AActor::BeginPlay();

	EndRenderer = CreateImageRenderer(ERenderOrder::TitleMap); // �̹��� ���� ����
	EndRenderer->SetImage("Mapback.png"); // �̹��� Set
	EndRenderer->SetTransform({ {0,0}, {1900,1100} }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 

	KirbyRenderer = CreateImageRenderer(ERenderOrder::Log); // �̹��� ���� ����
	KirbyRenderer->SetImage("Kirby_Right.png"); // �̹��� Set
	KirbyRenderer->SetTransform({ { 0,200 }, {64 * 3,64 * 3} });
	KirbyRenderer->CreateAnimation("Fly_Right", "kirby_Right.png", 58, 65, 0.1f, true);

	text1Renderer = CreateImageRenderer(ERenderOrder::Log); // �̹��� ���� ����
	text1Renderer->SetImage("text1.png"); // �̹��� Set
	text1Renderer->SetTransform({ {0,0}, {600,120} }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 
	text1Renderer->ActiveOff();

	text2Renderer = CreateImageRenderer(ERenderOrder::Log); // �̹��� ���� ����
	text2Renderer->SetImage("text2.png"); // �̹��� Set
	text2Renderer->SetTransform({ {10,0}, {600,120} }); // ���Ϳ����� ����(�̹���) ��ġ �� ũ�� ���� 
	text2Renderer->ActiveOff();
	
	EndRenderer->CreateAnimation("Mapback", "Mapback.png", 0, 4, 3.0f, true); // ������ �� �ֱ�
	EndRenderer->ChangeAnimation("Mapback");
	KirbyRenderer->ChangeAnimation("Fly_Right");

}

void AEndActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
