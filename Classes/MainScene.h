//
//  MainScene.h
//  ExpJam
//
//  Created by Two Tails on 09/12/2014.
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
 
private:
 
    // Test to see if the mouse is over the player circle
    bool pointInCircle( const cocos2d::Point &p );
    cocos2d::Point getMousePositionFromEvent( cocos2d::Event *event );
    
private:
    
    cocos2d::EventListenerMouse* _mouseEventListener = NULL;
 
    // Store the display area size for good measure
    cocos2d::Size visibleSize;
 
    // Player circle to drag about
    cocos2d::DrawNode *circle;
    
    // Has the player picked the circle up
    bool picked;
    
    // Position of the mouse when the button is held down
    cocos2d::Point mousePos;
};

#endif
