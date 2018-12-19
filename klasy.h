#include <SFML/Graphics.hpp>

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
