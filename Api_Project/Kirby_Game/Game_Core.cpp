#include "Game_Core.h"
#include "Kirby_Player.h"
#include "TitleLevel.h"
#include "Stage1_Level.h"

#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

UGame_Core::UGame_Core()
	: UEngineCore()
{
}

UGame_Core::~UGame_Core()
{
}

// 게임시작
void UGame_Core::BeginPlay() // 
{
	MainWindow.SetWindowPosition({ 200,100 }); // 
	MainWindow.SetWindowScale({1080,810});
	UEngineCore::BeginPlay();
	// "Title Level" + "을 만들다가 에러가 났습니다";

	// 기본 커비 리소스만 여기다가 로드
	// 실행경로가 나와야 한다고 생각합니다.
	UEngineDirectory NewPath; // 현재 파일 경로

	// NewPath.Move("ContentsResources");
	NewPath.MoveParent(); // 현재 파일 경로의 상위 폴더로 이동

	// 커비의 기본 움직임 이미지는 모든 스테이지에서 사용하므로 코어에서 로드
	NewPath.Move("GameResources"); // 현재 폴더에서 다른 폴더로 이동
	NewPath.Move("kirby_resources"); // 
	NewPath.Move("kirby_Base"); // 


	// 확장자도 마찬가지 대소문자 구분을 무조건 대문자로 바꿔서 찾을것이다..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		//std::string FullPath = File.GetFullPath(); // 파일의 전체 경로
		// 싱글톤 잊지 말라고 일부러 GetInst를 사용하겠습니다.
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath()); // 로딩 -> Map(Iamges)
	}
	UEngineResourcesManager::GetInst().CuttingImage("kirby_Right.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby_Left.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby2_Right.png", 10, 7);
	UEngineResourcesManager::GetInst().CuttingImage("kirby2_Left.png", 10, 7);

	SetFrame(60); //-> 프로그래머가 컴퓨터 프레임을 고정시킬수 있다.
	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UStage1_Level>("Stage1_Level");
	ChangeLevel("TitleLevel");
	
}

void UGame_Core::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
	// 플레이어 움직여야 한다.
}

void UGame_Core::End()
{
	UEngineCore::End();
}