#pragma once
#include <EngineCore\Actor.h>

class ATitleAcotr : public AActor
{
public:
	// constrcuter destructer
	ATitleAcotr(); // ����Ʈ ������
	~ATitleAcotr(); // ����Ʈ �Ҹ���

	// delete Function
	ATitleAcotr(const ATitleAcotr& _Other) = delete; // ����Ʈ ���� ������
	ATitleAcotr(ATitleAcotr&& _Other) noexcept = delete; 
	ATitleAcotr& operator=(const ATitleAcotr& _Other) = delete; // ����Ʈ ���� ������
	ATitleAcotr& operator=(ATitleAcotr&& _Other) noexcept = delete;

protected:

private:
};

