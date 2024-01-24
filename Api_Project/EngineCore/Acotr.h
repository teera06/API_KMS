#pragma once
#include <EngineBase/FTransform.h>

class AAcotr
{
public:
	// constrcuter destructer
	AAcotr(); // 디폴트 생성자
	~AAcotr(); // 디폴트 소멸자

	// delete Function
	AAcotr(const AAcotr& _Other) = delete; // 디폴트 복사 생성자
	AAcotr(AAcotr&& _Other) noexcept = delete; 
	AAcotr& operator=(const AAcotr& _Other) = delete; // 디폴트 대입 연산자
	AAcotr& operator=(AAcotr&& _Other) noexcept = delete;


protected:

private:
	
};

