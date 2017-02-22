//
//  SplashScene.h
//  ExpJam
//
//  Created by Stephen Longhurst on 22/02/2017.
//
//

#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

class SplashScene : public cocos2d::Scene
{
    typedef cocos2d::Scene Super;
public:
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);

    // scene initialisation
    virtual bool init();
    // scene shown
    virtual void onEnter();
    // scene hidden
    virtual void onExit();
    
    // called once per frame
    virtual void update( float delta );
 
protected:
    cocos2d::Label *text;
    int numLetters;
    std::vector<float> initalLetterY;
};

#endif
