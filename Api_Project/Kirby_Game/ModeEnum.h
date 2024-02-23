#pragma once

// 커비와 몬스터 개념 공유
enum class EAMode
{
	Base,
	Ice,
	Fire,
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
	hit,
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
	HPBar,
	HP,
	HPgauge,
	State,
	Monster,
	Base,
	Ice,
	kirby,
};

enum class ECollisionOrder
{
	Monster,
	iceMonster,
	IceAttack,
	AllStar,
	kirby
};