#pragma once
#include <EngineBase/FTransform.h>

class AAcotr
{
public:
	// constrcuter destructer
	AAcotr(); // ����Ʈ ������
	~AAcotr(); // ����Ʈ �Ҹ���

	// delete Function
	AAcotr(const AAcotr& _Other) = delete; // ����Ʈ ���� ������
	AAcotr(AAcotr&& _Other) noexcept = delete; 
	AAcotr& operator=(const AAcotr& _Other) = delete; // ����Ʈ ���� ������
	AAcotr& operator=(AAcotr&& _Other) noexcept = delete;


protected:

private:
	
};

