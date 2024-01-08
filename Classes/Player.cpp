#include "Player.h"

Player::Player()
{
}

bool Player::init()
{
	if (!Character::init())
	{
		return false;
	}
	// Idle 애니메이션 추가
	createAnimation("Idle", "Player/Idle/", 10, 0.1f);//0~10까지
	// Walk 애니메이션 추가
	createAnimation("Walking", "Player/Walking/", 22, 0.1f);//0~22까지
	// Run 애니메이션 추가
	createAnimation("Standing", "Player/Standing/", 8, 0.1f);
	// Jump 애니메이션 추가
	createAnimation("JumpUp", "player/JumpUp/", 5, 0.1f);
	// CrouchGrenade 애니메이션 추가
	createAnimation("CrouchGrenade", "player/CrouchGrenade/", 11, 0.1f);
	createAnimation("CrouchShoot", "player/CrouchShoot/", 11, 0.1f);
	createAnimation("Direction", "player/Direction/", 3, 0.1f);
	createAnimation("Grenade", "player/Grenade/", 6, 0.1f);
	createAnimation("Knife", "player/Knife/", 7, 0.1f);
	createAnimation("Reload", "player/Reload/", 18, 0.1f);
	createAnimation("Up", "player/Up/", 7, 0.1f);
	createAnimation("Victory", "player/Victory/", 6, 0.1f);
	createAnimation("Shooting", "player/Shooting/", 7, 0.1f);

	// 기본 애니메이션 설정
	playAnimation("Walking");

	return true;
}

// 플레이어의 움직임 처리 함수
void Player::move(cocos2d::Vec2 direction)
{
	// 플레이어를 주어진 방향으로 이동시키는 코드를 추가할 수 있습니다.
	// 플레이어를 주어진 방향으로 이동시키는 코드를 추가할 수 있습니다.

	// 예제로 Walk 애니메이션 플레이
	if (direction.length() > 0)
	{
		playAnimation("Walking");
	}
	else
	{
		playAnimation("Idle");
	}
}


