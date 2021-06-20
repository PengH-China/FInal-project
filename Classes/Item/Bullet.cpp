
#include "Bullet.h"


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
}





