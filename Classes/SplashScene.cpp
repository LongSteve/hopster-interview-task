//
//  SplashScene.cpp
//  ExpJam
//
//  Created by Stephen Longhurst on 22/02/2017.
//
//

#include "Constants.h"
#include "SplashScene.h"
#include "MainScene.h"
#include "MenuScene.h"

USING_NS_CC;

// Random function for the wibbling letters
float my_frand (const float min, const float max)
{
   float rnd = ((float)rand()/(float)RAND_MAX);
   return (rnd * (max-min) + min);
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    // super init first
    if ( !Super::init() )
    {
        return false;
    }
    
    // get visible size of window
    Size visibleSize = Director::getInstance()->getVisibleSize();
  
    // add a sprite
    Sprite* sprite = Sprite::create( "BlueBlob-Normal.png" );
    sprite->setPosition( Vec2( visibleSize.width / 2, visibleSize.height / 2 ) );
    // add the sprite as a child to this layer
    this->addChild( sprite );
 
    text = Label::createWithTTF("Angle of Bounce", "Marker Felt.ttf", 72);
    text->setPosition( Vec2( visibleSize.width / 2, visibleSize.height - text->getLineHeight() * 1.5 ) );
    this->addChild( text );
 
    auto scaleDown = ScaleTo::create(0.3, 1.2);
    auto scaleUp = ScaleTo::create(0.3, 0.8);
 
    auto ease_in = EaseBounceIn::create (scaleUp->clone ());
    auto ease_out = EaseBounceOut::create (scaleDown->clone ());
 
    numLetters = text->getStringLength();
    for (int i = 0; i < numLetters; i++)
    {
        auto letter = text->getLetter (i);
        auto delay = DelayTime::create (my_frand (0.1,0.5));
        auto seq = Sequence::create (delay, RepeatForever::create (Sequence::create (ease_in->clone(), ease_out->clone(), nullptr)), nullptr);
        letter->runAction(seq);
        initalLetterY.push_back (letter->getPositionY());
    }
 
    auto sscaleUp = ScaleTo::create (1.0, 32.0);
    auto ease = EaseInOut::create (sscaleUp, 1.0);
 
    auto transition = CallFunc::create( [&] ( ) {
       auto mainScene = MenuScene::create ();
       Director::getInstance ()->replaceScene (TransitionFade::create (0.5, mainScene, Color3B (0,0,0)));
    });
 
    sprite->runAction (Sequence::create (DelayTime::create(1.0), ease, transition, nullptr));
 
    // done
    return true;
}

void SplashScene::onEnter()
{
    Super::onEnter();
    
    // schedule update calls
    scheduleUpdate();
}

void SplashScene::onExit()
{
    Super::onExit();
 
    // unschedule update
    unscheduleUpdate();
}

void SplashScene::update( float delta )
{
   for (int i = 0; i < numLetters; i++)
   {
       auto letter = text->getLetter (i);
       float dY = my_frand (3, 6);
       float iY = initalLetterY.at (i);
       letter->setPositionY (iY + dY);
   }
}
