#include "Stage1_Level.h"

// Actor
#include "Stage1_MAP.h" 
#include "Kirby_Player.h" 
#include "Monster_Base.h"
#include "pengi_Ice.h"
#include "Kirby_HpBar.h"

// ���ҽ� (�̹���, ����) �ε��ϱ� ���� �ʿ��� ���
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UStage1_Level::UStage1_Level()
{
}

UStage1_Level::~UStage1_Level()
{
}

void UStage1_Level::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath; // ���� ���� ���

	NewPath.MoveParent(); // ���� ���� ����� ���� ������ �̵�

	NewPath.Move("GameResources"); // ���� �������� �ٸ� ������ �̵�
	NewPath.Move("Stage1"); // ���� �̵�

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
	UEngineResourcesManager::GetInst().CuttingImage("kirby_Right.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby_Left.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby2_Right.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("kirby2_Left.png", 10, 6);
	UEngineResourcesManager::GetInst().CuttingImage("Ice_Right.png", 10, 12);
	UEngineResourcesManager::GetInst().CuttingImage("Ice_Left.png", 10, 12);
	UEngineResourcesManager::GetInst().CuttingImage("effect_Right.png", 8, 2);
	UEngineResourcesManager::GetInst().CuttingImage("effect_Left.png", 8, 2);
	UEngineResourcesManager::GetInst().CuttingImage("changeHUD.png", 5, 2);

	// �̹��� ���� -> ���� ���� �̹���
	UEngineResourcesManager::GetInst().CuttingImage("Dee_Left.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Dee_Right.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Pengi_Right.png", 5, 2);
	UEngineResourcesManager::GetInst().CuttingImage("Pengi_Left.png", 5, 2);

	//NewPath.Move("GameResources"); // ���� �������� �ٸ� ������ �̵�
	//NewPath.Move("sound"); // ���� �̵�

	std::list<UEngineFile> testList = NewPath.AllFile({ ".wav", ".mp3" }, true);
		// �������� ��Ģ�� ���Ұų�.
	for (UEngineFile& File : testList)
	{
		UEngineSound::Load(File.GetFullPath());
	}

	BGMPlayer = UEngineSound::SoundPlay("Foot_1_1.wav");
	BGMPlayer.Loop();
	// BGMPlayer = UEngineSound::SoundPlay("anipang_ingame_wav.wav");
	// BGMPlayer.Off();
	



	// �� ����
	AStage1_MAP* Map = SpawnActor<AStage1_MAP>();
	Map->SetMapImage("stage1_map.png");
	Map->SetColMapImage("cor_map.png");
	Map->SwitchDebug();


	// Ŀ��� Ŀ�� ����â Actor ����
	SpawnActor<AKirby_Player>()->SetActorLocation({ 500,800 });
	SpawnActor<AKirby_HpBar>();

	// ���� Actor ����
	SpawnActor<AMonster_Base>()->SetActorLocation({ 800,700 });
	SpawnActor<AMonster_Base>()->SetActorLocation({ 1400,700 });
	SpawnActor<AMonster_Base>()->SetActorLocation({ 1900,600 });

	SpawnActor<Apengi_Ice>()->SetActorLocation({ 1100,800 });
	SpawnActor<Apengi_Ice>()->SetActorLocation({ 1700,800 });
	//SpawnActor<Apengi_Ice>()->SetActorLocation({ 1100,600 });
	
}

void UStage1_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

