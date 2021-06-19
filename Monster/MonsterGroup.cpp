#include "MonsterGroup.h"
#include "Role/Hero.h"
//#include "GlobalPara/GlobalParameter.h"

extern Hero* pHero;
const std::string MonsterFly::m_StrMonsterAnmi = "monster/Monster02";
const std::string MonsterFly::m_StrMonsterName = "monster/monster_0201.png";

void MonsterFly::update(float dt)
{
	auto monsterPos = this->getPosition() + this->getSprite()->getPosition();
	auto heroPos = pHero->getPosition() + pHero->getSprite()->getPosition();
	auto offset = heroPos - monsterPos;
	/*log("monster: x:%f,y:%f", monsterPos.x, monsterPos.y);
	log("hero: x:%f,y:%f", heroPos.x, heroPos.y);
	log("offset: x:%f,y:%f",offset.x, offset.y);*/
	if (offset.x > 200.f || offset.y > 200.f || offset.x < -200.f || offset.y < -200.f) {
		auto randAction = createRandAction();//too far,so the monster random move
		if (randAction) {
			this->m_sprite->runAction(randAction);
			
		}
		else {
			log("create rand monster action failed");
		}
	}
	else {//the monster find the hero
		/*float speed = 2.f;
		const int distance = offset.length();
		const int duration = distance / speed;*/
		this->m_sprite->runAction(MoveBy::create(1.5f, Vec2(offset.x/100.f,offset.y/100.f)));
		//飞猪的特判：创建子弹不经过武器。
		auto curTime = clock();
		if (static_cast<double>(curTime - m_lastShotTime) / CLOCKS_PER_SEC
			> 1 )
		{
			Bullet* pBullet = MonsterBullet::create();
			this->getParent()->addChild(pBullet, 5);
			pBullet->setPosition(monsterPos);
			pBullet->attack(offset.x, offset.y, monsterPos, 0);
			m_lastShotTime = curTime;
		}
	}
	Vec2 Size = m_pMonsterSprite->getContentSize();
	m_pHealth->setPosition(m_pMonsterSprite->getPosition() + Vec2(0, 7));
	m_pHealth->setScale(Size.x / 355 * 1.5);
}
bool MonsterFly::init()
{
    if (!Monster::init()) {
        return false;
    }
	//create its animation
	m_pMoveAnimation = this->createAnimate();

   // m_pDieSprite = sk::files::kPigDie;
    this->setName(QS::Name::kMonster);

    auto sprite = Sprite::create(this->m_StrMonsterName);
	m_pMonsterSprite = sprite;

    bindSprite(sprite);
	m_sprite->runAction(m_pMoveAnimation);
   // this->move();//执行动画

    //generatePhysics(20.f);
    return true;
}

MoveBy* MonsterFly::createRandAction()
{
	int randomDirection = cocos2d::random(1, 4);
	static Vec2 offset(0, 0);//avoid create and release the offset frequently
	switch (randomDirection) {
		case 1: {
			offset.x = -5;
			offset.y = 0;
			break;
		}
		case 2: {
			offset.x = 5;
			offset.y = 0;
			break;
		}
		case 3: {
			offset.x = 0;
			offset.y = -5;
			break;
		}
		case 4: {
			offset.x = 0;
			offset.y = 5;
			break;
		}
	}
	auto finalPos = m_sprite->getPosition() + offset;
	if (finalPos.x < 0 || finalPos.y < 0 ||finalPos.x>1280||finalPos.y>960) {
		MoveBy* moveBy = MoveBy::create(1.5f, Vec2(0,0));
		offset.x = 0;
		offset.y = 0;
		moveBy->retain();
		return moveBy;
	}
	else {
		//log("action!");
		MoveBy* moveBy = MoveBy::create(2.5f, Vec2(offset.x, offset.y));
		offset.x = 0;
		offset.y = 0;
		moveBy->retain();
		return moveBy;
	}
	/*Vec2 Size = m_sprite->getContentSize();
	m_pHealth->setPosition(m_sprite->getPosition() + Vec2(0, 7));
	m_pHealth->setScale(Size.x / 355 * 1.5);*/

}

MonsterFly* MonsterFly::createMonster(cocos2d::Point position)
{
    MonsterFly* p_monsterFly = new MonsterFly();

    if (p_monsterFly && p_monsterFly->init())
    {
        p_monsterFly->autorelease();
        p_monsterFly->monsterPositionInit(position);
        return p_monsterFly;
    }
    CC_SAFE_DELETE(p_monsterFly);
    return NULL;
}

Animate* MonsterFly::createAnimate(const std::string pActionName )
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(pActionName + ".plist", pActionName + ".png");

	const int iFrameNum = 3;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	/* 用一个列表保存所有SpriteFrame对象 */
	for (int i = 1; i <= iFrameNum; i++) {
		/* 从SpriteFrame缓存池中获取SpriteFrame对象 */
		frame = frameCache->getSpriteFrameByName(StringUtils::format
		("monster_020%d.png", i));
		if (nullptr == frame) {
			log("monster animation create failed!!,in monster.cpp line 20");
		}
		else {
			frameVec.pushBack(frame);
		}
	}

	/* 使用SpriteFrame列表创建动画对象 */
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 0.2f, -1);
	/* 将动画包装成一个动作 */
	Animate* action = Animate::create(animation);
	/*清除缓存*/
	AnimationCache::destroyInstance();
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();

	return action;
}

void MonsterFly::move()
{
	
	if (pHero) {
		//auto heroPos = pHero->getPosition() + pHero->getSprite()->getPosition();
		auto heroPos = pHero->getPosition();
		//auto heroPos = pHero->getSprite()->getPosition();
		auto monsterPos = this->getPosition() + this->getSprite()->getPosition();
		//auto monsterPos =  this->getSprite()->getPosition();
		//auto monsterPos = this->getPosition();
		auto offset = heroPos - monsterPos;
		
		log("monster move:offset.x:%d,offset.y:%d", offset.x, offset.y);
		MoveBy* moveBy = MoveBy::create(1.5f, Vec2(offset.x, offset.y));
		this->m_sprite->runAction(moveBy);
	}
	else {
		log("the pHero is nullptr");
	}
}
