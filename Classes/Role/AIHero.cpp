/**
*@file Hero.cpp
*@author 张子涵(Zhang Zihan),蔡明宏,彭浩
*@time 2021-06-11
*/
#include "AIHero.h"


AIHero* AIHero::createAIHero(Point position,std::string pName)
{
	AIHero* aihero = new AIHero();
	if (aihero && aihero->init(position,  pName))
	{
		aihero->autorelease();
		return aihero;
	}
	CC_SAFE_DELETE(aihero); 
	return NULL;
}

bool AIHero::init(Point position, std::string pName)
{


	if (!Monster::init())
	{
		return false;
	}
	
	setM_nowFacing(3);

	setHealth(10);
	setMaxHealth(10);

	this->setName(QS::Name::kMonster);
	setHeroSpriteName(pName);

	soldierPositionInit(position);
	m_pBackground->setScale(0.08f);
	m_pHealth->setScale(0.08f);

	schedule(CC_SCHEDULE_SELECTOR(AIHero::scheduleUpdateAIHero), 0.5f);

	return true;
}

void AIHero::setHeroSpriteName(std::string pName)
{
	this->m_pHeroSpriteName = pName;
	return;
}

std::string AIHero::getHeroSpriteName()
{
	return m_pHeroSpriteName;
}



void AIHero::soldierPositionInit(cocos2d::Point position)
{
	m_pHeroSprite = Sprite::create("Hero/" + m_pHeroSpriteName + ".png");
	m_pHeroSprite->setScale(2.0f);
	//m_pHeroSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->bindSprite(m_pHeroSprite);
	m_pMonsterSprite = m_pHeroSprite;

	genePhysicsBody(QS::kMonsterTag);

	auto* weapon = NormalGun::create();
	if (weapon == nullptr) {
		log("the weapon can't be created");
	}
	this->setMainWeapon(weapon);
}
void AIHero::setMainWeapon(Weapon* pWeapon)
{
	this->m_pHeroSprite->addChild(pWeapon, 2);
	pWeapon->setState(true);
	//pWeapon->setAnchorPoint(Vec2(0.5,0.5));
	pWeapon->setPosition(Point(m_pHeroSprite->getContentSize().width / 4, m_pHeroSprite->getContentSize().height) / 4);
	/*auto w = m_pHeroSprite->getContentSize().width;
	auto h = m_pHeroSprite->getContentSize().height;
	pWeapon->setPosition(w/2,h/2);*/
	pWeapon->setScale(1.0f,1.0f);
	m_pMainWeapon = pWeapon;
	log("Weapon set!!");
}



Weapon* AIHero::getMainWeapon()
{
	return m_pMainWeapon;
}


void AIHero::scheduleUpdateAIHero(float dt) {//detect every seconds what have done
	auto monsterPos = this->getPosition() + this->Monster::getSprite()->getPosition();
	auto heroPos = globalHero->getPosition() + globalHero->getSprite()->getPosition();
	auto offset = heroPos - monsterPos;
	/*log("monster: x:%f,y:%f", monsterPos.x, monsterPos.y);
	log("hero: x:%f,y:%f", heroPos.x, heroPos.y);
	log("offset: x:%f,y:%f",offset.x, offset.y);*/
	if (offset.x > 200.f || offset.y > 200.f || offset.x < -200.f || offset.y < -200.f) {
		auto randFacingDirection = cocos2d::random(0, 3);//too far,so the monster random move
		if (randFacingDirection) {
			setM_nowFacing(randFacingDirection);

			AImove(getM_nowFacing(), getHeroSpriteName());

		}
		else {
			log("create rand monster action failed");
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


Animate* AIHero::createAIAnimate(const std::string pActionName)
{
	/* 加载图片帧到缓存池 */
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(pActionName + ".plist", pActionName + ".png");

	int iFrameNum = 4;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	/* 用一个列表保存所有SpriteFrame对象 */
	for (int i = 1; i <= iFrameNum; i++) {
		/* 从SpriteFrame缓存池中获取SpriteFrame对象 */
		switch (getM_nowFacing())
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
				log("didn't find ");
		}
		frameVec.pushBack(frame);
	}

	/* 使用SpriteFrame列表创建动画对象 */
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 0.1f, 1);

	/* 将动画包装成一个动作 */
	Animate* action = Animate::create(animation);

	/*清除缓存*/
	AnimationCache::destroyInstance();
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
	//TextureCache::getInstance()->removeUnusedTextures();

	return action;
}



void AIHero::AImove(int face, const std::string pAnimateName) {
	log("move!!");
	// 0.3s duration
	int offsetX = 0, offsetY = 0;

	const int speedEveryPress = 4;

	Animate* movingAction;

	log("face %d", face);
	switch (face) {
		case QS::kDown: {
			offsetY = -speedEveryPress;
			movingAction = createAIAnimate("Hero/" + pAnimateName + "Down");
			log("pMoveAction down end!");
			break;
		}
		case QS::kUp: {
			offsetY = speedEveryPress;
			movingAction = createAIAnimate("Hero/" + pAnimateName + "Up");
			log("pMoveAction up end!");
			break;
		}
		case QS::kLeft: {
			offsetX = -speedEveryPress;
			movingAction = createAIAnimate("Hero/" + pAnimateName + "LeftDown");
			log("pMoveAction left end!");
			break;
		}
		case QS::kRight: {
			offsetX = speedEveryPress;
			movingAction = createAIAnimate("Hero/" + pAnimateName + "RightDown");
			log("pMoveAction right end!");
			break;
		}
		default: {
			log("invalid keybpard");
		}
	}


	auto moveBy = MoveBy::create(1.0f, Vec2(offsetX, offsetY));

	auto finalAction = Spawn::createWithTwoActions(moveBy, movingAction);
	
	this->m_pHeroSprite->runAction(finalAction);
	return;
}







bool AIHero::judgeAIHeroDie()
{
	if (getHealth() <= 0)
	{

		return true;
	}
	return false;
}

