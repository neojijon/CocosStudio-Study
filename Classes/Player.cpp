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
	// Idle �ִϸ��̼� �߰�
	createAnimation("Idle", "Player/Idle/", 10, 0.1f);//0~10����
	// Walk �ִϸ��̼� �߰�
	createAnimation("Walking", "Player/Walking/", 22, 0.1f);//0~22����
	// Run �ִϸ��̼� �߰�
	createAnimation("Standing", "Player/Standing/", 8, 0.1f);
	// Jump �ִϸ��̼� �߰�
	createAnimation("JumpUp", "player/JumpUp/", 5, 0.1f);
	// CrouchGrenade �ִϸ��̼� �߰�
	createAnimation("CrouchGrenade", "player/CrouchGrenade/", 11, 0.1f);
	createAnimation("CrouchShoot", "player/CrouchShoot/", 11, 0.1f);
	createAnimation("Direction", "player/Direction/", 3, 0.1f);
	createAnimation("Grenade", "player/Grenade/", 6, 0.1f);
	createAnimation("Knife", "player/Knife/", 7, 0.1f);
	createAnimation("Reload", "player/Reload/", 18, 0.1f);
	createAnimation("Up", "player/Up/", 7, 0.1f);
	createAnimation("Victory", "player/Victory/", 6, 0.1f);
	createAnimation("Shooting", "player/Shooting/", 7, 0.1f);

	// �⺻ �ִϸ��̼� ����
	playAnimation("Walking");

	return true;
}

// �÷��̾��� ������ ó�� �Լ�
void Player::move(cocos2d::Vec2 direction)
{
	// �÷��̾ �־��� �������� �̵���Ű�� �ڵ带 �߰��� �� �ֽ��ϴ�.
	// �÷��̾ �־��� �������� �̵���Ű�� �ڵ带 �߰��� �� �ֽ��ϴ�.

	// ������ Walk �ִϸ��̼� �÷���
	if (direction.length() > 0)
	{
		playAnimation("Walking");
	}
	else
	{
		playAnimation("Idle");
	}
}


