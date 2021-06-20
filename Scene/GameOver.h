#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "cocos2d.h"
#include "GlobalPara/GlobalParameter.h"
#include"Const/Const.h"
#include "AudioEngine.h"
#include "Menu/MyMenu.h"
//#include "Monster/MonsterGroup.h"

using namespace cocos2d;
class GameOver :public cocos2d::Layer
{
public:
	virtual bool init();
	static Scene* createLayer(RenderTexture* sqr);
	CREATE_FUNC(GameOver);


	void GoBackControl(cocos2d::Ref* pSender);

private:

	
};
#endif

