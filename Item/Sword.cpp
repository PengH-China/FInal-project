
#include "Sword.h"
//#include "SwordBullet.h"

Bullet* Sword::createBullet()
{
    return nullptr;
}

bool Sword::init()
{
    log("Trying to create sword");
    Sprite* pSprite = Sprite::create("item/sword.png");
    m_pSpriteWeapon = pSprite;
    bindSprite(pSprite);
    generatePhysicalBody(QS::message::kSwordMessage, QS::Name::kSwordWeapon);
    //��ʱ����ת60��
    pSprite->setRotation(-60.f); 
    setInterval(.2f);
    setBulletCount(0);
    setDamage(4);
    return true;
}

//Bullet* Sword::createBullet()
//{
//    /*����ص�������Ҫ�ټ��һ�¿�����*/
//    auto begin = CallFunc::create([&]() {
//        m_pSprite->setVisible(false);
//        });
//    auto delay = DelayTime::create(0.9);
//    auto end = CallFunc::create([&]() {
//        m_pSprite->setVisible(true);
//        });
//    auto seq = Sequence::create(begin, delay, end, nullptr);
//    Bullet* pBullet = SwordBullet::create();
//    m_pSprite->runAction(seq);
//    //if (gIsEffectPlaying)
//    //    AudioEngine::play2d(QS::files::kSwordAttack);
//    return pBullet;
//}