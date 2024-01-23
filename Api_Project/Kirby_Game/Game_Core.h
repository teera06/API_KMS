#pragma once
// ������ ���� -> ���� ���� ����
#include <EngineCore\EngineCore.h>

class Game_Core :public EngineCore
{
public:
	// constrcuter destructer
	Game_Core(); // ����Ʈ ������
	~Game_Core(); // ����Ʈ �Ҹ���

	// delete Function
	Game_Core(const Game_Core& _Other) = delete; // ����Ʈ ���� ������
	Game_Core(Game_Core&& _Other) noexcept = delete; 
	Game_Core& operator=(const Game_Core& _Other) = delete; // ����Ʈ ���� ������
	Game_Core& operator=(Game_Core&& _Other) noexcept = delete;

protected:
	
	// ���� ���� ��Ʈ���� ���� ����
	void EngineStart() override;
	void EngineUpdate() override;
	void EngineEnd() override;
private:
};

