#pragma once
#include <EngineCore/Level.h>

class UTitleLevel : public ULevel
{
public:
	// constrcuter destructer
	UTitleLevel(); // 디폴트 생성자
	~UTitleLevel(); // 디폴트 소멸자

	// delete Function
	UTitleLevel(const UTitleLevel& _Other) = delete; // 디폴트 복사 생성자
	UTitleLevel(UTitleLevel&& _Other) noexcept = delete; 
	UTitleLevel& operator=(const UTitleLevel& _Other) = delete; // 디폴트 대입 연산자
	UTitleLevel& operator=(UTitleLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
private:
};

