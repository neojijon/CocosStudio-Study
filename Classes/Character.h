#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
USING_NS_CC;

// 새로운 애니메이션 상태를 알리는 이벤트 클래스
class AnimationStateChangedEvent : public EventCustom {
public:
    static const std::string EVENT_NAME;

    AnimationStateChangedEvent(const std::string& state)
        : EventCustom(EVENT_NAME), newState(state) {}

    std::string getNewState() const { return newState; }

private:
    std::string newState;
};

class Character : public Sprite
{
public:
    // 캐릭터의 이동 상태를 정의하는 enum
    enum class CharacterState {
        IDLE,
        MOVING_LEFT,
        MOVING_RIGHT
    };

public:
    Character();

    CREATE_FUNC(Character);
    // 초기화 함수
    virtual bool init();

    // 캐릭터를 일정한 속도로 이동하는 함수
    void moveCharacter(float dt);

    virtual void update(float dt) override;

    void onMouseUp(EventMouse* event);

    //마우스이벤트
    void onMouseDown(EventMouse* event);
    //화면 터치이벤트
    bool onTouchBegan(Touch* touch, Event* event);

    // 플레이어의 움직임 처리 함수
    //void move(cocos2d::Vec2 direction);
    
    // 애니메이션을 생성하고 애니메이션 리스트에 추가하는 함수
    void createAnimation(const std::string& animationName, const std::string& fileName, int frameCount, float delay);

    // 애니메이션 실행 함수
    void playAnimation(const std::string& animationName);

    //애니메이션 블랜딩 함수
    //void animationBlending(const std::string& startAnimationName, const std::string& endAnimationName);

private:
    // 애니메이션 리스트
    std::map<std::string, cocos2d::Animation*> animationList;

    // 현재 플레이 중인 애니메이션 이름
    std::string currentAnimation;

    Vec2 m_Targetposition;   
    Vec2 m_Direction; //방향
    //에니메이션 상태
    CharacterState  m_CharacterState;

};

#endif // 

