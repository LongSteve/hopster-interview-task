//
//  HelpScene.cpp
//  ExpJam
//
//  Created by Stephen Longhurst on 22/02/2017.
//
//

#include "Constants.h"
#include "HelpScene.h"
#include "MenuScene.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool HelpScene::init()
{
    // super init first
    if ( !Super::init() )
    {
        return false;
    }
    
    // get visible size of window
    Size visibleSize = Director::getInstance()->getVisibleSize();
 
    Size sz;
 
    auto text = Label::createWithTTF("Instructions", "Marker Felt.ttf", 72);
    
    Point textPosition( visibleSize.width / 2, visibleSize.height - text->getLineHeight() );
    
    text->setPosition( textPosition );
    this->addChild( text );
 
    auto item1 = MenuItemImage::create ("ButtonBlue.png", "ButtonGreen.png", CC_CALLBACK_0(HelpScene::onBack,this,std::placeholders::_1));
    auto label1 = Label::createWithTTF ("Back", "Marker Felt.ttf", 48);
    label1->setAnchorPoint(Vec2 (0.5, 0.5));
    sz = item1->getContentSize();
    label1->setPosition (sz.width / 2, sz.height / 2);
    item1->addChild (label1);
    
    std::string help_text = "To play 'Angle of Bounce', you have to guess where to place the spikey ball.";
    help_text += "\nGrab it with the mouse and move it around by holding the button down.";
    help_text += "\nSend the ball off by clicking the 'fire', and try to hit the poor little star.";
    help_text += "\nGood luck, and click the bomb to return to the main menu at any time.";
    
    auto help = Label::createWithTTF(help_text, FONT_TTF_FILE, 24);
    textPosition.y -= (text->getLineHeight () * 2);
    help->setPosition (textPosition);
    this->addChild (help);
    
    auto menu = Menu::create (item1, nullptr);
    menu->alignItemsVertically ();
    this->addChild (menu, 100);
    menu->setPositionY(menu->getPositionY() - sz.height / 2);
 
    auto leaf1 = Sprite::create ("Leaf1.png");
    leaf1->setAnchorPoint (Vec2 (0,1));
    leaf1->setPosition (0, visibleSize.height);
    leaf1->setOpacity (128);
    this->addChild (leaf1);

    auto leaf6 = Sprite::create ("Leaf6.png");
    leaf6->setAnchorPoint (Vec2 (1,0));
    leaf6->setPosition (visibleSize.width, 0);
    leaf6->setOpacity (128);
    this->addChild (leaf6);
 
    // done
    return true;
}

#pragma mark - Menu Actions

void HelpScene::onBack (Ref *sender)
{
    auto menuScene = MenuScene::create ();
    Director::getInstance ()->replaceScene (TransitionFade::create (0.5, menuScene, Color3B (0,0,0)));
}

void HelpScene::onEnter()
{
    Super::onEnter();
}

void HelpScene::onExit()
{
    Super::onExit();
    
}
