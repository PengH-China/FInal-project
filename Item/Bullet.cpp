/**
*@file Bullet.cpp
*@author 蔡明宏
*@date 5/26/2021
*/
#include "Bullet.h"

void Bullet::moveEnd()
{
    m_isArrive = true;
    this->removeAllChildrenWithCleanup(true);
    this->autorelease(); 
}

void Bullet::bindSprite(Sprite* pSprite, QS::Kind kind, QS::BulletShape shape, std::string name)
{
    PhysicsBody* body = nullptr;
    m_pBulletSprite = pSprite;

    if (shape == QS::BulletShape::kCircle)
    {
        body = PhysicsBody::createCircle(m_pBulletSprite->getContentSize().width / 2);
    }
    else if (shape == QS::BulletShape::kRectangle)
    {
        body = PhysicsBody::createBox(m_pBulletSprite->getContentSize());
    }

    if (kind == QS::Kind::kSelf)
    {
        body->setCategoryBitmask(1);
        body->setCollisionBitmask(1);
        body->setContactTestBitmask(1);
        body->setRotationEnable(false);
        m_pBulletSprite->setTag(QS::kHeroBulletTag);
        m_pBulletSprite->setPhysicsBody(body);
    }
    else if (kind == QS::Kind::kMonster)
    {
        body->setCategoryBitmask(1);
        body->setCollisionBitmask(1);
        body->setContactTestBitmask(1);
        body->setRotationEnable(false);
        m_pBulletSprite->setTag(QS::kMonsterBulletTag);
        m_pBulletSprite->setPhysicsBody(body);
    }
    this->addChild(m_pBulletSprite, QS::kBulletPriority, name);  
    //此处tag使用的string形式，且未赋初值，不知道能否使用
}





