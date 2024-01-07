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
	playAnimation("Victory");

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

// 애니메이션 실행 함수
void Player::playAnimation(const std::string& animationName)
{
	if (currentAnimation == animationName)
	{
		// 이미 플레이 중인 애니메이션이라면 중복 실행하지 않음
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


