#include "Stage1_Level.h"
#include "Kirby_Player.h"
#include "Monster_Base.h"

#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>


UStage1_Level::UStage1_Level()
{
}

UStage1_Level::~UStage1_Level()
{
}

void UStage1_Level::BeginPlay()
{

	// �����ΰ� ���;� �Ѵٰ� �����մϴ�.
	UEngineDirectory NewPath;

	NewPath.MoveParent();
	// NewPath.Move("ContentsResources");

	NewPath.Move("GameResources");
	NewPath.Move("Texture");

	SpawnActor<Kirby_Player>();
	// SpawnActor<Player>();

	// ������ 
	// �÷��̾�
	// ���
	// ����
	// ������ �ڵ�� ���⼭ �� ������ �Ѵ�.
}
