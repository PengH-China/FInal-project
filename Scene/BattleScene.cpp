/**
*@file BattleScene.cpp
*@author 张子涵 方新宇
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

	//背景图片 background picture
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
	/* 保存meta图层的引用 */
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
			/* 不为0，代表存在这个格子 */
			if (tiledGid != 0) {
				/*
				获取该地图格子的所有属性，目前我们只有一个Collidable属性
				格子是属于meta层的，但同时也是属于整个地图的，所以在获取格子的所有属性
				时，通过格子唯一标识在地图中取得
				*/
				Value properties = m_map->getPropertiesForGID(tiledGid);

				ValueMap propertiesMap = properties.asValueMap();

				if (propertiesMap.find("Collidable") != propertiesMap.end())
				{
					/* 取得格子的Collidable属性值 */
					Value prop = propertiesMap.at("Collidable");
					if (prop.asString().compare("true") == 0)
					{
						Sprite* gidSprite = m_meta->getTileAt(Vec2(x, y));
						gidSprite->setName(QS::tag::kGidTag);
						log("set (%d,%d) gid as barrier", x, y);
					}
					
		}
	}
	
			///* 判断Collidable属性是否为true，如果是，则不让玩家移动 */
			//if (prop.asString().compare("true") == 0 && isJumping == false) {
			//	isJumping = true;

			//	auto jumpBy = JumpBy::create(0.5f, Point(-100, 0), 80, 1);
			//	CallFunc* callfunc = CallFunc::create([&]() {
			//		/* 恢复状态 */
			//		isJumping = false;
			//		});

			//	/* 执行动作，碰撞到障碍物时的反弹效果 */
			//	auto actions = Sequence::create(jumpBy, callfunc, NULL);
			//	this->runAction(actions);
			}
		}
        
}