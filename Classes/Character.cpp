#include "Character.h"

Character::Character() : currentAnimation("")
{
}

// �ʱ�ȭ �Լ�
bool Character::init()
{
    if (!Sprite::init())
    {
        return false;
    }


	//auto listener = EventListenerTouchOneByOne::create(); //ȭ�� ��ġ	
	//listener->onTouchBegan = CC_CALLBACK_2(Character::onTouchBegan, this);

	auto listener = EventListenerMouse::create(); //���콺 �̺�Ʈ
	//listener->onMouseDown = CC_CALLBACK_1(Character::onMouseDown, this);
	listener->onMouseUp = CC_CALLBACK_1(Character::onMouseUp, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// �����ٷ��� �̿��Ͽ� �� �����Ӹ��� update �Լ� ȣ��
	schedule(CC_SCHEDULE_SELECTOR(Character::update));

    return true;
}

// ĳ���͸� ������ �ӵ��� �̵��ϴ� �Լ�
void Character::moveCharacter(float dt) {

	float speed = 150.0f;  // �̵� �ӵ� (�ȼ�/��)

	// ĳ������ ���� ��ġ���� ��ǥ ��ġ������ ���� ���
	m_Direction = m_Targetposition - this->getPosition();

	// �̵� �Ÿ� ���
	float distance = m_Direction.length();

	if ( distance > 0.1f) {

		// �̵� ���� ����ȭ
		m_Direction.normalize();

		// �̵� �ӵ��� delta time�� ���Ͽ� �̵� �Ÿ� ���
		float moveDistance = speed * dt;

		// ���� �̵� �Ÿ� ���
		float actualMoveDistance = std::min(moveDistance, distance);

		// �̵� ���Ϳ� �̵� �Ÿ��� ���Ͽ� ���ο� ��ġ ���
		Vec2 newPosition = this->getPosition() + m_Direction * actualMoveDistance;

		// ĳ���� �̵�
		this->setPosition(newPosition);

		// �̵��� �Ϸ�Ǹ� ��ǥ ��ġ �ʱ�ȭ
		if (actualMoveDistance >= distance) {
			//m_Targetposition = Vec2::ZERO;

			// ĳ���� ���¸� IDLE�� ����
			m_CharacterState = CharacterState::IDLE;
			playAnimation("Idle");			
		}

		// �̵� ���⿡ ���� ��������Ʈ�� ���� ����
		if (m_Direction.x > 0) {
			// ���������� �̵��ϴ� ���
			this->setFlippedX(false);
		}
		else if (m_Direction.x < 0) {
			// �������� �̵��ϴ� ���
			this->setFlippedX(true);
		}
	}
}

// �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ�
void Character::update(float dt) {
	// ĳ���� �̵� ���� ȣ��
	moveCharacter(dt);
}

//���� ���׷��̵�
void Character::onMouseUp(EventMouse* event) {
		
	CCLOG("���콺 Ŭ���̺�Ʈ ��ǥ: X:%f   , Y:%f", event->getCursorX(), event->getCursorY());
		
	//������ ���� ���� ���ͼ� ����.
	if ((m_Targetposition.x == event->getCursorX()) && (m_Targetposition.y == event->getCursorY()))
		return;

	// ���콺 Ŭ���� ��ġ ����
	m_Targetposition = Vec2(event->getCursorX(), event->getCursorY());

	// ĳ���� ���¸� �̵� ������ ����
	m_CharacterState = (m_Targetposition.x < this->getPositionX()) ? CharacterState::MOVING_LEFT : CharacterState::MOVING_RIGHT;

	playAnimation("Walking");
}


// 1. �ܰ�
//void Character::onMouseUp(EventMouse* event) {
//
//	CCLOG("���콺 Ŭ���̺�Ʈ ��ǥ: X:%f   , Y:%f", event->getCursorX(), event->getCursorY());
//		
//	//������ ���� ���� ���ͼ� ����.
//	if ((Targetpos.x == event->getCursorX()) && (Targetpos.y == event->getCursorY()))
//		return;
//
//
//	// ���콺 Ŭ���� ��ġ�� �̵��ϴ� �ִϸ��̼� ����
//	float speed = 200.0f;  // �̵� �ӵ� (�ȼ�/��)
//	Targetpos = Vec2(event->getCursorX(), event->getCursorY());
//
//	// �̵� �Ÿ� ���
//	float distance = this->getPosition().distance(Targetpos);
//
//	// �̵��� �ɸ��� �ð� ���
//	float duration = distance / speed;
//
//	// MoveBy �׼��� ����Ͽ� �̵� �ִϸ��̼� ����
//	auto moveBy = MoveBy::create(duration, Targetpos - this->getPosition());
//	this->runAction(moveBy);
//}


void Character::onMouseDown(EventMouse* event) {

	CCLOG("���콺 Ŭ���̺�Ʈ ��ǥ: X:%f   , Y:%f", event->getCursorX(), event->getCursorY());

	//������ ���� ���� ���ͼ� ����.
	if ((m_Targetposition.x == event->getCursorX()) && (m_Targetposition.y == event->getCursorY()))
		return;

	// ���콺 Ŭ���� ��ġ ����
	m_Targetposition = Vec2(event->getCursorX(), event->getCursorY());

	// ���콺 Ŭ���� ��ġ�� �̵��ϴ� �ִϸ��̼� ����
	//auto moveTo = MoveTo::create(2.0f, Vec2(event->getCursorX(), event->getCursorY()));

	// ĳ������ ���� ��ġ���� ���콺 Ŭ���� ��ġ�� �̵��ϴ� �ִϸ��̼� ����
	//this->runAction(moveTo);
}


bool Character::onTouchBegan(Touch* touch, Event* event) {
	
	// ��ġ�� ��ġ�� �̵��ϴ� �ִϸ��̼� ����
	auto moveTo = MoveTo::create(1.0f, touch->getLocation());

	// ĳ������ ���� ��ġ���� ��ġ�� ��ġ�� �̵��ϴ� �ִϸ��̼� ����
	this->runAction(moveTo);

	// �̵� �ִϸ��̼��� ������ ĳ������ ȸ�� �ִϸ��̼��� ������ ���� �ֽ��ϴ�.
	// ���� ���, �Ʒ��� �ڵ�� ĳ���Ͱ� �̵��� �Ŀ� 360�� ȸ���ϴ� �ִϸ��̼��� �߰��մϴ�.
	//auto rotateBy = RotateBy::create(1.0f, 360.0f);
	//this->runAction(Sequence::create(moveTo, rotateBy, nullptr));

	return true;
}



// �ִϸ��̼� ���� �Լ�
void Character::playAnimation(const std::string& animationName)
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




void Character::createAnimation(const std::string& animationName, const std::string& fileName, int frameCount, float delay)
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

