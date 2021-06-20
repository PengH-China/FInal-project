#include "MonsterGroup.h"
#include "Role/Hero.h"
#include "GlobalPara/GlobalParameter.h"

extern Hero* globalHero;
const std::string MonsterBlueOne::m_StrMonsterAnmi = "monster/Monster01";
const std::string MonsterBlueOne::m_StrMonsterName = "monster/monster_0101.png";
const std::string MonsterFly::m_StrMonsterAnmi = "monster/Monster02";
const std::string MonsterFly::m_StrMonsterName = "monster/monster_0201.png";
const std::string MonsterCrawl::m_StrMonsterAnmi = "monster/Monster03";
const std::string MonsterCrawl::m_StrMonsterName = "monster/monster_0301.png";
const std::string MonsterBlueTwo::m_StrMonsterAnmi = "monster/Monster04";
const std::string MonsterBlueTwo::m_StrMonsterName = "monster/monster_0401.png";

void MonsterFly::update(float dt)
{
	auto monsterPos = this->getPosition() + this->getSprite()->getPosition();
	auto heroPos = globalHero->getPosition() + globalHero->getSprite()->getPosition();
	auto offset = heroPos - monsterPos;
	const float safeDistance = 20.f;
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
	else if ((offset.x < safeDistance && offset.y < safeDistance)
		|| (offset.x > -safeDistance && offset.y > -safeDistance)) {
		this->m_sprite->runAction(MoveBy::create(1.f,
			Vec2(-offset.x / 100.f, -offset.y / 100.f)));
		auto curTime = clock();
		if (static_cast<double>(curTime - m_lastShotTime) / CLOCKS_PER_SEC
	> 1)
		{
			Bullet* pBullet = MonsterBullet::create();
			this->getParent()->addChild(pBullet, 5);
			pBullet->setPosition(monsterPos);
			pBullet->setDamage(2);
			pBullet->attack(offset.x, offset.y, monsterPos, 0);
			m_lastShotTime = curTime;
		}
	}
	else {//the monster find the hero
		this->m_sprite->runAction(MoveBy::create(1.5f, Vec2(offset.x / 100.f, offset.y / 100.f)));
		//飞猪的特判：创建子弹不经过武器。
		auto curTime = clock();
		if (static_cast<double>(curTime - m_lastShotTime) / CLOCKS_PER_SEC
	> 1)
		{
			Bullet* pBullet = MonsterBullet::create();
			this->getParent()->addChild(pBullet, QS::kMonsterPriority);
			pBullet->setPosition(monsterPos);
			pBullet->setDamage(2);
			pBullet->attack(offset.x, offset.y, monsterPos, 0);
			m_lastShotTime = curTime;
		}
	}

	resetUI();
	judgeMonsterDie();

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

	genePhysicsBody(QS::kMonsterTag);
	setHealth(10);

	return true;
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

Animate* MonsterFly::createAnimate(const std::string pActionName)
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

void MonsterBlueOne::update(float dt)
{
	auto monsterPos = this->getPosition() + this->getSprite()->getPosition();
	auto heroPos = globalHero->getPosition() + globalHero->getSprite()->getPosition();
	auto offset = heroPos - monsterPos;
	const float safeDistance = 20.f;

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
		this->m_sprite->runAction(MoveBy::create(1.5f, Vec2(offset.x / 100.f, offset.y / 100.f)));
		//
		// 
		// 
		//
	}
	resetUI();
	judgeMonsterDie();
}

bool MonsterBlueOne::init()
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

	genePhysicsBody(QS::kMonsterTag);
	setHealth(10);

	return true;
}


MonsterBlueOne* MonsterBlueOne::createMonster(cocos2d::Point position)
{
	MonsterBlueOne* p_monsterBlueOne = new MonsterBlueOne();

	if (p_monsterBlueOne && p_monsterBlueOne->init())
	{
		p_monsterBlueOne->autorelease();
		p_monsterBlueOne->monsterPositionInit(position);
		return p_monsterBlueOne;
	}
	CC_SAFE_DELETE(p_monsterBlueOne);
	return NULL;
}

Animate* MonsterBlueOne::createAnimate(const std::string pActionName)
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
		("monster_010%d.png", i));
		if (nullptr == frame) {
			log("monster animation create failed!!,in monster.cpp line 307");
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

void MonsterCrawl::update(float dt)
{
	auto monsterPos = this->getPosition() + this->getSprite()->getPosition();
	auto heroPos = globalHero->getPosition() + globalHero->getSprite()->getPosition();
	auto offset = heroPos - monsterPos;
	const float safeDistance = 20.f;

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
	else if ((offset.x < safeDistance && offset.y < safeDistance)
		|| (offset.x > -safeDistance && offset.y > -safeDistance)) {
		this->m_sprite->runAction(MoveBy::create(1.f,
			Vec2(-offset.x / 100.f, -offset.y / 100.f)));
		auto curTime = clock();
		if (static_cast<double>(curTime - m_lastShotTime) / CLOCKS_PER_SEC
	> 1)
		{
			Bullet* pBullet = MonsterBullet::create();
			this->getParent()->addChild(pBullet, 5);
			pBullet->setPosition(monsterPos);
			pBullet->setDamage(2);
			pBullet->attack(offset.x, offset.y, monsterPos, 0);
			m_lastShotTime = curTime;
		}
	}
	else {//the monster find the hero
		this->m_sprite->runAction(MoveBy::create(1.5f, Vec2(offset.x / 100.f, offset.y / 100.f)));
		//飞猪的特判：创建子弹不经过武器。
		auto curTime = clock();
		if (static_cast<double>(curTime - m_lastShotTime) / CLOCKS_PER_SEC
	> 1)
		{
			Bullet* pBullet = MonsterBullet::create();
			this->getParent()->addChild(pBullet, QS::kMonsterPriority);
			pBullet->setPosition(monsterPos);
			pBullet->setDamage(2);
			pBullet->attack(offset.x, offset.y, monsterPos, 0);
			m_lastShotTime = curTime;
		}
	}

	resetUI();
	judgeMonsterDie();
}

bool MonsterCrawl::init()
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

	genePhysicsBody(QS::kMonsterTag);
	setHealth(10);

	return true;
}

MonsterCrawl* MonsterCrawl::createMonster(cocos2d::Point position)
{
	MonsterCrawl* p_monsterCrawl = new MonsterCrawl();

	if (p_monsterCrawl && p_monsterCrawl->init())
	{
		p_monsterCrawl->autorelease();
		p_monsterCrawl->monsterPositionInit(position);
		return p_monsterCrawl;
	}
	CC_SAFE_DELETE(p_monsterCrawl);
	return NULL;
}

Animate* MonsterCrawl::createAnimate(const std::string pActionName)
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
		("monster_030%d.png", i));
		if (nullptr == frame) {
			log("monster animation create failed!!");
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

void MonsterBlueTwo::update(float dt)
{
	auto monsterPos = this->getPosition() + this->getSprite()->getPosition();
	auto heroPos = globalHero->getPosition() + globalHero->getSprite()->getPosition();
	auto offset = heroPos - monsterPos;
	const float safeDistance = 20.f;

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
		this->m_sprite->runAction(MoveBy::create(1.5f, Vec2(offset.x / 100.f, offset.y / 100.f)));
		//
		// 
		//

	}

	resetUI();
	judgeMonsterDie();
}

bool MonsterBlueTwo::init()
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

	genePhysicsBody(QS::kMonsterTag);
	setHealth(10);

	return true;
}


MonsterBlueTwo* MonsterBlueTwo::createMonster(cocos2d::Point position)
{
	MonsterBlueTwo* p_monsterBlueTwo = new MonsterBlueTwo();

	if (p_monsterBlueTwo && p_monsterBlueTwo->init())
	{
		p_monsterBlueTwo->autorelease();
		p_monsterBlueTwo->monsterPositionInit(position);
		return p_monsterBlueTwo;
	}
	CC_SAFE_DELETE(p_monsterBlueTwo);
	return NULL;
}

Animate* MonsterBlueTwo::createAnimate(const std::string pActionName)
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
		("monster_040%d.png", i));
		if (nullptr == frame) {
			log("monster animation create failed!!");
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