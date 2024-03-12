#pragma once

#include <EngineCore/EngineCore.h>
#include <EngineCore/Level.h>

class UEndingLevel : public ULevel
{
public:
	// constrcuter destructer
	UEndingLevel(); // 디폴트 생성자
	~UEndingLevel(); // 디폴트 소멸자

	// delete Function
	UEndingLevel(const UEndingLevel& _Other) = delete; // 디폴트 복사 생성자
	UEndingLevel(UEndingLevel&& _Other) noexcept = delete; 
	UEndingLevel& operator=(const UEndingLevel& _Other) = delete; // 디폴트 대입 연산자
	UEndingLevel& operator=(UEndingLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel)override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	FVector windowscale = GEngine->MainWindow.GetWindowScale(); // 윈도우창 크기 Get

	static bool LoadCheck;
};

