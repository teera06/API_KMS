#pragma once
class SubBoss
{
public:
	// constrcuter destructer
	SubBoss(); // 디폴트 생성자
	~SubBoss(); // 디폴트 소멸자

	// delete Function
	SubBoss(const SubBoss& _Other) = delete; // 디폴트 복사 생성자
	SubBoss(SubBoss&& _Other) noexcept = delete; 
	SubBoss& operator=(const SubBoss& _Other) = delete; // 디폴트 대입 연산자
	SubBoss& operator=(SubBoss&& _Other) noexcept = delete;

protected:

private:
};

