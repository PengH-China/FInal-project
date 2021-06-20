/**
*@file BattleScene.cpp
*@author 张子涵 方新宇
*@date 6/5/2021
*/


#include "BattleScene.h"


Scene* BattleScene::createScene()
{
	auto scene = BattleScene::createWithPhysics();
	//auto layer = BattleScene::create(map);
	auto mapLayer = MapLayer::create();

	scene->addChild(mapLayer, QS::kMapLayerPriority);
	scene->addUI();
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemImage* SettingItemImage = nullptr;
	SettingItemImage = MenuItemImage::create(
		"button/Setting-normal.png",
		"button/Setting-push.png");
	if (SettingItemImage != nullptr)
	{
		log("not null");
	}
	auto SettingItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(BattleScene::menuPauseCallback, scene),
		SettingItemImage,
		NULL);
	SettingItem->setAnchorPoint(Vec2(1,1));
	SettingItem->setPosition(Vec2(visibleSize.width , visibleSize.height ));
	// SettingItem->setPosition(Vec2(winSize.width - SettingItem->getContentSize().width / 2, winSize.height - SettingItem->getContentSize().height / 2));
	//this->addChild(SettingItem, 1);
	Menu* pmenu = Menu::create(SettingItem, NULL);
	pmenu->setPosition(Vec2::ZERO);
	scene->addChild(pmenu, QS::kUIPriority);

	scene->scheduleUpdate();
	scene->schedule(CC_SCHEDULE_SELECTOR(BattleScene::scheduleUpdateHeroDie), 0.1f);

	return scene;
}



void BattleScene::scheduleUpdateHeroDie(float dt)
{
	if (backToMenu)
	{
		backToMenu = false;
		auto scene = MyMenu::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	log("judging hero die");
	if (globalHero->judgeHeroDie())
	{
		if (isEffect) {
			auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);
			//按键声
		}
		Size visibleSize = Director::getInstance()->getVisibleSize();
		RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

		renderTexture->begin();
		this->visit();
		/*Node* Sender = this->getParent();
		Sender->retain();
		Sender->visit();*/
		renderTexture->end();

		Director::getInstance()->pushScene(GameOver::createLayer(renderTexture));
		log("hero die and game over");
	}

}

BattleScene* BattleScene::createWithPhysics()
{
	auto* ret = new (std::nothrow) BattleScene();
	if (ret && ret->initWithPhysics()&&ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
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
	return true;
}

void BattleScene::addUI()
{
	auto* UIboard = HeroUI::create();
	if (UIboard == nullptr)
	{
		log("UI picture not found");
	}
	else
	{
		log("begin init UI");
		const Vec2 boardSize = Vec2(600, 214);
		Vec2 boardPosition = Vec2(0, 0);
		boardPosition.x = boardSize.x / 4 + 45;//35;
		boardPosition.y = this->getContentSize().height - boardSize.y / 4 - 15;
		/*log("boardSize.y %f", boardSize.y);
		log("boardSize.x %f", boardSize.x);
		log("x:%f", boardPosition.x);
		log("y:%f", boardPosition.y);*/
		//float spx = BattleMapSprite->getTextureRect().getMaxX();
		//float spy = BattleMapSprite->getTextureRect().getMaxY();
		UIboard->setPosition(boardPosition);
		addChild(UIboard, QS::kUIPriority, QS::Name::kHeroUI);
		log("end init UI");
	}
}

void BattleScene::menuPauseCallback(cocos2d::Ref* pSender)
{
	if (isEffect) {
		auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);
		//按键声
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

	renderTexture->begin();
	this->visit();
	/*Node* Sender = this->getParent();
	Sender->retain();
	Sender->visit();*/
	renderTexture->end();

	Director::getInstance()->pushScene(PauseLayer::createLayer(renderTexture));
}