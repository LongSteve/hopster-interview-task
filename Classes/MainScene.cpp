//
//  MainScene.cpp
//  Hopster Coding Interview
//
//  Created by Steve Longhurst on 22/02/2017.
//
//

#include "Constants.h"
#include "MenuScene.h"
#include "MainScene.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MainScene::init()
{
    // super init first
    if ( !Super::init() )
    {
        return false;
    }
    
    // get visible size of window
    visibleSize = Director::getInstance()->getVisibleSize();
 
    // Background colour
    LayerColor *lc = LayerColor::create (BACKGROUND_COLOR);
    this->addChild (lc);
    
    // Create a bomb 'button' in the top right corner of the screen to exit the scene
    auto bomb_sprite_normal = Sprite::create ("Bomb1.png");
    auto bomb_sprite_selected = Sprite::create ("Bomb1Red.png");
    bomb_sprite_normal->setScale (0.5f);
    bomb_sprite_selected->setScale (0.5f);
    Size sz = bomb_sprite_normal->getContentSize();
    auto bombMenuItem = MenuItemSprite::create ( bomb_sprite_normal, bomb_sprite_selected, CC_CALLBACK_0(MainScene::onQuit, this, std::placeholders::_1) );
    
    // Create a 'fire' button in the bottom left of the screen to fire the ball with
    Vector<SpriteFrame *>fireFrames(2);
    fireFrames.pushBack( SpriteFrame::create( "Flame1.png", Rect( 0,0,230,291 ) ) );
    fireFrames.pushBack( SpriteFrame::create( "Flame2.png", Rect( 0,0,230,291 ) ) );
    auto fireAnimation = Animation::createWithSpriteFrames( fireFrames, 0.2f );
    fireAnimation->setLoops( -1 );
    auto animate = Animate::create( fireAnimation );
    auto fireSprite = Sprite::create();
    fireSprite->runAction( animate );
    fireSprite->setScale( 0.4f );
    fireSprite->setContentSize( Size( 230 * 0.4, 291 * 0.4 ) );

    auto fireSpriteSelect = Sprite::create();
    fireSpriteSelect->runAction( animate->clone() );
    fireSpriteSelect->setScale( 0.4f );
    fireSpriteSelect->setContentSize( Size( 230 * 0.4, 291 * 0.4 ) );
    fireSpriteSelect->setColor( Color3B( 0,200,0 ) );
    auto fireMenuItem = MenuItemSprite::create (fireSprite, fireSpriteSelect, CC_CALLBACK_0(MainScene::onFire, this, std::placeholders::_1) );
    
    // add a menu item to handle clicking on the bomb or the fire
    auto menu = Menu::create( fireMenuItem, bombMenuItem, nullptr );
    menu->alignItemsHorizontallyWithPadding( 100.0f );
    Size mz = menu->getContentSize();

    // Take into account the menu is normally slapped in the center of the screen
    fireMenuItem->setPosition(-visibleSize.width / 2 + (230 * 0.2), -visibleSize.height / 2 + (291 * 0.2) + 10);
    bombMenuItem->setPosition(visibleSize.width / 2 - 10, visibleSize.height / 2);
    
    this->addChild (menu);
    
    // Load the red blob sprite for the 'target'
    sprite_as_target = Sprite::create( "Petal-Happy.png" );
    sprite_as_target->setAnchorPoint (Point (1.0, 0.0));
    sprite_as_target->setScale (0.25);
    sprite_as_target->setPosition (visibleSize.width,0);
    this->addChild (sprite_as_target, 100);
    
    sprite_on_target = Sprite::create( "Petal-Concern.png" );
    sprite_on_target->setAnchorPoint (Point (1.0, 0.0));
    sprite_on_target->setScale (0.25);
    sprite_on_target->setPosition (visibleSize.width,0);
    sprite_on_target->setVisible( false );
    this->addChild (sprite_on_target, 100);
    
    sprite_hit = Sprite::create( "Petal-Bump.png" );
    sprite_hit->setAnchorPoint (Point (1.0, 0.0));
    sprite_hit->setScale (0.25);
    sprite_hit->setPosition (visibleSize.width,0);
    sprite_hit->setVisible( false );
    this->addChild (sprite_hit, 100);
    
    // Some background fauna, like the menu
    auto leaf1 = Sprite::create ("Leaf1.png");
    leaf1->setAnchorPoint (Vec2 (0,1));
    leaf1->setPosition (0, visibleSize.height);
    leaf1->setOpacity(128);
    this->addChild (leaf1);

    auto leaf6 = Sprite::create ("Leaf6.png");
    leaf6->setAnchorPoint (Vec2 (1,0));
    leaf6->setPosition (visibleSize.width, 0);
    leaf6->setOpacity(128);
    this->addChild (leaf6);
    
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
    
    // start a new game
    startNewGame();
    
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

void MainScene::startNewGame()
{
    // A circle for the player to drag about at 0,0
    circle = DrawNode::create ();
    circle->drawDot( Vec2 (0,0), CIRCLE_RADIUS, CIRCLE_REST_COLOR );
    circle->setPosition( CIRCLE_RADIUS * 4, CIRCLE_RADIUS * 4);
    this->addChild (circle, 200);
    
    // Add a nice sprite to the circle
    auto spike_ball = Sprite::create( "SpikeBall1.png" );
    spike_ball->setScale( 0.75f );
    circle->addChild (spike_ball);
    
    // The point it will bounce off of, at a random position on the top of the screen
    int rMax = visibleSize.width - WALL_LENGTH;
    int rMin = (WALL_LENGTH / 2);
    int rnd = arc4random () % (rMax-rMin) + rMin;
    bouncePoint = Point (rnd, visibleSize.height);
    
    // Draw a solid 'line' or 'wall' at this point
    wall = DrawNode::create ();
    
    std::vector<Vec2> verts;
    verts.push_back (Vec2 (0,-10));
    verts.push_back (Vec2 (0,10));
    verts.push_back (Vec2 (WALL_LENGTH,10));
    verts.push_back (Vec2 (WALL_LENGTH,-10));
    
    wall->drawPolygon( verts.data(), 4, Color4F (0,0,0,1.0), 2, Color4F (1.0,1.0,1.0,1.0) );
    wall->setPosition (bouncePoint);
    this->addChild (wall);
    
    // Add an incident angle from the ball to the wall
    incident = DrawNode::create ();
    this->addChild (incident);
    
    // Add the relected angle
    reflect = DrawNode::create ();
    this->addChild (reflect);
    
    // The end point
    endPoint = DrawNode::create ();
    endPoint->drawDot( Vec2 (0,0), CIRCLE_RADIUS, TARGET_COLOR );
    endPoint->setPosition( CIRCLE_RADIUS, CIRCLE_RADIUS );
    this->addChild (endPoint);
    
    pickedCircle = false;
    shotTaken = false;
    onTarget = false;
}

void MainScene::update( float delta )
{
    if( shotTaken )
    {
        return;
    }
    
    // Is the player moving the circle around
    if( pickedCircle )
    {
        // Limit the circle position
        if( mousePos.x >= 0 && mousePos.x < visibleSize.width && mousePos.y >= 0 && mousePos.y < visibleSize.height)
        {
            circle->setPosition (mousePos);
        }
    }
    
    // Draw the incident angle (from the ball to the wall)
    incident->clear ();
    auto start = circle->getPosition ();
    auto end = wall->getPosition();
    end.x += WALL_LENGTH / 2;
    incident->drawSegment(start, end, 2, Color4F( 1.0, 0.0, 1.0, 1.0));

    // Reflect the angle in the x axis to determine the reflected vector
    reflect->clear ();
    auto r_start = wall->getPosition();
    r_start.x += WALL_LENGTH / 2;
    Point r_end;
    r_end.y = start.y;
    r_end.x = end.x + (end.x - start.x);
    
    // Normalise the incident to shorten it so it's not obvious where it might end
    Vec2 norm (r_end.x - r_start.x, r_end.y - r_start.y);
    norm.normalize();
    norm.scale (WALL_LENGTH);
    
    incident->drawSegment(r_start, r_start + norm, 2, Color4F( 0.8, 0.8, 0.0, 1.0));
    
    // Take into account the sprite size, and the fact it's anchored bottom right
    Size sprite_sz = sprite_as_target->getContentSize() * sprite_as_target->getScale();
    Point target_s = sprite_hit->getPosition();
    target_s.x -= sprite_sz.width / 2;
    target_s.y += sprite_sz.height / 2;
    
    // Work out a vector to hit the target
    Vec2 target_r = target_s - r_start;
    Vec2 target_v( r_end.x - r_start.x, r_end.y - r_start.y );
    target_v.normalize();
    target_v.scale( target_r.length() );
    
    // If the reflected vector is over the target, then change it's sprite to 'concern'
    Point target = r_start + target_v;
    float dx = target_s.x - target.x;
    float dy = target_s.y - target.y;
    if (sqrtf( dx * dx + dy * dy) < CIRCLE_RADIUS)
    {
        sprite_as_target->setVisible( false );
        sprite_on_target->setVisible( true );
        onTarget = true;
    }
    else
    {
        sprite_as_target->setVisible( true );
        sprite_on_target->setVisible( false );
        onTarget = false;
    }
    
    endPoint->setPosition( target );
}

#pragma mark - Menu Methods

void MainScene::onQuit(Ref *sender)
{
    cocos2d::log ("quit game");
    auto scene = MenuScene::create ();
    Director::getInstance ()->replaceScene (TransitionFade::create (0.5, scene, Color3B (0,0,0)));
}

void MainScene::onFire(Ref *sender)
{
    if( shotTaken )
    {
        return;
    }
    
    // trigger the ball moving
    shotTaken = true;
    
    // Hide the lines
    reflect->setVisible( false );
    incident->setVisible( false );
    endPoint->setVisible( false );
    
    // Calculate the ball movement path
    auto r_start = wall->getPosition();
    r_start.x += WALL_LENGTH / 2;
    auto movement1 = MoveTo::create (1.0f, r_start);
    auto ease1 = EaseIn::create (movement1, 0.75f);
    auto movement2 = MoveTo::create (1.0f, endPoint->getPosition());
    auto ease2 = EaseIn::create (movement2, 0.75f);
    auto complete = CallFunc::create( [&] ( ) {
        this->fireEnd ();
    });
    auto sequence = Sequence::create (ease1, ease2, complete, nullptr);
    circle->runAction (sequence);
    
    auto spike_ball = circle->getChildren().at (0);
    auto rotate = RotateBy::create( 1.0f, 360.0f);
    spike_ball->runAction( RepeatForever::create( rotate ) );
}

void MainScene::fireEnd ()
{
    circle->runAction (ScaleTo::create (0.5f, 0.0f));
    std::string finishedText;

    if( onTarget )
    {
        finishedText = "Well Done - 100 Points";
        
        sprite_as_target->setVisible( false );
        sprite_on_target->setVisible( false );
        sprite_hit->setVisible( true );
    }
    else
    {
        finishedText = "Unlucky - 0 Points";
    }
    
    finishedLabel = Label::createWithTTF(finishedText, FONT_TTF_FILE, 72);
    finishedLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    finishedLabel->setScale (0.0f);
    
    auto complete = CallFunc::create( [&] ( ) {
        this->onQuit (NULL);
    });
    
    auto sequence = Sequence::create( EaseBounceOut::create(ScaleTo::create(1.0f, 1.0f)), DelayTime::create (2.0f), complete, nullptr );
    finishedLabel->runAction (sequence);
    this->addChild (finishedLabel, 500);
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
    if( shotTaken )
    {
        return;
    }
    
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
    if( shotTaken )
    {
        return;
    }

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
