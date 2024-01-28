#pragma once
#include <EngineCore\Actor.h>

enum class Mode
{
	Base,
	Fire,

};

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

	void InputTick(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	float QSkillCool = 0.0f;
	UImageRenderer* KirbyRenderer=nullptr;

	int RLpoint = 0; // 방향(왼쪽, 오른쪽 방향 전환) 체크 -> 발사 방향 
	int JumpKey = 0; // 점프키를 눌렀을때 할수 있는것 -> 공중부양
	float WalkSpeed = 100.0f; // 걷는 속도
	float RunSpeed = 200.0f; // 뛰는 속도

	Mode KirbyMode = Mode::Base;
};

