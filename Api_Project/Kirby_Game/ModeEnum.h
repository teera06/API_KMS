#pragma once

// Ŀ��� ���� ���� ����
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
	Object,
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
};

enum class ECollisionOrder
{
	Monster,
	iceMonster,
	FireMonster,
	SirMonster,
	MikeMonster,
	Hammer,
	IceBoxTop,
	IceBox,
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
	Boss,
	kirby
};

enum class ESirOwner
{
	None,
	SirMonster,
	kirby
};

