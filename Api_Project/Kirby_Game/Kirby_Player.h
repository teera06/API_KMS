#pragma once
#include <EngineCore\Actor.h>

class Kirby_Player : public AActor
{
public:
	// constrcuter destructer
	Kirby_Player(); // 디폴트 생성자
	~Kirby_Player(); // 디폴트 소멸자

	// delete Function
	Kirby_Player(const Kirby_Player& _Other) = delete; // 디폴트 복사 생성자
	Kirby_Player(Kirby_Player&& _Other) noexcept = delete; 
	Kirby_Player& operator=(const Kirby_Player& _Other) = delete; // 디폴트 대입 연산자
	Kirby_Player& operator=(Kirby_Player&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
};

