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
	Stop,
	Jump,
	FlyReady,
	Fly,
	Flyfall,
	hit,
	Absorption,
	IceAttack,
	FireReady,
	FireAttack,
	All_Attack,
	HeadDown,
};

enum class EActorDir
{
	None,
	Left,
	Right,
};

enum class ERenderOrder
{
	TitleMap,
	Log,
	Stage1_Map,
	Stage2_Map,
	Monster,
	HPBar,
	HPgauge,
	State,
	Base,
	Ice,
	Fire,
	kirby,
	effect,
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