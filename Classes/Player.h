#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include "Character.h"
USING_NS_CC;

class Player : public Character
{
public :	
	CREATE_FUNC(Player);
    
    Player();

public :
    // �ʱ�ȭ �Լ�
    virtual bool init();

    // �÷��̾��� ������ ó�� �Լ�
    void move(cocos2d::Vec2 direction);

    // �ִϸ��̼� ���� �Լ�
    void playAnimation(const std::string& animationName);

    //virtual void onEnter() override;


private:
    // �ִϸ��̼� ����Ʈ
    std::map<std::string, cocos2d::Animation*> animationList;

    // ���� �÷��� ���� �ִϸ��̼� �̸�
    std::string currentAnimation;

    // �ִϸ��̼��� �����ϰ� �ִϸ��̼� ����Ʈ�� �߰��ϴ� �Լ�
    void createAnimation(const std::string& animationName, const std::string& fileName, int frameCount, float delay);

};

#endif // 

