//
//  MenuScene.h
//  ExpJam
//
//  Created by Stephen Longhurst on 22/02/2017.
//
//

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"


class MenuScene : public cocos2d::Scene
{
    typedef cocos2d::Scene Super;
public:
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

    // scene initialisation
    virtual bool init();
    // scene shown
    virtual void onEnter();
    // scene hidden
    virtual void onExit();
 
    // Menu actions
    void onStart (cocos2d::Ref *sender);
    void onHelp (cocos2d::Ref *sender);
    void onQuit (cocos2d::Ref *sender); 
};

#endif
