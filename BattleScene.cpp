/**
*@file BattleScene.cpp
*@author 张子涵 方新宇
*@date 6/5/2021
*/


#include "cocos2d.h"
#include "BattleScene.h"
#include "Role/Hero.h"

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
	log("problem2!?");
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//背景图片 background picture
	BattleScene::loadBackgroundMap(this);


	auto* hero = Hero::createHero(Vec2(180, 100));
	addChild(hero);

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
	m_pMap = map;
	/* 保存meta图层的引用 */
	this->m_pMeta = m_pMap->getLayer("meta");
	this->m_pMeta->setVisible(false);
}
