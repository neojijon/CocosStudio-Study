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



    //virtual void onEnter() override;



};

#endif // 

