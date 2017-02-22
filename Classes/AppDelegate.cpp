//
//  AppDelegate.cpp
//  Hopster Coding Interview
//
//  Created by Steve Longhurst on 22/02/2017.
//
//

#include "AppDelegate.h"
#include "SplashScene.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

USING_NS_CC;


AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // seed the random number generator
    srand (static_cast <unsigned> (time(0)));
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
    {
        glview = GLView::create( "Game" );
        director->setOpenGLView( glview );
    }

    // turn on display FPS
    director->setDisplayStats( false );

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval( 1.0 / 60.0f );

    // create and run scene. it's an autorelease object
    auto scene = SplashScene::create();
    director->runWithScene( scene );

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
