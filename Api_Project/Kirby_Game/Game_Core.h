#pragma once
#include <EngineCore\EngineCore.h>

class UGame_Core : public UEngineCore // 상속
{
public:
	
	// 클래스 디폴트
	UGame_Core(); // 디폴트 생성자
	~UGame_Core(); // 디폴트 소멸자

	UGame_Core(const UGame_Core& _Other) = delete;
	UGame_Core(UGame_Core&& _Other) noexcept = delete;
	UGame_Core& operator=(const UGame_Core& _Other) = delete;
	UGame_Core& operator=(UGame_Core&& _Other) noexcept = delete;

protected:
	// 오버라이드 
	void BeginPlay() override; // 시작
	void Tick(float _DeltaTime) override; // 업데이트
	void End() override; // 종료

private:

	// 윈도우창 크기 (X,Y)
	int windowX = 1000;
	int windowY = 700;

	// 윈도우창 위치 (X,Y)
	int positionX = 200;
	int positionY = 100;
};

