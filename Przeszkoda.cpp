#include "klasy.h"

Przeszkoda::Przeszkoda(std::string a)
{
    tekstura.loadFromFile(a);
    obraz.setTexture(tekstura);
}

Przeszkoda::~Przeszkoda()
{
    ;
}

sf::Sprite Przeszkoda::getObraz()
{
    return obraz;
}

void Przeszkoda::setPosition(float x,float y)
{
    obraz.setPosition(x,y);
}
