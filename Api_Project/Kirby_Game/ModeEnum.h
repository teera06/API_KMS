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
	SirMonster,
	MikeMonster,
	SubBoss,
	SubBossAtt,
	MainBoss,
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