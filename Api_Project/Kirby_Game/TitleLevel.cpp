#include "TitleLevel.h"
#include "TitleActor.h"

#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h> // Level 0 EngineDirectory
#include <EngineBase\EngineFile.h> // Level0 EngineFile

#include <EngineCore/EngineCore.h>

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();
	// �����ΰ� ���;� �Ѵٰ� �����մϴ�.
	UEngineDirectory NewPath; // ���� ���� ���
	FVector windowscale = GEngine->MainWindow.GetWindowScale();

	// NewPath.Move("ContentsResources");
	NewPath.MoveParent(); // ���� ���� ����� ���� ������ �̵�

	NewPath.Move("GameResources"); // ���� �������� �ٸ� ������ �̵�
	NewPath.Move("Title");


	// Ȯ���ڵ� �������� ��ҹ��� ������ ������ �빮�ڷ� �ٲ㼭 ã�����̴�..
	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath(); // ������ ��ü ���
		// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
		UEngineResourcesManager::GetInst().LoadImg(FullPath); // �ε� -> Map(Iamges)
	}

	SpawnActor<ATitleActor>()->SetActorLocation(windowscale.Half2D()); // Level ���� Actor ��ġ ���� ;
	
}
