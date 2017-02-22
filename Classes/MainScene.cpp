//
//  MainScene.cpp
//  Hopster Coding Interview
//
//  Created by Steve Longhurst on 22/02/2017.
//
//

#include "MainScene.h"


USING_NS_CC;

#define CIRCLE_RADIUS 40

#define BACKGROUND_COLOR Color4B (128,128,128,255)
#define CIRCLE_REST_COLOR Color4F (0.5,0,0,1.0)
#define CIRCLE_HOVER_COLOR Color4F (0.0,1.0,0,1.0)
#define CIRCLE_PICKED_COLOR Color4F (0.0,0.0,1.0,1.0)

// on "init" you need to initialize your instance
bool MainScene::init()
{
    // super init first
    if ( !Super::init() )
    {
        return false;
    }
    
    // Member variable init
    pickedCircle = false;
    
    // get visible size of window
    visibleSize = Director::getInstance()->getVisibleSize();
 
    // Background colour
    LayerColor *lc = LayerColor::create (BACKGROUND_COLOR);
    this->addChild (lc);
 
    // A circle for the player to drag about
    circle = DrawNode::create ();
    circle->drawDot (Vec2 (0,0), CIRCLE_RADIUS, CIRCLE_REST_COLOR);
    this->addChild (circle);
 
    // done
    return true;
}

void MainScene::onEnter()
{
    Super::onEnter();
 
    // create a mouse event listener
    if( _mouseEventListener == NULL )
    {
        _mouseEventListener = EventListenerMouse::create();
        _mouseEventListener->onMouseMove = CC_CALLBACK_1( MainScene::onMouseMove, this );
        _mouseEventListener->onMouseUp = CC_CALLBACK_1( MainScene::onMouseUp, this );
        _mouseEventListener->onMouseDown = CC_CALLBACK_1( MainScene::onMouseDown, this );
        _mouseEventListener->onMouseScroll = CC_CALLBACK_1( MainScene::onMouseScroll, this );
    }
    
    // register event listeners
    _eventDispatcher->addEventListenerWithSceneGraphPriority( _mouseEventListener, this );
    
    // schedule update calls
    scheduleUpdate();
}

void MainScene::onExit()
{
    Super::onExit();
    
    // de-register event listeners
    _eventDispatcher->removeEventListener( _mouseEventListener );
    
    // unschedule update
    unscheduleUpdate();
}

void MainScene::update( float delta )
{
    // Is the player moving the circle around
    if( pickedCircle )
    {
        // Limit the circle position
        if( mousePos.x >= 0 && mousePos.x < visibleSize.width && mousePos.y >= 0 && mousePos.y < visibleSize.height)
        {
            circle->setPosition (mousePos);
        }
    }
}

#pragma mark - Private Methods

bool MainScene::pointInCircle (const Point &p)
{
    float dx = circle->getPositionX() - p.x;
    float dy = circle->getPositionY() - p.y;
    
    if( sqrtf (dx*dx + dy*dy) < CIRCLE_RADIUS )
    {
        return true;
    }
    
    return false;
}

Point MainScene::getMousePositionFromEvent( Event *event )
{
    EventMouse* e = (EventMouse*)event;

    // Cocos2d-x returns mouse coordinates in OpenGL space, which has the y axis inverted.  Not sure why this is!
    Point cursorPos( e->getCursorX(), visibleSize.height + e->getCursorY() );
    
    return cursorPos;
}

#pragma mark - Mouse Events


void MainScene::onMouseDown( Event *event )
{
    Point pos = getMousePositionFromEvent (event);
    if (pointInCircle (pos))
    {
        circle->clear();
        circle->drawDot( Vec2 (0,0), CIRCLE_RADIUS, CIRCLE_PICKED_COLOR );
        pickedCircle = true;
    }
    mousePos = pos;
}

void MainScene::onMouseUp( Event *event )
{
    pickedCircle = false;
}

void MainScene::onMouseMove( Event *event )
{
    // Cocos2d-x returns mouse coordinates in OpenGL space, which has the y axis inverted.  Not sure why this is!
    Point pos = getMousePositionFromEvent (event);
    
    // check to see if the cursor is over the player circle
    if (pointInCircle (pos))
    {
        circle->clear ();
        circle->drawDot( Vec2 (0,0), CIRCLE_RADIUS, pickedCircle ? CIRCLE_PICKED_COLOR : CIRCLE_HOVER_COLOR);
    }
    else
    {
        circle->clear ();
        circle->drawDot (Vec2 (0,0), CIRCLE_RADIUS, CIRCLE_REST_COLOR);
    }
    
    mousePos = pos;
}

void MainScene::onMouseScroll( Event *event )
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Scroll detected, X: ";
    str += std::to_string(e->getScrollX()) + " Y: " + std::to_string(e->getScrollY());
    cocos2d::log( "%s", str.c_str() );
}
