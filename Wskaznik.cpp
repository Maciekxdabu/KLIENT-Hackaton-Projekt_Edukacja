#include "klasy.h"

Wskaznik::Wskaznik(std::string a)
{
    tekstura.loadFromFile(a);
    celownik.setTexture(tekstura);
}
sf::Sprite Wskaznik::getObraz()
{
    return celownik;
}
Wskaznik::~Wskaznik()
{
    ;
}
void Wskaznik::setPosition(float x, float y)
{
    celownik.setPosition(x,y);
}
