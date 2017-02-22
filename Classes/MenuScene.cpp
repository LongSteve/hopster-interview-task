//
//  MenuScene.cpp
//  ExpJam
//
//  Created by Stephen Longhurst on 22/02/2017.
//
//

#include "MenuScene.h"
#include "MainScene.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool MenuScene::init()
{
    // super init first
    if ( !Super::init() )
    {
        return false;
    }
    
    // get visible size of window
    Size visibleSize = Director::getInstance()->getVisibleSize();
 
    Size sz;
 
    auto text = Label::createWithTTF("Main Menu", "Marker Felt.ttf", 72);
    text->setPosition( Vec2( visibleSize.width / 2, visibleSize.height - text->getLineHeight() ) );
    this->addChild( text );
 
    auto item1 = MenuItemImage::create ("ButtonBlue.png", "ButtonGreen.png", CC_CALLBACK_0(MenuScene::onStart,this,std::placeholders::_1));
    auto label1 = Label::createWithTTF ("Play Game", "Marker Felt.ttf", 48);
    label1->setAnchorPoint(Vec2 (0.5, 0.5));
    sz = item1->getContentSize();
    label1->setPosition (sz.width / 2, sz.height / 2);
    item1->addChild (label1);
 
    auto item2 = MenuItemImage::create ("ButtonBlue.png", "ButtonGreen.png", CC_CALLBACK_0(MenuScene::onHelp,this,std::placeholders::_1));
    auto label2 = Label::createWithTTF ("Instructions", "Marker Felt.ttf", 48);
    label2->setAnchorPoint(Vec2 (0.5, 0.5));
    sz = item2->getContentSize();
    label2->setPosition (sz.width / 2, sz.height / 2);
    item2->addChild (label2);
 
    auto item3 = MenuItemImage::create ("ButtonBlue.png", "ButtonGreen.png", CC_CALLBACK_0(MenuScene::onQuit,this,std::placeholders::_1));
    auto label3 = Label::createWithTTF ("Quit Game", "Marker Felt.ttf", 48);
    label3->setAnchorPoint(Vec2 (0.5, 0.5));
    sz = item3->getContentSize();
    label3->setPosition (sz.width / 2, sz.height / 2);
    item3->addChild (label3);
 
    auto menu = Menu::create (item1, item2, item3, nullptr);
    menu->alignItemsVertically ();
    this->addChild (menu, 100);
    menu->setPositionY(menu->getPositionY() - sz.height / 2);
 
    auto leaf1 = Sprite::create ("Leaf1.png");
    leaf1->setAnchorPoint (Vec2 (0,1));
    leaf1->setPosition (0, visibleSize.height);
    this->addChild (leaf1);

    auto leaf6 = Sprite::create ("Leaf6.png");
    leaf6->setAnchorPoint (Vec2 (1,0));
    leaf6->setPosition (visibleSize.width, 0);
    this->addChild (leaf6);
 
    // done
    return true;
}

#pragma mark - Menu Actions

void MenuScene::onStart (Ref *sender)
{
    auto mainScene = MainScene::create ();
    Director::getInstance ()->replaceScene (TransitionFade::create (0.5, mainScene, Color3B (0,0,0)));
}

void MenuScene::onHelp (Ref *sender)
{
}

void MenuScene::onQuit (Ref *sender)
{
   Director::getInstance()->end();
   #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
      exit(0);
   #endif
}

void MenuScene::onEnter()
{
    Super::onEnter();
}

void MenuScene::onExit()
{
    Super::onExit();
    
}
