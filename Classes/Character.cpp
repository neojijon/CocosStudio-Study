#include "Character.h"

// �ʱ�ȭ �Լ�
bool Character::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // �÷��̾� ��������Ʈ�� �߰��ϴ� �ڵ� ���� �߰��� �� �ֽ��ϴ�.

    return true;
}

//// �÷��̾��� ������ ó�� �Լ�
//void Character::move(cocos2d::Vec2 direction)
//{
//    // �÷��̾ �־��� �������� �̵���Ű�� �ڵ带 �߰��� �� �ֽ��ϴ�.
//}

