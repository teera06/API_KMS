#pragma once

// 커비와 몬스터 개념 공유
enum class EAMode
{
	Base,
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
	Absorption,
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
	Stage1_Map,
	Monster,
	Base,
	Fire,
	kirby,
};

enum class ECollisionOrder
{
	Monster,
	AllStar,
	kirby
};