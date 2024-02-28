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
	Flyfall,
	hit,
	Absorption,
	IceAttack,
	All_Attack,
	HeadDown,
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
	HPBar,
	HPgauge,
	State,
	Base,
	Ice,
	kirby,
	Menu,
};

enum class ECollisionOrder
{
	Monster,
	iceMonster,
	FireMonster,
	IceAttack,
	FireAttack,
	AllStar,
	kirby
};

enum class EIceOwner
{
	None,
	iceMonster,
	kirby
};