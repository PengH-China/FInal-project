/**
*@file BattleScene.cpp
*@author ���Ӻ� ������
*@date 6/5/2021
*/


#include "cocos2d.h"
#include "BattleScene.h"
#include"Const/Const.h"

using namespace cocos2d;

cocos2d::Scene* BattleScene::createScene()
{
	return BattleScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//����ͼƬ background picture
	BattleScene::loadBackgroundMap(this);
	BattleScene::setGidTag();
	return true;
}

void BattleScene::loadBackgroundMap(cocos2d::Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Background MenuItem %p", item);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXTiledMap* battleMap = TMXTiledMap::create("map1.tmx");
	BattleScene::setTiledMap(battleMap);
	battleMap->setAnchorPoint(Vec2(0, 0));
	//battleMap->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
	this->addChild(battleMap);
}



void BattleScene::menuBackCallback(cocos2d::Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch back MenuItem %p", item);

	Director::getInstance()->popScene();

}

void BattleScene::setTiledMap(TMXTiledMap* map)
{
	m_map = map;
	/* ����metaͼ������� */
	this->m_meta = m_map->getLayer("meta");
	this->m_meta->setVisible(false);
}
void BattleScene::setGidTag()
{
	Size sizeOfMap=m_map->getMapSize();
	log("sizeOfMap:%f %f", sizeOfMap.width-1, sizeOfMap.height-1);
	for (int y = 0; y <= sizeOfMap.height - 1; y++) {
		for (int x = 0; x <= sizeOfMap.width - 1; x++) {
			int tiledGid = m_meta->getTileGIDAt(Vec2(x,y));
			/* ��Ϊ0���������������� */
			if (tiledGid != 0) {
				/*
				��ȡ�õ�ͼ���ӵ��������ԣ�Ŀǰ����ֻ��һ��Collidable����
				����������meta��ģ���ͬʱҲ������������ͼ�ģ������ڻ�ȡ���ӵ���������
				ʱ��ͨ������Ψһ��ʶ�ڵ�ͼ��ȡ��
				*/
				Value properties = m_map->getPropertiesForGID(tiledGid);

				ValueMap propertiesMap = properties.asValueMap();

				if (propertiesMap.find("Collidable") != propertiesMap.end())
				{
					/* ȡ�ø��ӵ�Collidable����ֵ */
					Value prop = propertiesMap.at("Collidable");
					if (prop.asString().compare("true") == 0)
					{
						Sprite* gidSprite = m_meta->getTileAt(Vec2(x, y));
						gidSprite->setName(QS::tag::kGidTag);
						log("set (%d,%d) gid as barrier", x, y);
					}
					
		}
	}
	
			///* �ж�Collidable�����Ƿ�Ϊtrue������ǣ���������ƶ� */
			//if (prop.asString().compare("true") == 0 && isJumping == false) {
			//	isJumping = true;

			//	auto jumpBy = JumpBy::create(0.5f, Point(-100, 0), 80, 1);
			//	CallFunc* callfunc = CallFunc::create([&]() {
			//		/* �ָ�״̬ */
			//		isJumping = false;
			//		});

			//	/* ִ�ж�������ײ���ϰ���ʱ�ķ���Ч�� */
			//	auto actions = Sequence::create(jumpBy, callfunc, NULL);
			//	this->runAction(actions);
			}
		}
        
}