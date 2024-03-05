#include "Stage3_Level.h"


#include "Stage3_Map.h"
#include "Kirby_Player.h" 
#include "Kirby_HpBar.h"

// ���ҽ� (�̹���, ����) �ε��ϱ� ���� �ʿ��� ���
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UStage3_Level::UStage3_Level()
{
}

UStage3_Level::~UStage3_Level()
{
}

void UStage3_Level::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath; // ���� ���� ���

	NewPath.MoveToSearchChild("GameResources");
	NewPath.Move("Stage"); // ���� �̵�
	NewPath.Move("stage3");
	// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
	// png, bmp ���� 
	// true -> ���� ���� �����ȿ� �̹����� ����Լ��� üũ

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath(); // ������ ��ü ���
		// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
		UEngineResourcesManager::GetInst().LoadImg(FullPath); // �ε� -> Map(Iamges)
	}

	// �̹��� ���� -> Ŀ�� ���� �̹���
	UEngineResourcesManager::GetInst().CuttingImage("Mike_Right.png", 10, 4);
	UEngineResourcesManager::GetInst().CuttingImage("Mike_Left.png", 10, 4);
}

void UStage3_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UStage3_Level::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	SetCameraPos({ 0,0 }); // ī�޶� ��ġ ����

	// �� ����
	NewMap = SpawnActor<AStage3_Map>();
	NewMap->SetMapImage("Stage3_Map.png");
	NewMap->SetColMapImage("cor3_Map.png");
	NewMap->SwitchDebug();

	// Ŀ��� Ŀ�� ����â Actor ����
	NewPlayer = SpawnActor<AKirby_Player>();
	NewPlayer->SetActorLocation({ 500,300 });

	NewHpBar = SpawnActor<AKirby_HpBar>();
}

void UStage3_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);

	GEngine->DestroyLevel("Stage3_Level");
}
