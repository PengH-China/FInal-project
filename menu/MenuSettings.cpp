#include "MenuSettings.h"
#include "cocos2d.h"
#include "AudioEngine.h"

using namespace cocos2d;

Scene* MenuSettings::createScene()
{
	return MenuSettings::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuSettings::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//loadBackgroundPicture(this);//load background picture

	MenuItemFont::setFontName("POBG");
	MenuItemFont::setFontSize(86);

	//��Ч����Sound Effect

	auto* soundEffectLabel = Label::createWithSystemFont("Sound Effect", "Arial", 80, Size::ZERO, TextHAlignment::RIGHT);
	soundEffectLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 8 * 7));
	this->addChild(soundEffectLabel, 1);

	auto* soundEffectOff = MenuItemImage::create(
		"button/OFF-normal.png",
		"button/OFF-push.png");

	auto* soundEffectOn = MenuItemImage::create(
		"button/ON-normal.png",
		"button/ON-push.png");

	auto* soundEffectStatus = soundEffectOff;
	auto* soundEffectChoice = soundEffectOn;

	if (isEffect) {
		soundEffectStatus = soundEffectOn;
		soundEffectChoice = soundEffectOff;
	}

	auto soundEffectControlItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(MenuSettings::menuSoundEffectCallback, this),
		soundEffectStatus,
		soundEffectChoice,
		NULL);

	soundEffectControlItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 8 * 6));

	//�������� Music
	//���ֱ�ǩ Music Label (the white words to simblize the item)
	auto* musicLabel = Label::createWithSystemFont("Music", "Arial", 80, Size::ZERO, TextHAlignment::RIGHT);
	musicLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 8 * 5));
	this->addChild(musicLabel, 1);

	auto* musicOff = MenuItemImage::create(
		"button/OFF-normal.png",
		"button/OFF-push.png");

	auto* musicOn = MenuItemImage::create(
		"button/ON-normal.png",
		"button/ON-push.png");

	auto* musicStatus = musicOff;
	auto* musicChoice = musicOn;

	if (isMusic) {
		 musicStatus = musicOn;
		 musicChoice = musicOff;
	}

	auto musicControlItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(MenuSettings::menuMusicCallback, this),
		musicStatus,
		musicChoice,
		NULL);

	musicControlItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 8 * 4));


	//back

	auto* backItemImage = MenuItemImage::create(
		"button/BACK-normal.png",
		"button/BACK-push.png");

	auto backMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(MenuSettings::menuBackCallback, this),
		backItemImage,
		NULL);

	backMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));
	//this->addChild(backMenuItem);

	//menu
	Menu* mn = Menu::create(soundEffectControlItem, musicControlItem, backMenuItem, NULL);
	mn->setPosition(Size::ZERO);
	this->addChild(mn);


	return true;
}


void MenuSettings::loadBackgroundPicture(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* menuBackground = Sprite::create("menu/background.jpg");
	menuBackground->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	Size mywinsize = Director::getInstance()->getWinSize();
	float winw = mywinsize.width; //��ȡ��Ļ���
	float winh = mywinsize.height;//��ȡ��Ļ�߶�
	float spx = menuBackground->getTextureRect().getMaxX();
	float spy = menuBackground->getTextureRect().getMaxY();
	menuBackground->setScaleX(winw / spx); //���þ��������ű���
	menuBackground->setScaleY(winh / spy);
	this->addChild(menuBackground);
}


void MenuSettings::menuSoundEffectCallback(Ref* pSender)
{
	auto* soundEffectControlItem = (MenuItemToggle*)pSender;
	log("soundEffectControlItem %d", soundEffectControlItem->getSelectedIndex());

	if (isEffect) {
		auto soundEffectID = AudioEngine::play2d("sound/Blip.wav", false);
		//������
	}
	if (isEffect) //ѡ��״̬ Off -> On
	{
		isEffect = false;
	}
	else
	{
		isEffect = true;
		auto soundEffectID = AudioEngine::play2d("sound/Blip.wav", false);
	}
	
}

void MenuSettings::menuMusicCallback(Ref* pSender)
{
	auto* musicControlItem = (MenuItemToggle*)pSender;
	log("menuMusicCallback %d", musicControlItem->getSelectedIndex());

	//���ļ�����
	//auto sharedFileUtils = FileUtils::getInstance();
	//std::string pathKey = sharedFileUtils->fullPathForFilename("isMusic.txt");
	


	if (isMusic) //ѡ��״̬ Off -> On
	{
		AudioEngine::stopAll();
	}
	else
	{
		auto backgroundAudioID = AudioEngine::play2d("sound/backgroundMusic.mp3", true);
		//true--->loop
	}

	if (isEffect) {
		auto soundEffectID = AudioEngine::play2d("sound/Blip.wav", false);
		//������
	}
}

void MenuSettings::menuBackCallback(cocos2d::Ref* pSender)
{
	MenuItem* item = (MenuItem*)pSender;
	log("Touch back MenuItem %p", item);

	Director::getInstance()->popScene();

}
