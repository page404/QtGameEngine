#include <QApplication>

#include "Game.h"
#include "Sprite.h"
#include "Spear.h"

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create a Map and a Game
    Map* map = new Map(15,15,64);
    game = new Game(map);
    game->launch();

    // create an Entity
    Entity* player = new Entity();
    map->addEntity(player);
    player->setCellPos(Node(2,2));

    // give the entity a sprite (overrides default one)
    Sprite* spr = new Sprite();
    player->setSprite(spr);
    spr->addFrames(":resources/graphics/human",1,"stand"); // stand anim
    spr->addFrames(":resources/graphics/human",6,"walk");  // walk anim
    spr->play("stand",1,1); // play stand anim

    // allow this Entity to be accessed by Entity* Game::player()
    // allow Entity to move in response to keyboard/mouse
    game->setPlayer(player);

    // add some attachment points for the player
    player->addNamedPoint(QPointF(-20,0),"left shoulder");
    player->addNamedPoint(QPointF(-20,50),"right shoulder");
    player->addNamedPoint(QPointF(25,25),"head");

    // attach spear to left shoulder of player Entity
    Spear* spear = new Spear();
    map->addEntity(spear);
    player->spear_ = spear;
    spear->setPointPos(player->namedPoint("left shoulder"));
    spear->setParentEntity(player);
    spear->setOwner(player);

    return a.exec();
}
