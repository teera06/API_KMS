#include "Stage2_Level.h"

#include "Stage3_Level.h"
#include "Stage2_Map.h"
#include "Kirby_Player.h" 
#include "Kirby_HpBar.h"
#include "Monster_Base.h"
#include "Monster_Fire.h"
#include "Monster_Sir.h"
#include "Box.h"

// 리소스 (이미지, 사운드) 로드하기 위해 필요한 헤더
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

bool UStage2_Level::LoadCheck = false;

UStage2_Level::UStage2_Level()
{
}

UStage2_Level::~UStage2_Level()
{
}

void UStage2_Level::BeginPlay()
{
	ULevel::BeginPlay();

	if (false == LoadCheck)
	{
		LoadCheck = true;

		UEngineDirectory NewPath; // 현재 파일 경로

		NewPath.MoveToSearchChild("GameResources");
		NewPath.Move("Stage"); // 폴더 이동
		NewPath.Move("stage2");
		// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
		std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
		// png, bmp 파일 
		// true -> 폴더 안의 폴더안에 이미지도 재귀함수로 체크

		for (UEngineFile& File : AllFileList)
		{
			std::string FullPath = File.GetFullPath(); // 파일의 전체 경로
			// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
			UEngineResourcesManager::GetInst().LoadImg(FullPath); // 로딩 -> Map(Iamges)
		}

		// 이미지 컷팅 -> 커비 관련 이미지
		UEngineResourcesManager::GetInst().CuttingImage("Sir_Right.png", 10, 10);
		UEngineResourcesManager::GetInst().CuttingImage("Sir_Left.png", 10, 10);
		UEngineResourcesManager::GetInst().CuttingImage("SirMonster_Right.png", 5, 5);
		UEngineResourcesManager::GetInst().CuttingImage("SirMonster_Left.png", 5, 5);
		UEngineResourcesManager::GetInst().CuttingImage("item.png", 3, 1);

		std::list<UEngineFile> SoundList = NewPath.AllFile({ ".wav", ".mp3" }, true);
		// 엔진만의 규칙을 정할거냐.
		for (UEngineFile& File : SoundList)
		{
			UEngineSound::Load(File.GetFullPath());
		}
	}
}

void UStage2_Level::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UStage2_Level::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	BGMPlayer = UEngineSound::SoundPlay("Stage1BGM.mp3");
	BGMPlayer.SetVolume(0.7f);
	BGMPlayer.Loop();

	SetCameraPos({ 0,585}); // 카메라 위치 설정

	// 맵 생성
	NewMap = SpawnActor<AStage2_Map>();
	NewMap->SetMapImage("stage2_map.png");
	NewMap->SetColMapImage("cor2_map.png");
	NewMap->SwitchDebug();

	// 커비와 커비 상태창 Actor 생성
	NewPlayer = SpawnActor<AKirby_Player>();
	NewPlayer->SetActorLocation({ 500,1200 });

	NewHpBar = SpawnActor<AKirby_HpBar>();

	NewBase[0] = SpawnActor<AMonster_Base>();
	NewBase[0]->SetActorLocation({ 750,1050 });

	NewBase[1] = SpawnActor<AMonster_Base>();
	NewBase[1]->SetActorLocation({1800,1000});
	
	for (int i = 0; i < Firesize; i++)
	{
		NewFire[i] = SpawnActor<AMonster_Fire>();
		NewFire[i]->SetActorLocation({ 1000 + i * 1000,600 });
	}

	NewFire[5]= SpawnActor<AMonster_Fire>();
	NewFire[5]->SetActorLocation({ 3600,1000 });

	
	NewSir[0] = SpawnActor<AMonster_Sir>();
	NewSir[0]->SetActorLocation({1000,800});
	
	NewSir[1] = SpawnActor<AMonster_Sir>();
	NewSir[1]->SetActorLocation({ 2800,1000 });

	NewSir[2] = SpawnActor<AMonster_Sir>();
	NewSir[2]->SetActorLocation({ 4800,1000 });

	NewSir[3] = SpawnActor<AMonster_Sir>();
	NewSir[3]->SetActorLocation({ 5200,600 });
	
	NewBox = SpawnActor<ABox>();
	NewBox->SetIsItem(true);
	NewBox->SetActorLocation({ 3370,1000 });;
	GEngine->CreateLevel<UStage3_Level>("Stage3_Level"); // stage2_Level 다음 레벨 미리 준비
}

void UStage2_Level::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
	BGMPlayer.Off();
	GEngine->DestroyLevel("Stage2_Level");
}
