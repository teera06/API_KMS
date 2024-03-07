#pragma once

// 커비와 몬스터 개념 공유
enum class EAMode
{
	Base,
	Ice,
	Fire,
	Mike,
	Sir,
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
	SirJump,
	FlyReady,
	Fly,
	Flyfall,
	hit,
	Absorption,
	IceAttack,
	FireReady,
	FireAttack,
	SirAttack,
	MikeAttack,
	HammerAttack,
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
	Stage3_Map,
	Last_Map,
	Monster,
	Hammer,
	Base,
	Ice,
	Sir,
	Fire,
	Sound,
	Bullet,
	kirby,
	HPBar,
	HPgauge,
	State,
	effect,
	Menu,
};

enum class ECollisionOrder
{
	Monster,
	iceMonster,
	FireMonster,
	SirMonster,
	MikeMonster,
	Hammer,
	SubBoss,
	MainBoss,
	SubBossAtt,
	MainBossAtt,
	IceAttack,
	FireAttack,
	SirAttack,
	MikeAttack,
	AllStar,
	kirby
};

enum class EIceOwner
{
	None,
	iceMonster,
	kirby
};

enum class ESirOwner
{
	None,
	SirMonster,
	kirby
};

