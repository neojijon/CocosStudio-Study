#include "Character.h"

Character::Character() : currentAnimation("")
{
}

// 초기화 함수
bool Character::init()
{
    if (!Sprite::init())
    {
        return false;
    }


	//auto listener = EventListenerTouchOneByOne::create(); //화면 터치	
	//listener->onTouchBegan = CC_CALLBACK_2(Character::onTouchBegan, this);

	auto listener = EventListenerMouse::create(); //마우스 이벤트
	//listener->onMouseDown = CC_CALLBACK_1(Character::onMouseDown, this);
	listener->onMouseUp = CC_CALLBACK_1(Character::onMouseUp, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	// 스케줄러를 이용하여 매 프레임마다 update 함수 호출
	schedule(CC_SCHEDULE_SELECTOR(Character::update));

    return true;
}

// 캐릭터를 일정한 속도로 이동하는 함수
void Character::moveCharacter(float dt) {

	float speed = 150.0f;  // 이동 속도 (픽셀/초)

	// 캐릭터의 현재 위치에서 목표 위치까지의 벡터 계산
	m_Direction = m_Targetposition - this->getPosition();

	// 이동 거리 계산
	float distance = m_Direction.length();

	if ( distance > 0.1f) {

		// 이동 벡터 정규화
		m_Direction.normalize();

		// 이동 속도에 delta time을 곱하여 이동 거리 계산
		float moveDistance = speed * dt;

		// 실제 이동 거리 계산
		float actualMoveDistance = std::min(moveDistance, distance);

		// 이동 벡터에 이동 거리를 곱하여 새로운 위치 계산
		Vec2 newPosition = this->getPosition() + m_Direction * actualMoveDistance;

		// 캐릭터 이동
		this->setPosition(newPosition);

		// 이동이 완료되면 목표 위치 초기화
		if (actualMoveDistance >= distance) {
			//m_Targetposition = Vec2::ZERO;

			// 캐릭터 상태를 IDLE로 변경
			m_CharacterState = CharacterState::IDLE;
			playAnimation("Idle");			
		}

		// 이동 방향에 따라 스프라이트의 방향 설정
		if (m_Direction.x > 0) {
			// 오른쪽으로 이동하는 경우
			this->setFlippedX(false);
		}
		else if (m_Direction.x < 0) {
			// 왼쪽으로 이동하는 경우
			this->setFlippedX(true);
		}
	}
}

// 매 프레임마다 호출되는 업데이트 함수
void Character::update(float dt) {
	// 캐릭터 이동 로직 호출
	moveCharacter(dt);
}

//최종 업그레이드
void Character::onMouseUp(EventMouse* event) {
		
	CCLOG("마우스 클릭이벤트 좌표: X:%f   , Y:%f", event->getCursorX(), event->getCursorY());
		
	//여러번 같은 값이 들어와서 막음.
	if ((m_Targetposition.x == event->getCursorX()) && (m_Targetposition.y == event->getCursorY()))
		return;

	// 마우스 클릭한 위치 저장
	m_Targetposition = Vec2(event->getCursorX(), event->getCursorY());

	// 캐릭터 상태를 이동 중으로 변경
	m_CharacterState = (m_Targetposition.x < this->getPositionX()) ? CharacterState::MOVING_LEFT : CharacterState::MOVING_RIGHT;

	playAnimation("Walking");
}


// 1. 단계
//void Character::onMouseUp(EventMouse* event) {
//
//	CCLOG("마우스 클릭이벤트 좌표: X:%f   , Y:%f", event->getCursorX(), event->getCursorY());
//		
//	//여러번 같은 값이 들어와서 막음.
//	if ((Targetpos.x == event->getCursorX()) && (Targetpos.y == event->getCursorY()))
//		return;
//
//
//	// 마우스 클릭한 위치로 이동하는 애니메이션 생성
//	float speed = 200.0f;  // 이동 속도 (픽셀/초)
//	Targetpos = Vec2(event->getCursorX(), event->getCursorY());
//
//	// 이동 거리 계산
//	float distance = this->getPosition().distance(Targetpos);
//
//	// 이동에 걸리는 시간 계산
//	float duration = distance / speed;
//
//	// MoveBy 액션을 사용하여 이동 애니메이션 생성
//	auto moveBy = MoveBy::create(duration, Targetpos - this->getPosition());
//	this->runAction(moveBy);
//}


void Character::onMouseDown(EventMouse* event) {

	CCLOG("마우스 클릭이벤트 좌표: X:%f   , Y:%f", event->getCursorX(), event->getCursorY());

	//여러번 같은 값이 들어와서 막음.
	if ((m_Targetposition.x == event->getCursorX()) && (m_Targetposition.y == event->getCursorY()))
		return;

	// 마우스 클릭한 위치 저장
	m_Targetposition = Vec2(event->getCursorX(), event->getCursorY());

	// 마우스 클릭한 위치로 이동하는 애니메이션 생성
	//auto moveTo = MoveTo::create(2.0f, Vec2(event->getCursorX(), event->getCursorY()));

	// 캐릭터의 현재 위치에서 마우스 클릭한 위치로 이동하는 애니메이션 실행
	//this->runAction(moveTo);
}


bool Character::onTouchBegan(Touch* touch, Event* event) {
	
	// 터치한 위치로 이동하는 애니메이션 생성
	auto moveTo = MoveTo::create(1.0f, touch->getLocation());

	// 캐릭터의 현재 위치에서 터치한 위치로 이동하는 애니메이션 실행
	this->runAction(moveTo);

	// 이동 애니메이션이 끝나면 캐릭터의 회전 애니메이션을 실행할 수도 있습니다.
	// 예를 들어, 아래의 코드는 캐릭터가 이동한 후에 360도 회전하는 애니메이션을 추가합니다.
	//auto rotateBy = RotateBy::create(1.0f, 360.0f);
	//this->runAction(Sequence::create(moveTo, rotateBy, nullptr));

	return true;
}



// 애니메이션 실행 함수
void Character::playAnimation(const std::string& animationName)
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

