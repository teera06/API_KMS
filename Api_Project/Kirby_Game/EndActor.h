#pragma once
class EndActor
{
public:
	// constrcuter destructer
	EndActor(); // 디폴트 생성자
	~EndActor(); // 디폴트 소멸자

	// delete Function
	EndActor(const EndActor& _Other) = delete; // 디폴트 복사 생성자
	EndActor(EndActor&& _Other) noexcept = delete; 
	EndActor& operator=(const EndActor& _Other) = delete; // 디폴트 대입 연산자
	EndActor& operator=(EndActor&& _Other) noexcept = delete;

protected:

private:
};

