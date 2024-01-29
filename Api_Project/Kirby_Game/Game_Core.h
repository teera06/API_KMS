#pragma once
#include <EngineCore\EngineCore.h>

// ���� :
class Game_Core : public EngineCore
{
public:
	// constrcuter destructer
	Game_Core();
	~Game_Core();

	// delete Function
	Game_Core(const Game_Core& _Other) = delete;
	Game_Core(Game_Core&& _Other) noexcept = delete;
	Game_Core& operator=(const Game_Core& _Other) = delete;
	Game_Core& operator=(Game_Core&& _Other) noexcept = delete;

protected:
	// �θ��� 
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void End() override;

private:

};
