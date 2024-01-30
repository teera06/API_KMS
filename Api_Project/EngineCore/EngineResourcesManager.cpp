#include "EngineResourcesManager.h"
#include <EnginePlatform\WindowImage.h> // Level2 WindowImage
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineDebug.h>
#include "EngineCore.h"
#include "EngineBase\EngineDebug.h"

//UEngineResourcesManager UEngineResourcesManager::Inst;
//UEngineResourcesManager* UEngineResourcesManager::pInst = nullptr;

UEngineResourcesManager::UEngineResourcesManager()
{
}

UEngineResourcesManager::~UEngineResourcesManager() // 소멸자에서 릭 정리
{
	for (std::pair<const std::string, UWindowImage*>& Pair : Images)
	{
		delete Pair.second;
		Pair.second = nullptr;
	}

	Images.clear();
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path)
{
	UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
	std::string FileName = NewPath.GetFileName();
	return LoadImg(_Path, FileName);
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path, std::string_view _Name)
{
	// 모든 이름은 대문자로
	std::string UpperName = UEngineString::ToUpper(_Name); // 대문자 변환

	if (true == Images.contains(UpperName)) // Map(Images) -> 이미 존재하는 경우 -> 에러 처리
	{
		// 에디터 모드나 디버그에서는 속력을 따질필요가 없다.
		// 게임에서 실제 실행되지 않을 내용에 대해서는 속력을 따지지 않는다.
		MsgBoxAssert(std::string("경로 : ") + std::string(_Path) + "파일명 : " + std::string(_Name) + "이미 로드한 파일을 또 로드하려고 했습니다");
		return nullptr;
	}

	// (자식)UWindowImage <-UPathObject <- UNameObject(부모)
	UWindowImage* NewImage = new UWindowImage(); // 동적할당
	NewImage->SetName(UpperName); // 파일이름 -> Level0 (NameObject)
	NewImage->SetPath(_Path); // 경로 -> Level0 (PathObject)
	NewImage->Load(GEngine->MainWindow.GetWindowImage()); // Level1 (WindowImage), 확장자에 따른 이미지 로드 준비() 더 확인하기

	// .Png .bmp => 확장자만 바꾸면 png가 bmp가 된다고 생각했던 학생이 있었는데 아닙니다.
	// 제대로 이미지 편집 프로그램에서 포맷을 변경하고 저장하셔야 합니다.
	// 일단 winapi는 기본적으로 png를 출력하는 함수를 지원하지 않습니다.
	// 무조건 bmp만 됩니다.
	// .Png를 로드해서 bmp로 변경해서 출력할 겁니다. => 처음합니다.
	// 그래서 Png를 출력하는것도 아니고 부분 반투명
	Images[UpperName] = NewImage; // Map(Images) 에서 관리

	return nullptr;

}

UWindowImage* UEngineResourcesManager::FindImg(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name); // 소문자 -> 대문자 변환 -> 이유: 비교시 대문자 통일

	if (false == Images.contains(UpperName)) // Map에서 관리하는 파일이 존재하지 않은 경우
	{
		MsgBoxAssert("파일명 : " + std::string(_Name) + "은 존재하지 않는 이미지입니다");
		return nullptr; // 리턴
	}

	return Images[UpperName]; // Map에 존재하는 파일명을 리턴
}