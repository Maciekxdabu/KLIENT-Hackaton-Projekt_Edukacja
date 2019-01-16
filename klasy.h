#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 3.141592653589

extern sf::Texture pociskT;
extern float deltaTime;

class Przeszkoda
{
    protected:

        sf::Sprite obraz;
        sf::Texture tekstura;

    public:

        Przeszkoda(std::string);
        ~Przeszkoda();
        sf::Sprite getObraz();
        void setPosition(float,float);
};

class Wskaznik
{
    protected:

        sf::Sprite celownik;
        sf::Texture tekstura;

    public:
        Wskaznik(std::string);
        ~Wskaznik ();
        sf::Sprite getObraz();
        void setPosition(float,float);
};

class Pocisk
{
protected:
    sf::Vector2f wektor;
    sf::Sprite obraz;

    static float R;

public:
    Pocisk(float, sf::Vector2f);
    void ruch();
    sf::Sprite getObraz();
    sf::Vector2f getPosition();
    float getRotation();
    void setPostition();
    void setRotation();
};
