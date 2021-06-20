
#include "GlobalPara/GlobalParameter.h"
#include "MyMenu.h"


USING_NS_CC;

Scene* MyMenu::createScene()
{
    return MyMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MyMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    MyMenu::loadBackgroundPicture(this);//加载背景图片

    //helpItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));

    MenuItemFont::setFontName("POBG");
    MenuItemFont::setFontSize(150);

    MenuItemFont* startItem = MenuItemFont::create("Start",
        CC_CALLBACK_1(MyMenu::menuStartCallback, this));

    MenuItemFont* joinItem = MenuItemFont::create("Join Game",
        CC_CALLBACK_1(MyMenu::menuJoinGameCallback, this));

    MenuItemFont* settingsItem = MenuItemFont::create("Settings",
        CC_CALLBACK_1(MyMenu::menuSettingsCallback, this));

    MenuItemFont* helpItem = MenuItemFont::create("Help",
        CC_CALLBACK_1(MyMenu::menuHelpCallback, this));

    MenuItemFont* exitItem = MenuItemFont::create("Exit",
        CC_CALLBACK_1(MyMenu::menuExitCallback, this));

    Menu* mn = Menu::create(startItem, joinItem, settingsItem, helpItem, exitItem, NULL);
    mn->alignItemsVertically();
    this->addChild(mn);

    return true;
}


void MyMenu::menuExitCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->end();
}

void MyMenu::loadBackgroundPicture(cocos2d::Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Background MenuItem %p", item);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* menuBackground = Sprite::create("menu/MenuBackground.png");
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


void MyMenu::menuStartCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Start MenuItem %p", item);

    if (isEffect) 
    {
        auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);//按键声
        log("soundEffect%d is on", soundEffectID);
        //按键声
    }

    auto changeSceneAnmiate = SceneChangeLoad::createScene();
    if (changeSceneAnmiate == nullptr) 
    {
        log("failed change scene create!");
    }
    else {
        log("123 1");
    }
    Sleep(1000);

    auto scene = HomePage::createScene();
    Director::getInstance()->pushScene(scene);
}

void MyMenu::menuJoinGameCallback(cocos2d::Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Join Game MenuItem %p", item);
    if (isEffect) 
    {
        auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);//按键声
        log("soundEffect%d is on", soundEffectID);
        //按键声
    }
}
void MyMenu::menuSettingsCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Settings MenuItem %p", item);

    if (isEffect) 
    {
        auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);//按键声
        log("soundEffect%d is on", soundEffectID);
        //按键声
    }

    auto scene = MenuSettings::createScene();
    Director::getInstance()->pushScene(scene);
}

void MyMenu::menuHelpCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    log("Touch Help MenuItem %p", item);

    if (isEffect) 
    {
        auto soundEffectID = AudioEngine::play2d("sound/Blip.mp3", false);//按键声
        log("soundEffect%d is on", soundEffectID);
        //按键声
    }

    auto scene = MenuHelp::createScene();
    Director::getInstance()->pushScene(scene);
}