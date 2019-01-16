#include "klasy.h"

Pocisk::Pocisk(float o, sf::Vector2f p)
{
    wektor.x = R*cos( (o-90)*PI/180 );
    wektor.y = R*sin( (o-90)*PI/180 );

    obraz.setPosition(p);
    obraz.setOrigin(5, 5);
    obraz.setTexture(pociskT);
    //obraz.setRotation(atan2(w.y, w.x)/PI*180 + 90);
    obraz.setRotation(o);
}

void Pocisk::ruch()
{
    obraz.move(wektor.x*deltaTime, wektor.y*deltaTime);
}

sf::Sprite Pocisk::getObraz()
{
    return obraz;
}

sf::Vector2f Pocisk::getPosition()
{
    return obraz.getPosition();
}

float Pocisk::getRotation()
{
    return obraz.getRotation();
}
