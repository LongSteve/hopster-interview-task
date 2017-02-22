//
//  HelpScene.h
//  ExpJam
//
//  Created by Stephen Longhurst on 22/02/2017.
//
//

#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"

class HelpScene : public cocos2d::Scene
{
    typedef cocos2d::Scene Super;
public:
    // implement the "static create()" method manually
    CREATE_FUNC(HelpScene);

    // scene initialisation
    virtual bool init();
    // scene shown
    virtual void onEnter();
    // scene hidden
    virtual void onExit();
 
    // Menu actions
    void onBack (cocos2d::Ref *sender);
};


#endif
