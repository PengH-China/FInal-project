/**
*@file Item.h
*@author ������
*@date 5/28/2021
*/
#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
//#include "Role/Hero.h"
#include "Const/Const.h"

using namespace cocos2d;

/**
*@brief ��Ʒ��
*@author ������
*/

class Item :public Node
{
public:
	/**
	*@brief �󶨾���
	*/
	void bindSprite(Sprite* pSprite);

	/**
	*@brief ��ȡ����
	*@author ������
	*/
	Sprite* getSprite();

	/**
	*@brief ��������
	*@author ������
	*/
	/*virtual void interact() = 0;*/

	/**
	*@brief �޸�m_pPresentContactItem
	*@author ������
	*/
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual bool onContactSeparate(PhysicsContact& contact);

	/**
	*@brief ����������
	*@author ������
	*/
	void generatePhysicalBody(std::string message, const std::string itemName);
	/**
	*@brief �Ƿ�ɴ�����
	*@author ���
	*/
	bool isAbleOpen();
protected:
	Sprite* m_pSprite;
};

/**
*@brief ����������������ʾ��Ϣ
*@author ������
*/
#endif
#pragma once
