/**
*@file Bullet.cpp
*@author 蔡明宏
*@date 5/26/2021
*/
#include "Bullet.h"

float Bullet::getSpeed()
{
    return m_bulletSpeed;
}

void Bullet::setSpeed(float speed)
{
    m_bulletSpeed = speed;
}

void Bullet::setDamage(int damage)
{
    damage = damage;
}

int Bullet::getDamage()
{
    return m_damage;
}

void Bullet::moveEnd()
{
    m_isArrive = true;
    this->removeAllChildrenWithCleanup(true);
    this->autorelease(); 
}

void Bullet::bindSprite(Sprite* pSprite, QS::Kind kind, QS::BulletShape shape, std::string name)
{
    PhysicsBody* body = nullptr;
    m_bulletSprite = pSprite;

    if (shape == QS::BulletShape::kCircle)
    {
        body = PhysicsBody::createCircle(m_bulletSprite->getContentSize().width / 2);
    }
    else if (shape == QS::BulletShape::kRectangle)
    {
        body = PhysicsBody::createBox(m_bulletSprite->getContentSize());
    }

    if (kind == QS::Kind::kSelf)
    {
        body->setCategoryBitmask(QS::bitMask::kSelfBulletCategory);
        body->setCollisionBitmask(QS::bitMask::kSelfBulletCollision);
        body->setContactTestBitmask(QS::bitMask::kSelfBulletContact);
        body->setRotationEnable(false);
        m_bulletSprite->setPhysicsBody(body);
    }
    else if (kind == QS::Kind::kMonster)
    {
        body->setCategoryBitmask(QS::bitMask::kMonsterBulletCategory);
        body->setCollisionBitmask(QS::bitMask::kMonsterBulletCollision);
        body->setContactTestBitmask(QS::bitMask::kMonsterBulletContact);
        body->setRotationEnable(false);
        m_bulletSprite->setPhysicsBody(body);
    }
    this->addChild(m_bulletSprite, 3, name);  
    //此处tag使用的string形式，且未赋初值，不知道能否使用
}





