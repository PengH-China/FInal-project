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
	///* ����ͼƬ֡������� */
	//SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	//frameCache->addSpriteFramesWithFile(pActionName + ".plist", pActionName + ".png");

	//const int iFrameNum = 3;
	//SpriteFrame* frame = NULL;
	//Vector<SpriteFrame*> frameVec;

	///* ��һ���б�������SpriteFrame���� */
	//for (int i = 1; i <= iFrameNum; i++) {
	//	/* ��SpriteFrame������л�ȡSpriteFrame���� */
	//	frame = frameCache->getSpriteFrameByName(StringUtils::format
	//											("monster_0%d0%d.png", whichMonster,i));
	//	if(nullptr==frame){
	//		log("monster animation create failed!!,in monster.cpp line 20");
	//	}
	//	else {
	//		frameVec.pushBack(frame);
	//	}
	//}

	///* ʹ��SpriteFrame�б����������� */
	//Animation* animation = Animation::createWithSpriteFrames(frameVec, 0.1f, 1);


	///* ��������װ��һ������ */
	//Animate* action = Animate::create(animation);

	///*�������*/
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
