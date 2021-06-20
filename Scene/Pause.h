#ifndef __PAUSELAYER_H__
#define __PAUSELAYER_H__

#include "cocos2d.h"
#include "GlobalPara/GlobalParameter.h"
//#include "Role/Hero.h"
#include"Const/Const.h"
#include "AudioEngine.h"
#include "Menu/MyMenu.h"
//#include "Monster/MonsterGroup.h"

using namespace cocos2d;
class PauseLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	static Scene* createLayer(RenderTexture* sqr);
	CREATE_FUNC(PauseLayer);
	//¼ÌÐøÓÎÏ·
	void menuContinueCallback(cocos2d::Ref* pSender);

	void SEControl(cocos2d::Ref* pSender);

	void BGDMusicControl(cocos2d::Ref* pSender);

	void GoBackControl(cocos2d::Ref* pSender);

private:

	
};
#endif
