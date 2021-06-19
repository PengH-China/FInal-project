
#include "Sword.h"
//#include "SwordBullet.h"

bool Sword::init()
{
	scheduleUpdate();

	auto listenerKeyboard = EventListenerKeyboard::create();
	//键盘事件响应函数
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Weapon::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Weapon::onKeyReleased, this);
	//注册键盘监听
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    log("Trying to create sword");
    Sprite* pSprite = Sprite::create("Item/Sword-1.png");
    m_pSpriteWeapon = pSprite;
    bindSprite(pSprite);
	generatePhysicalBody(QS::message::kSwordMessage, QS::kHeroSwordRestingTag);
    //逆时针旋转60度
    //pSprite->setRotation(-40.f);
	setWeaponName(QS::Name::kSwordWeapon);
    Weapon::setInterval(.2f);
    Weapon::setBulletCount(0);
    Weapon::setDamage(4);
	Weapon::setState(false);
	pSprite->setScale(0.6f);
    return true;
}

Bullet* Sword::createBullet()
{
    /*具体回调作用需要再检测一下可行性*/

    auto begin = CallFunc::create([&]() {
        //m_pSprite->setVisible(false);
		//m_pSprite->setTag(QS::kHeroSwordAttackingTag);
		generatePhysicalBody(QS::message::kSwordMessage, QS::kHeroSwordAttackingTag);
		});
    auto delay = DelayTime::create(0.9);
    auto end = CallFunc::create([&]() {
        //m_pSprite->setVisible(true);
		m_pSprite->setTag(QS::kHeroSwordRestingTag);
        });
    auto seq = Sequence::create(begin, delay, end, nullptr);
    //Bullet* pBullet = SwordBullet::create();
	m_pSprite->runAction(Spawn::create(seq, createAnimate("Sword1"), nullptr));

	auto pBullet = NormalBullet::create();
	//if (gIsEffectPlaying)
    //    AudioEngine::play2d(QS::files::kSwordAttack);
    return pBullet;
}

Animate* Sword::createAnimate(const std::string pActionName)
{
	/* 加载图片帧到缓存池 */
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Item/"+pActionName + ".plist","Item/"+ pActionName + ".png");

	int iFrameNum = 3;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	/* 用一个列表保存所有SpriteFrame对象 */
	for (int i = 1; i <= iFrameNum; i++) {
		/* 从SpriteFrame缓存池中获取SpriteFrame对象 */
		switch (100)
		{
		case QS::kUp:
			frame = frameCache->getSpriteFrameByName(StringUtils::format("W0%d.png", i));
			break;
		case QS::kDown:
			frame = frameCache->getSpriteFrameByName(StringUtils::format("S0%d.png", i));
			break;
		case QS::kRight:
			frame = frameCache->getSpriteFrameByName(StringUtils::format("D0%d.png", i));
			break;
		case QS::kLeft:
			frame = frameCache->getSpriteFrameByName(StringUtils::format("A0%d.png", i));
			break;
		default:
			frame = frameCache->getSpriteFrameByName(StringUtils::format("sword2-%d.png", i));
			log("sword picture ");
		}
		frameVec.pushBack(frame);
	}

	/* 使用SpriteFrame列表创建动画对象 */
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 0.1f, 1);

	animation-> setRestoreOriginalFrame(true);

	/* 将动画包装成一个动作 */
	Animate* action = Animate::create(animation);

	/*清除缓存*/
	AnimationCache::destroyInstance();
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
	//TextureCache::getInstance()->removeUnusedTextures();

	return action;
}