#pragma once
#include <EngineCore\Actor.h>

#include "ActorCommon.h"
#include "ModeEnum.h"

#include "Kirby_Player.h"


class Apengi_Ice : public AActor, public ActorCommon
{
public:
	// constrcuter destructer
	Apengi_Ice(); // 디폴트 생성자
	~Apengi_Ice(); // 디폴트 소멸자

	// delete Function
	Apengi_Ice(const Apengi_Ice& _Other) = delete; // 디폴트 복사 생성자
	Apengi_Ice(Apengi_Ice&& _Other) noexcept = delete; 
	Apengi_Ice& operator=(const Apengi_Ice& _Other) = delete; // 디폴트 대입 연산자
	Apengi_Ice& operator=(Apengi_Ice&& _Other) noexcept = delete;
	void IceState();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImageRenderer* PengiRenderer = nullptr; // 커비 랜더링 (이미지)
	UCollision* PengiCollision = nullptr;

	AKirby_Player* Player = AKirby_Player::GetMainPlayer();
	
	FVector DirMonster = FVector::Left;
	FVector IceMove = FVector::Zero; // 얼음 이동 관련 공통 
	void AniCreate();
	void BaseMove(float _DeltaTime);
	const float sight = 250.0f; // 몬스터 시야
	bool IsIce = false; // 언 상태 인지 bool값 공통
	int checkX = 0; // 벽에 충돌할때 X축 범위
	float MoveSpeed = 30.0f; // 몬스터 공통 스피드
	const float IceSpeed = 200.0f; // 얼음(얼려진 후) 이동 스피드
};

