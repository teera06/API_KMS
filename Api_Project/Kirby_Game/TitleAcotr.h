#pragma once
#include <EngineCore\Actor.h>

class ATitleAcotr : public AActor
{
public:
	// constrcuter destructer
	ATitleAcotr(); // 디폴트 생성자
	~ATitleAcotr(); // 디폴트 소멸자

	// delete Function
	ATitleAcotr(const ATitleAcotr& _Other) = delete; // 디폴트 복사 생성자
	ATitleAcotr(ATitleAcotr&& _Other) noexcept = delete; 
	ATitleAcotr& operator=(const ATitleAcotr& _Other) = delete; // 디폴트 대입 연산자
	ATitleAcotr& operator=(ATitleAcotr&& _Other) noexcept = delete;

protected:

private:
};

