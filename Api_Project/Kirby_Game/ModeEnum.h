#pragma once

// Ŀ��� ���� ���� ����
enum class EAMode
{
	Base,
	Ice,
	Mike,
	Sword,
	Hammer,
};

enum class EActorState
{
	None,
	Idle,
	Walk,
	Run,
	Jump,
	FlyReady,
	Fly,
	fall,
	Absorption,
	IceAttack,
	All_Attack,
	HeadDown,
	CameraFreeMove,
	FreeMove,

};

enum class EActorDir
{
	Left,
	Right,
};

enum class ERenderOrder
{
	TitleMap,
	Log,
	Stage1_Map,
	Monster,
	Base,
	Ice,
	kirby,
};

enum class ECollisionOrder
{
	Monster,
	iceMonster,
	AllStar,
	kirby
};