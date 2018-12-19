#include <SFML/Network.hpp>
#include <thread>
#include <iostream>
#include <cmath>

#include "klasy.h"

using namespace std;

#define PI 3.141592653589

sf::TcpSocket serwer;
bool polaczenie = false;

int ilosc_graczy;

bool klawisze[4];
float obrot;
sf::Texture graczT;
sf::Sprite player1, player2;

void connectTCP()
{
    while (serwer.connect("192.168.0.107", 38001) != sf::Socket::Done)
    {
        cout << "Oczekiwanie na polaczenie z serwerem" << endl;
    }

    sf::Packet paczka;
    while (serwer.receive(paczka))
    {
        ;
    }
    paczka >> ilosc_graczy;

    polaczenie = true;
}

void odbierz()
{
    sf::Packet paczka;

    while (serwer.receive(paczka) == sf::Socket::Done)
    {
        /*for (int i=0; i<ilosc_graczy; i++)
        {
            ;
        }*/

        float pozX, pozY, obr;

        paczka >> pozX >> pozY >> obr;
        player2.setPosition(pozX,pozY);
        player2.setRotation(obr);

        paczka >> pozX >> pozY >> obr;
        player1.setPosition(pozX,pozY);
        player1.setRotation(obr);
    }
}

void wyslij()
{
    sf::Packet paczka;

    for (int i=0; i<4; i++)
        paczka << klawisze[i];

    paczka << player1.getRotation();
}

int main()
{
    sf::RenderWindow okno(sf::VideoMode(800, 700, 32), "Projekt Edukacja KLIENT");

    Przeszkoda * przeszkoda[8];

    Wskaznik myszka("img/celownik.png");
    okno.setMouseCursorVisible(false);

    graczT.loadFromFile("img/gracz.png");
    player1.setTexture(graczT);
    player1.setPosition(200, 200);
    player1.setOrigin(25,25);
    player2.setTexture(graczT);
    player2.setPosition(250, 250);
    player2.setOrigin(25,25);

    for (int i=0; i<8; i++)
        przeszkoda[i] = new Przeszkoda("img/przeszkoda.png");

    przeszkoda[0]->setPosition(237,203);
    przeszkoda[1]->setPosition(518,203);
    przeszkoda[2]->setPosition(237,452);
    przeszkoda[3]->setPosition(518,452);
    przeszkoda[4]->setPosition(377,50);
    przeszkoda[5]->setPosition(705,327);
    przeszkoda[6]->setPosition(377,605);
    przeszkoda[7]->setPosition(50,327);

    while (okno.isOpen())
    {
        sf::Event zdarzenie;
        while (okno.pollEvent(zdarzenie))
        {
            if (zdarzenie.type == sf::Event::Closed)
            {
                okno.close();
            }
        }

        for (int i=0; i<4; i++)
            klawisze[i] = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            klawisze[0] = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            klawisze[2] = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            klawisze[1] = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            klawisze[3] = true;
        }

        myszka.setPosition(sf::Mouse::getPosition(okno).x,sf::Mouse::getPosition(okno).y);

        player1.setRotation( atan2(myszka.getObraz().getPosition().y - player1.getPosition().y,
                                   myszka.getObraz().getPosition().x - player1.getPosition().x )/PI*180 + 90 );


        okno.clear(sf::Color::White);

        okno.draw(player1);
        okno.draw(player2);
        okno.draw(myszka.getObraz());

        for (int i=0; i<8; i++)
            okno.draw(przeszkoda[i]->getObraz());

        okno.display();
    }

    return 0;
}