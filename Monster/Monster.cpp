#include "Monster.h"
#include "cocos2d.h"

Sprite* Monster::getSprite()
{
	return m_pMonsterSprite;
}

void Monster::monsterPositionInit(cocos2d::Point position)
{
	/*m_pMonsterSprite = Sprite::create("monster/" + m_pMonsterSpriteName + ".png");
	m_pMonsterSprite->setScale(2.0f);
	this->bindSprite(m_pMonsterSprite);
	this->genePhysicsBody();
	this->setPosition(position);*/
}

Animate* Monster::createAnimate(const std::string pActionName)
{
	///* 加载图片帧到缓存池 */
	//SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	//frameCache->addSpriteFramesWithFile(pActionName + ".plist", pActionName + ".png");

	//const int iFrameNum = 3;
	//SpriteFrame* frame = NULL;
	//Vector<SpriteFrame*> frameVec;

	///* 用一个列表保存所有SpriteFrame对象 */
	//for (int i = 1; i <= iFrameNum; i++) {
	//	/* 从SpriteFrame缓存池中获取SpriteFrame对象 */
	//	frame = frameCache->getSpriteFrameByName(StringUtils::format
	//											("monster_0%d0%d.png", whichMonster,i));
	//	if(nullptr==frame){
	//		log("monster animation create failed!!,in monster.cpp line 20");
	//	}
	//	else {
	//		frameVec.pushBack(frame);
	//	}
	//}

	///* 使用SpriteFrame列表创建动画对象 */
	//Animation* animation = Animation::createWithSpriteFrames(frameVec, 0.1f, 1);


	///* 将动画包装成一个动作 */
	//Animate* action = Animate::create(animation);

	///*清除缓存*/
	//AnimationCache::destroyInstance();
	//SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();

	//return action;
	return NULL;
}

Monster* Monster::createMonster(cocos2d::Point position)
{
	/*Monster* monster = new Monster();

	if (monster && monster->init())
	{
		monster->autorelease();
		monster->monsterPositionInit(position);
		return monster;
	}
	CC_SAFE_DELETE(monster);
	*/
	return NULL;
}

bool Monster::init()
{
	if (!Role::init()) {
		return false;
	}
	scheduleUpdate();
	//srand((unsigned)time(NULL));
	//this->whichMonster = rand() % 3 + 1;
	//log("choose a monster,it is %d", whichMonster);
	//init the random number that decides choose which image of monster

	//nameMonster[17] = (whichMonster + '0');
	//nameMonsterForAnmi[8] = (whichMonster + '0');
	//log("the name of monster -- %s", nameMonsterForAnmi);
	//auto monsterAction = createAnimate(nameMonsterForAnmi); gengrate an action in scene
	
	return true;
}
