#pragma once
#include <EngineCore\Actor.h>

class Kirby_Player : public AActor
{
public:
	// constrcuter destructer
	Kirby_Player(); // ����Ʈ ������
	~Kirby_Player(); // ����Ʈ �Ҹ���

	// delete Function
	Kirby_Player(const Kirby_Player& _Other) = delete; // ����Ʈ ���� ������
	Kirby_Player(Kirby_Player&& _Other) noexcept = delete; 
	Kirby_Player& operator=(const Kirby_Player& _Other) = delete; // ����Ʈ ���� ������
	Kirby_Player& operator=(Kirby_Player&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
};

