//
//  MainScene.h
//  Hopster Coding Interview
//
//  Created by Steve Longhurst on 22/02/2017.
//
//

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"


class MainScene : public cocos2d::Scene
{
    typedef cocos2d::Scene Super;
public:
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

    // scene initialisation
    virtual bool init();
    // scene shown
    virtual void onEnter();
    // scene hidden
    virtual void onExit();
    
    // called once per frame
    virtual void update( float delta );
        
    // mouse pressed down
    void onMouseDown( cocos2d::Event *event );
    // mouse button lifted
    void onMouseUp( cocos2d::Event *event );
    // mouse moved
    void onMouseMove( cocos2d::Event *event );
    // mouse scroll
    void onMouseScroll( cocos2d::Event *event );
    
    // Menu
    void onQuit (cocos2d::Ref *sender);
 
private:
 
    // Test to see if the mouse is over the player circle
    bool pointInCircle( const cocos2d::Point &p );
    cocos2d::Point getMousePositionFromEvent( cocos2d::Event *event );
    
    // Game state functions
    void startNewGame ();
    
private:
    
    cocos2d::EventListenerMouse* _mouseEventListener = NULL;
 
    // Store the display area size for good measure
    cocos2d::Size visibleSize;
 
    // Player circle to drag about
    cocos2d::DrawNode *circle;
    
    // Wall for the ball to bounce off of
    cocos2d::DrawNode *wall;
    
    // Character to fling the ball too
    cocos2d::Sprite *sprite_as_target;
    cocos2d::Sprite *sprite_on_target;
    cocos2d::Sprite *sprite_hit;
    
    // Final resting place of the ball once thrown
    cocos2d::DrawNode *endPoint;
    
    // Has the player picked the circle up
    bool pickedCircle;
    
    // Position of the mouse when the button is held down
    cocos2d::Point mousePos;
    
    // Position for the circle to bounce off of along the top of the screen
    cocos2d::Point bouncePoint;
    
    // Angles denoted by lines
    cocos2d::DrawNode *incident;
    cocos2d::DrawNode *reflect;
};

#endif
