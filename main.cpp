#include <SFML/Network.hpp>
#include <thread>
#include <iostream>
#include <fstream>

#include "klasy.h"

using namespace std;

//#define PI 3.141592653589

sf::RenderWindow okno;

sf::TcpSocket serwer;
bool polaczenie = false;
bool zakonczone = false;

sf::Texture graczT;
int ilosc_graczy=0;
vector<sf::Sprite*> gracze;

sf::Texture pociskT;
int pociskow=0;
//vector<Pocisk*> pociski;
vector<sf::Sprite*> pociski;

bool klawisze[4];
float obrot;
bool wysylaj=false;

bool lewy;
float cooldown=-1;
sf::Clock zegar;
float deltaTime;

//sf::Sprite player1, player2;

fstream plik;
sf::IpAddress adres;

float Pocisk::R = 500;

void connectTCP()
{
    while (serwer.connect(adres, 38001) != sf::Socket::Done && polaczenie == false && zakonczone == false)
    {
        cout << "Oczekiwanie na polaczenie z serwerem" << endl;
    }

    /*sf::Packet paczka;
    while (serwer.receive(paczka))
    {
        ;
    }
    paczka >> ilosc_graczy;*/

    polaczenie = true;
}

void odbierz()
{
    while (zakonczone == false)
    {
        /*for (int i=0; i<ilosc_graczy; i++)
        {
            ;
        }*/

        sf::Packet paczka;

        if (polaczenie == true && serwer.receive(paczka) == sf::Socket::Done)
        {
            paczka >> ilosc_graczy;

            if (ilosc_graczy != gracze.size())
            {
                for (int i=0; i<gracze.size(); i++)
                    delete gracze[i];
                gracze.clear();

                float x, y, o;
                for (int i=0; i<ilosc_graczy; i++)
                {
                    sf::Sprite *bufor;
                    bufor = new sf::Sprite();
                    paczka >> x >> y >> o;

                    bufor->setTexture(graczT);
                    bufor->setOrigin(25, 25);
                    bufor->setPosition(x, y);
                    bufor->setRotation(o);

                    gracze.push_back(bufor);
                }
            }
            else
            {
                float x, y, o;
                for (int i=0; i<gracze.size(); i++)
                {
                    paczka >> x >> y >> o;
                    gracze[i]->setPosition(x, y);
                    gracze[i]->setRotation(o);
                }
            }

            paczka >> pociskow;

            if (pociskow != pociski.size())
            {
                for (int i=0; i<pociski.size(); i++)
                    delete pociski[i];
                pociski.clear();

                float x, y, o;
                for (int i=0; i<pociskow; i++)
                {
                    //Pocisk *bufor;
                    //bufor = new Pocisk(o, sf::Vector2f(x, y));
                    sf::Sprite *bufor;
                    bufor = new sf::Sprite();
                    paczka >> x >> y >> o;

                    bufor->setTexture(pociskT);
                    bufor->setOrigin(5, 5);
                    bufor->setPosition(x, y);
                    bufor->setRotation(o);

                    pociski.push_back(bufor);
                }
            }
            else
            {
                float x, y, o;
                for (int i=0; i<pociski.size(); i++)
                {
                    paczka >> x >> y >> o;
                    pociski[i]->setPosition(x, y);
                    pociski[i]->setRotation(o);
                }
            }

            //float pozX, pozY, obr;

            /*paczka >> pozX >> pozY >> obr;
            player1.setPosition(pozX,pozY);
            player1.setRotation(obr);

            paczka >> pozX >> pozY >> obr;
            player2.setPosition(pozX,pozY);
            player2.setRotation(obr);*/
        }
    }
}

void wyslij()
{
    while (zakonczone == false)
    {
        if (wysylaj == true && polaczenie == true)
        {
            sf::Packet paczka;

            for (int i=0; i<4; i++)
                paczka << klawisze[i];

            //paczka << player2.getRotation();
            paczka << sf::Mouse::getPosition(okno).x << sf::Mouse::getPosition(okno).y;

            paczka << lewy;

            if (lewy == true)
            {
                cooldown = 1;
                lewy = false;
            }

            if (serwer.send(paczka) == sf::Socket::Done)
                wysylaj = false;
        }
    }
}

int main()
{
    plik.open("adres.txt", ios::in);

    plik >> adres;

    plik.close();

    okno.create(sf::VideoMode(800, 700, 32), "Projekt Edukacja KLIENT");

    Przeszkoda * przeszkoda[8];

    //serwer.setBlocking(false);

    Wskaznik myszka("img/celownik.png");
    okno.setMouseCursorVisible(false);

    graczT.loadFromFile("img/gracz.png");
    pociskT.loadFromFile("img/pocisk.png");
    /*player1.setTexture(graczT);
    player1.setPosition(200, 200);
    player1.setOrigin(25,25);
    player2.setTexture(graczT);
    player2.setPosition(250, 250);
    player2.setOrigin(25,25);*/

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

    thread polacz(connectTCP);

    thread odbior(odbierz);
    thread wysylka(wyslij);

    zegar.restart();

    while (okno.isOpen())
    {
        sf::Event zdarzenie;
        while (okno.pollEvent(zdarzenie))
        {
            if (zdarzenie.type == sf::Event::Closed)
            {
                okno.close();
            }

            if (zdarzenie.type == sf::Event::MouseButtonPressed)
            {
                if (zdarzenie.mouseButton.button == sf::Mouse::Left && cooldown <= 0)
                {
                    lewy = true;
                }
            }
        }

        //for (int i=0; i<4; i++)
            //klawisze[i] = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            klawisze[0] = true;
        }
        else
            klawisze[0] = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            klawisze[2] = true;
        }
        else
            klawisze[2] = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            klawisze[1] = true;
        }
        else
            klawisze[1] = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            klawisze[3] = true;
        }
        else
            klawisze[3] = false;

        myszka.setPosition(sf::Mouse::getPosition(okno).x,sf::Mouse::getPosition(okno).y);

        //player2.setRotation( atan2(myszka.getObraz().getPosition().y - player2.getPosition().y,
        //                           myszka.getObraz().getPosition().x - player2.getPosition().x )/PI*180 + 90 );

        wysylaj = true;

        okno.clear(sf::Color::White);

        //okno.draw(player1);
        //okno.draw(player2);

        for (sf::Sprite *gracz: gracze)
            okno.draw(*gracz);

        for (sf::Sprite *pocisk: pociski)
            okno.draw(*pocisk);

        for (int i=0; i<8; i++)
            okno.draw(przeszkoda[i]->getObraz());

        okno.draw(myszka.getObraz());

        okno.display();

        if (cooldown > 0)
            cooldown -= deltaTime;

        deltaTime = zegar.restart().asSeconds();
    }

    polaczenie = false;
    zakonczone = true;

    polacz.join();
    wysylka.join();
    odbior.join();

    return 0;
}
