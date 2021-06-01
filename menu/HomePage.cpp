#include "HomePage.h"
#include "cocos2d.h"


using namespace cocos2d;

cocos2d::Scene* HomePage::createScene()
{
	return HomePage::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HomePage::init()
{
	if (!Scene::init())
	{
		return false;
	}

	memset(num, 0, sizeof(num));

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//背景图片 background picture
	HomePage::loadBackgroundPicture(this);


	//在菜单上展现十个游戏参与者，第一个固定是host

	auto* menu = Menu::create();
	menu->setPosition(Size::ZERO);
	addChild(menu);

	//the choose AI/player
	for (int i = 0; i < 10; i++) {
		//左上角是 host
		if (i == 5) {
			auto* host = MenuItemImage::create(
				"button/HOST.png",
				"button/HOST.png");

			auto item = MenuItemToggle::createWithCallback(
				CC_CALLBACK_1(HomePage::selectPlayerOrAICallback, this, i),
				host, host, NULL);

			item->setPosition(Vec2((i % 5 + 1) * (origin.x + visibleSize.width) / 6,
				(i / 5 + 1) * (origin.y + visibleSize.height) / 3));
			menu->addChild(item);
		}
		else {
			auto* AI = MenuItemImage::create(
				"button/AI-normal.png",
				"button/AI-push.png");

			auto* player = MenuItemImage::create(
				"button/PLAYER-normal.png",
				"button/PLAYER-push.png");

			auto item = MenuItemToggle::createWithCallback(
				CC_CALLBACK_1(HomePage::selectPlayerOrAICallback, this, i),
				AI, player, NULL);

			item->setPosition(Vec2((i % 5 + 1) * (origin.x + visibleSize.width) / 6,
				(i / 5 + 1) * (origin.y + visibleSize.height) / 3));
			menu->addChild(item);
		}
	}


	//20 arrows
	for (int i = 0; i < 10; i++) {

		auto* leftArrow = MenuItemImage::create(
			"button/LeftArrow-normal.png",
			"button/LeftArrow-push.png",
			CC_CALLBACK_1(HomePage::leftArrowCallback, this, i));

		auto* rightArrow = MenuItemImage::create(
			"button/RightArrow-normal.png",
			"button/RightArrow-push.png",
			CC_CALLBACK_1(HomePage::rightArrowCallback, this, i));

		//leftArrow->setAnchorPoint(Point(0.5, 0.5));
		leftArrow->setPosition(Vec2((i % 5 + 1) * (origin.x + visibleSize.width) / 6 - (origin.x + visibleSize.width) / 18,
			(i / 5 + 1) * (origin.y + visibleSize.height) / 3 + (origin.y + visibleSize.height) / 6));
		menu->addChild(leftArrow);

		
		rightArrow->setPosition(Vec2((i % 5 + 1) * (origin.x + visibleSize.width) / 6 + (origin.x + visibleSize.width) / 18,
			(i / 5 + 1) * (origin.y + visibleSize.height) / 3 + (origin.y + visibleSize.height) / 6));
		menu->addChild(rightArrow);
	}

	//10 charactors
	for (int i = 0; i < 10; i++) {

		Sprite* charactor = Sprite::create("actor/Soldier-1.png");


		charactor->setPosition(Vec2((i % 5 + 1) * (origin.x + visibleSize.width) / 6,
			(i / 5 + 1) * (origin.y + visibleSize.height) / 3 + (origin.y + visibleSize.height) / 6));
		this->addChild(charactor);

	}


	//start gam
	auto* startItemImage = MenuItemImage::create(
		"button/START-normal.png",
		"button/START-push.png");

	auto startGameItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(HomePage::startGameCallback, this),
		startItemImage,
		NULL);
	startGameItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));
	menu->addChild(startGameItem);


	//back too menu
	auto* backItemImage = MenuItemImage::create(
		"button/BACK-normal.png",
		"button/BACK-push.png");

	auto backMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(HomePage::menuBackCallback, this),
		backItemImage,
		NULL);
	backMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 8));
	menu->addChild(backMenuItem);


	return true;
}

void HomePage::loadBackgroundPicture(cocos2d::Ref* pSender)
{
	//c
	MenuItem* item = (MenuItem*)pSender;
	log("Touch Background MenuItem %p", item);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* menuBackground = Sprite::create("menu/RoomBackground.png");
	menuBackground->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	Size mywinsize = Director::getInstance()->getWinSize();
	float winw = mywinsize.width; //获取屏幕宽度
	float winh = mywinsize.height;//获取屏幕高度
	float spx = menuBackground->getTextureRect().getMaxX();
	float spy = menuBackground->getTextureRect().getMaxY();
	menuBackground->setScaleX(winw / spx); //设置精灵宽度缩放比例
	menuBackground->setScaleY(winh / spy);
	this->addChild(menuBackground);
}



void HomePage::selectPlayerOrAICallback(Ref* pSender, const int i)
{


}


void HomePage::leftArrowCallback(Ref* pSender,const int i)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch rightAroow MenuItem %p", item);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (num[i] <= 0) {
		num[i] = ACTOR_NUM;
	}
	Sprite* charactor = Sprite::create(actorImagePath[--num[i]]);

	charactor->setPosition(Vec2((i % 5 + 1) * (origin.x + visibleSize.width) / 6,
		(i / 5 + 1) * (origin.y + visibleSize.height) / 3 + (origin.y + visibleSize.height) / 6));
	this->addChild(charactor);
}
void HomePage::rightArrowCallback(Ref* pSender, const int i)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch rightAroow MenuItem %p", item);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (num[i] >= ACTOR_NUM-1) {
		num[i] = -1;
	}
	Sprite* charactor = Sprite::create(actorImagePath[++num[i]]);

	charactor->setPosition(Vec2((i % 5 + 1) * (origin.x + visibleSize.width) / 6,
		(i / 5 + 1) * (origin.y + visibleSize.height) / 3 + (origin.y + visibleSize.height) / 6));
	this->addChild(charactor);
}

void HomePage::startGameCallback(cocos2d::Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch start game Item %p", item);


}


void HomePage::menuBackCallback(cocos2d::Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch back MenuItem %p", item);

	Director::getInstance()->popScene();

}

