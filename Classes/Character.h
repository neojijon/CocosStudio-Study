#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
USING_NS_CC;

class Character : public Sprite
{
public:
    CREATE_FUNC(Character);
    // �ʱ�ȭ �Լ�
    virtual bool init();

    // �÷��̾��� ������ ó�� �Լ�
    //void move(cocos2d::Vec2 direction);

};

#endif // 

