#include "Stage2_Level.h"


#include "Stage2_Map.h"
#include "Kirby_Player.h" 
// ���ҽ� (�̹���, ����) �ε��ϱ� ���� �ʿ��� ���
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UStage2_Level::UStage2_Level()
{
}

UStage2_Level::~UStage2_Level()
{
}

void UStage2_Level::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath; // ���� ���� ���

	NewPath.MoveToSearchChild("GameResources");
	NewPath.Move("Stage"); // ���� �̵�
	NewPath.Move("stage2");
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

	SetCameraPos({ 0,550 }); // ī�޶� ��ġ ����

	// �� ����
	AStage2_Map* Map = SpawnActor<AStage2_Map>();
	Map->SetMapImage("stage2_map.png");
	//Map->SetMapImage("stage2_map.png");
	Map->SetColMapImage("cor2_map.png");
	Map->SwitchDebug();

	// Ŀ��� Ŀ�� ����â Actor ����
	SpawnActor<AKirby_Player>()->SetActorLocation({ 500,1000 });
	//SpawnActor<AKirby_HpBar>();
}

void UStage2_Level::Tick(float _DeltaTime)
{

}
