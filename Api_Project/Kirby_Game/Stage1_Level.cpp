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

	// 실행경로가 나와야 한다고 생각합니다.
	UEngineDirectory NewPath;

	// NewPath.Move("ContentsResources");
	NewPath.MoveParent();

	NewPath.Move("ContentsResources");
	NewPath.Move("Texture");


	// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	

	// CherryBomb_0.png
	UEngineResourcesManager::GetInst().LoadImg("test.png");

	SpawnActor<Kirby_Player>();
	// SpawnActor<Player>();

	// 할일은 
	// 플레이어
	// 배경
	// 몬스터
	// 등등등을 코드로 여기서 다 만들어야 한다.
}
