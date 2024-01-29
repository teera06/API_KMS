#pragma once
#include "ModeEnum.h"

class Monster_Base
{
public:
	// constrcuter destructer
	Monster_Base(); // ����Ʈ ������
	~Monster_Base(); // ����Ʈ �Ҹ���

	// delete Function
	Monster_Base(const Monster_Base& _Other) = delete; // ����Ʈ ���� ������
	Monster_Base(Monster_Base&& _Other) noexcept = delete; 
	Monster_Base& operator=(const Monster_Base& _Other) = delete; // ����Ʈ ���� ������
	Monster_Base& operator=(Monster_Base&& _Other) noexcept = delete;

protected:

private:

	Mode MonsterBase = Mode::Base;
};

