#include "GameOver.h"


bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//原点坐标
	Point origin = Director::getInstance()->getVisibleOrigin();


	auto* GoBackItemImage = MenuItemImage::create(
		"button/Return-normal.png",
		"button/Return-push.png");

	auto GoBackItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(GameOver::GoBackControl, this),
		GoBackItemImage,
		NULL);
	GoBackItem->setPosition(Vec2(origin.x + visibleSize.width / 2+100, origin.y + visibleSize.height / 8 * 4-100 ));

	Menu* mn = Menu::create(  GoBackItem, NULL);
	mn->setPosition(Size::ZERO);
	this->addChild(mn);

	return true;

	
}

Scene* GameOver::createLayer(RenderTexture* sqr)
{
	Scene* scene = Scene::create();
	GameOver* gameOverLayer = GameOver::create();
	scene->addChild(gameOverLayer, 1);
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

void GameOver::GoBackControl(cocos2d::Ref* pSender)
{
	if (isEffect) {
		auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);
		//按键声
	}
	auto scene = MyMenu::createScene();
	Director::getInstance()->replaceScene(scene);

}






