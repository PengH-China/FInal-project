#include "SceneChangeLoad.h"

static void problemLoading(const char* filename){
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* SceneChangeLoad::createScene(){
	return SceneChangeLoad::create();
}


bool SceneChangeLoad::init(){
    
    if (!Scene::init()){
        return false;
    }

    auto winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = DrawNode::create();
    background->drawSolidRect(origin, winSize, cocos2d::Color4F(0.0, 0.0, 0.0, 1.0));
    this->addChild(background);
    
    Sprite* pBackGround = Sprite::create("processBar/processBackGround.png");
    if (nullptr == pBackGround) {
        problemLoading("failed background create!");
    }
    else {
        pBackGround->setPosition(winSize.width / 2 + origin.x, winSize.height / 2 + origin.y);
        pBackGround->setScale(3.0f);
        this->addChild(pBackGround);
    }
    

    auto label = Label::createWithTTF("Loading, please wait for a while", 
                                      "fonts/Marker Felt.ttf", 30);
    if (label == nullptr){
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else{
        label->setPosition(Vec2(origin.x + winSize.width / 2,
                                origin.y + winSize.height / 6));
        this->addChild(label, 1);
    }

    Sprite* runSp = Sprite::create("processBar/begin.png");
    if (runSp == nullptr) {
        problemLoading("failed processBar create!");
    }
    else {
        runSp->setScaleX(3.5f);
        runSp->setScaleY(1.5f);
        runSp->setPosition(winSize.width / 2 + origin.x, winSize.height / 5);
        this->addChild(runSp);
        runSp->runAction(SceneChangeLoad::createAnimate());
    }
    //Director::getInstance()->end();

}

Animate* SceneChangeLoad::createAnimate(){
    /* 加载图片帧到缓存池 */
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
   // const char* Bar

    frameCache->addSpriteFramesWithFile("processBar/BarVersion2.plist", 
                                        "processBar/BarVersion2.png");

    const int iFrameNum = 4;
    SpriteFrame* frame = NULL;
    Vector<SpriteFrame*> frameVec;

    /* 用一个列表保存所有SpriteFrame对象 */
    for (int i = 1; i <= iFrameNum; i++) {
        /* 从SpriteFrame缓存池中获取SpriteFrame对象 */
        frame = frameCache->getSpriteFrameByName(StringUtils::format("BarVersion20%d.png", i));
        frameVec.pushBack(frame);
    }

    /* 使用SpriteFrame列表创建动画对象 */
    Animation* animation = Animation::createWithSpriteFrames(frameVec);
    animation->setLoops(1);
    animation->setDelayPerUnit(1.5f);

    /* 将动画包装成一个动作 */
    Animate* action = Animate::create(animation);

    return action;
}
