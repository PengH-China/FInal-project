#include "Pause.h"

bool PauseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto* soundEffectLabel = Label::createWithSystemFont("Setting", "Arial", 65, Size::ZERO, TextHAlignment::RIGHT);
	soundEffectLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 8 * 5+40));
	this->addChild(soundEffectLabel, 1);
	//继续游戏按钮
	auto* continueGameItemImage = MenuItemImage::create(
		"button/Continue-normal.png",
		"button/Continue-push.png");
	auto continueGameItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(PauseLayer::menuContinueCallback, this),
		continueGameItemImage,
		NULL);
	continueGameItem->setPosition(Vec2(origin.x + visibleSize.width / 2+100, origin.y + visibleSize.height / 8 * 5-70));

	
	auto* SEControlItemImage = MenuItemImage::create(
		"button/SoundEffect-normal.png",
		"button/SoundEffect-push.png");

	auto SEControlItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(PauseLayer::SEControl, this),
		SEControlItemImage,
		NULL);
	SEControlItem->setPosition(Vec2(origin.x + visibleSize.width / 2-100, origin.y + visibleSize.height / 8 * 5-70));

	auto* BackgroundMusicControlItemImage = MenuItemImage::create(
		"button/BackgroundMusic-normal.png",
		"button/BackgroundMusic-push.png");

	auto BackgroundMusicControlItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(PauseLayer::BGDMusicControl, this),
		BackgroundMusicControlItemImage,
		NULL);
	BackgroundMusicControlItem->setPosition(Vec2(origin.x + visibleSize.width / 2-100, origin.y + visibleSize.height / 8 * 4-100));

	auto* GoBackItemImage = MenuItemImage::create(
		"button/Return-normal.png",
		"button/Return-push.png");

	auto GoBackItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(PauseLayer::GoBackControl, this),
		GoBackItemImage,
		NULL);
	GoBackItem->setPosition(Vec2(origin.x + visibleSize.width / 2+100, origin.y + visibleSize.height / 8 * 4-100 ));

	Menu* mn = Menu::create(SEControlItem, BackgroundMusicControlItem, continueGameItem, GoBackItem, NULL);
	mn->setPosition(Size::ZERO);
	this->addChild(mn);

	return true;
}

Scene* PauseLayer::createLayer(RenderTexture* sqr)
{
	Scene* scene = Scene::create();
	PauseLayer* pauseLayer = PauseLayer::create();
	scene->addChild(pauseLayer, 1);
	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
  //并将Sprite添加到GamePause场景层中
  //得到窗口的大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* screenShotPicture = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	screenShotPicture->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。
	screenShotPicture->setFlippedY(true);            //翻转，因为UI坐标和OpenGL坐标不同
	screenShotPicture->setColor(cocos2d::Color3B::GRAY); //图片颜色变灰色
	scene->addChild(screenShotPicture);

	Sprite* background = Sprite::create("menu/Pause/PauseBackground.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。
	scene->addChild(background);

	return scene;
}

void PauseLayer::menuContinueCallback(cocos2d::Ref* pSender)
{
	if (isEffect)
	{
		auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);
		//按键声
	}
	Director::getInstance()->popScene();
}
void PauseLayer::SEControl(cocos2d::Ref* pSender)
{
	auto* soundEffectControlItem = (MenuItemToggle*)pSender;
	log("soundEffectControlItem %d", soundEffectControlItem->getSelectedIndex());

	if (isEffect)
	{
		auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);
		//按键声
	}
	if (isEffect) //选中状态 Off -> On
	{
		isEffect = false;
		log(isEffect);
	}
	else
	{
		isEffect = true;
		auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);
	}
}
void PauseLayer::BGDMusicControl(cocos2d::Ref* pSender)
{
	auto* musicControlItem = (MenuItemToggle*)pSender;
	log("menuMusicCallback %d", musicControlItem->getSelectedIndex());
	//log("%s",)
	if (isMusic) //选中状态 Off -> On
	{
		AudioEngine::stopAll();
		isMusic = false;
	}
	else
	{
		auto backgroundAudioID = AudioEngine::play2d("sound/backgroundMusic.mp3", true);
		isMusic = true;
		//true--->loop
	}

	if (isEffect) 
	{
		auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);
		//按键声
	}
}
void PauseLayer::GoBackControl(cocos2d::Ref* pSender)
{
	if (isEffect) 
	{
		auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);
		//按键声
	}
	backToMenu = true;
	//auto scene = MyMenu::createScene();
	Director::getInstance()->popScene();

}





