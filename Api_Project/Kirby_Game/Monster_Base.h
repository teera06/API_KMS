#pragma once
#include "ModeEnum.h"

class Monster_Base
{
public:
	// constrcuter destructer
	Monster_Base(); // 디폴트 생성자
	~Monster_Base(); // 디폴트 소멸자

	// delete Function
	Monster_Base(const Monster_Base& _Other) = delete; // 디폴트 복사 생성자
	Monster_Base(Monster_Base&& _Other) noexcept = delete; 
	Monster_Base& operator=(const Monster_Base& _Other) = delete; // 디폴트 대입 연산자
	Monster_Base& operator=(Monster_Base&& _Other) noexcept = delete;

protected:

private:

	Mode MonsterBase = Mode::Base;
};

