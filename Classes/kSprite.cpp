#include "kSprite.h"
//#include "bzStateGame.h"
#include "MapScene.h"

//#include "UtilsGL.h"
//#include "ProgramGL.h"
#include "renderer/backend/Types.h"
//#include <kComm.h>


bool kSprite::init()
{
    frm = 0;
    ori = getTextureRect();
    ori.size = getContentSize();
    return true;
}

kSprite* kSprite::create(const std::string& filename)
{
    kSprite *sprite = new (std::nothrow) kSprite();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->init();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

kSprite* kSprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
    kSprite *sprite = new (std::nothrow) kSprite();
    if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->init();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

kSprite* kSprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
    CCASSERT(frame != nullptr, msg);
#endif
    
    return createWithSpriteFrame(frame);
}

kSprite* kSprite::createWithTexture(Texture2D *texture)
{
    kSprite *sprite = new (std::nothrow) kSprite();
    if (sprite && sprite->initWithTexture(texture))
    {
        sprite->init();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void kSprite::setVisible(bool bVisible)
{
    Node::setVisible(bVisible);
    if (!bVisible) {
        frm = 0;
    }
}


void kSprite::drawPos(Vec2 pos) {
    drawPos(pos, Color4F(1,1,1,1), 0, 1.0, 0, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, Color4F color) {
    drawPos(pos, color, 0, 1.0, 0, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, int img_d, float img_s) {
    drawPos(pos, Color4F(1,1,1,1), img_d, img_s, 0, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, int img_d, int drawType, float img_s) {
    drawPos(pos, Color4F(1,1,1,1), img_d, img_s, drawType, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, Color4F color, int img_d, float img_s) {
    drawPos(pos, color, img_d, img_s, 0, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, Color4F color, int drawType) {
    drawPos(pos, color, 0, 1.0, drawType, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, int img_d, float img_s, int drawType) {
    drawPos(pos, Color4F(1,1,1,1), img_d, img_s, drawType, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, Color4F color, int img_d, float img_s, int drawType, int cx, int cy, float rotate) {
    if (isVisible()) {
        int tag = getTag();
        if (++frm >= MAX_FRM) {
            log("error kSprite: over frame!");
            return;
        }
        auto pa = (MapScene*) getParent();
        auto spr = pa->getSprite(GETT_TYPE(tag), GETT_IDX(tag), GETT_FRM(tag)+frm, this);
        spr->drawPos(pos, color, img_d, img_s, drawType, cx, cy, rotate);
        return;
    }

    setVisible(true);
    setColor(Color3B(color));
    setOpacity(color.a*255);
    setAnchorPoint(Vec2(0,1));
    setFlippedX(img_d==1);
    setScale(img_s, img_s);
    setRotation(0);
    if (rotate != 0) {
        float x = pos.x - cx;
        float y = pos.y - cy;
        pos.x = x * cosf(rotate) - y * sinf(rotate) + cx;
        pos.y = x * sinf(rotate) + y * cosf(rotate) + cy;
        setRotation(RAD2DEG(rotate));
    }
    if (drawType != 0) {//À½???
        BlendFunc blend;
        switch(drawType) {
        case 1:                    
            blend.src = backend::BlendFactor::DST_ALPHA;
            blend.dst = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
            break;
        case 2:
            blend.src = backend::BlendFactor::DST_ALPHA;
            blend.dst = backend::BlendFactor::ONE;
            break;
        default:
            blend.src = backend::BlendFactor::SRC_ALPHA;
            blend.dst = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
            break;
        }
        setBlendFunc(blend);
    }

    convertScreenCoord(pos);
    setPosition(pos);
    setLocalZOrder(zorder++);
}

void kSprite::convertScreenCoord(Vec2& pos)
{
    convertScreenCoord(pos.x, pos.y);
}

void kSprite::convertScreenCoord(float& x, float& y)   //old screen -> cocos screen
{
    //x *= TOUCH_SCALE;
    //y = SCREEN_HEIGHT - y*TOUCH_SCALE;
    y = SCREEN_HEIGHT - y;
}

void kSprite::drawPos(Vec2 pos, int tx, int ty, int tw, int th) {
    drawPos(pos, tx, ty, tw, th, Color4F(1,1,1,1), 0, 1.0, 0, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, int tx, int ty, int tw, int th, float img_s) {
    drawPos(pos, tx, ty, tw, th, Color4F(1,1,1,1), 0, img_s, 0, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, int tx, int ty, int tw, int th, int drawType) {
    drawPos(pos, tx, ty, tw, th, Color4F(1,1,1,1), 0, 1.0, drawType, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, int tx, int ty, int tw, int th, float img_s, int drawType) {
    drawPos(pos, tx, ty, tw, th, Color4F(1,1,1,1), 0, img_s, drawType, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, int tx, int ty, int tw, int th, Color4F color, int img_d, float img_s) {
    drawPos(pos, tx, ty, tw, th, color, img_d, img_s, 0, 0, 0, 0);
}

void kSprite::drawPos(Vec2 pos, int tx, int ty, int tw, int th, Color4F color, int img_d, float img_s, int drawType, int cx, int cy, float rotate) {
    if (isVisible()) {
        int tag = getTag();
        if (++frm >= MAX_FRM) {
            log("error kSprite: over frame!");
            return;
        }
        auto pa = (MapScene*) getParent();
        auto spr = pa->getSprite(GETT_TYPE(tag), GETT_IDX(tag), GETT_FRM(tag)+frm, this);
        spr->drawPos(pos, tx, ty, tw, th, color, img_d, img_s, drawType, cx, cy, rotate);
        return;
    }

    setTextureRect(Rect(ori.origin.x+tx,ori.origin.y+ty,tw,th));
    drawPos(pos, color, img_d, img_s, drawType, cx, cy, rotate);
}

//////////////////////////////////////////////////////////////////////////////////////////
//void kSprite::drawRect(Rect rect) {
//    drawRect(rect, Color4F(1,1,1,1));
//}
//
//void kSprite::drawRect(Rect rect, Color4F color) {
//}
