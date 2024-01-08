#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
USING_NS_CC;

// ���ο� �ִϸ��̼� ���¸� �˸��� �̺�Ʈ Ŭ����
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
    // ĳ������ �̵� ���¸� �����ϴ� enum
    enum class CharacterState {
        IDLE,
        MOVING_LEFT,
        MOVING_RIGHT
    };

public:
    Character();

    CREATE_FUNC(Character);
    // �ʱ�ȭ �Լ�
    virtual bool init();

    // ĳ���͸� ������ �ӵ��� �̵��ϴ� �Լ�
    void moveCharacter(float dt);

    virtual void update(float dt) override;

    void onMouseUp(EventMouse* event);

    //���콺�̺�Ʈ
    void onMouseDown(EventMouse* event);
    //ȭ�� ��ġ�̺�Ʈ
    bool onTouchBegan(Touch* touch, Event* event);

    // �÷��̾��� ������ ó�� �Լ�
    //void move(cocos2d::Vec2 direction);
    
    // �ִϸ��̼��� �����ϰ� �ִϸ��̼� ����Ʈ�� �߰��ϴ� �Լ�
    void createAnimation(const std::string& animationName, const std::string& fileName, int frameCount, float delay);

    // �ִϸ��̼� ���� �Լ�
    void playAnimation(const std::string& animationName);

    //�ִϸ��̼� ���� �Լ�
    //void animationBlending(const std::string& startAnimationName, const std::string& endAnimationName);

private:
    // �ִϸ��̼� ����Ʈ
    std::map<std::string, cocos2d::Animation*> animationList;

    // ���� �÷��� ���� �ִϸ��̼� �̸�
    std::string currentAnimation;

    Vec2 m_Targetposition;   
    Vec2 m_Direction; //����
    //���ϸ��̼� ����
    CharacterState  m_CharacterState;

};

#endif // 

