#include "Player.h"

Player::Player(): currentAnimation("")
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
	playAnimation("Victory");

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

// �ִϸ��̼� ���� �Լ�
void Player::playAnimation(const std::string& animationName)
{
	if (currentAnimation == animationName)
	{
		// �̹� �÷��� ���� �ִϸ��̼��̶�� �ߺ� �������� ����
		return;
	}

	auto animation = animationList.find(animationName);
	if (animation != animationList.end())
	{
		this->stopAllActions();
		auto animate = cocos2d::Animate::create(animation->second);
		this->runAction(cocos2d::RepeatForever::create(animate));
		currentAnimation = animationName;
	}
}



void Player::createAnimation(const std::string& animationName, const std::string& fileName, int frameCount, float delay)
{
	auto animation = cocos2d::Animation::create();
	animation->setDelayPerUnit(delay);

	for (int i = 0; i <= frameCount; ++i)
	{
		std::string frameName = fileName + std::to_string(i) + ".png";
		animation->addSpriteFrameWithFile(frameName);
	}

	animation->setRestoreOriginalFrame(true);
	animation->retain();

	animationList[animationName] = animation;
}


