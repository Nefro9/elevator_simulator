#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include "SFML\Graphics.hpp"


using namespace sf;
using namespace std;

namespace {
    const int elevatorWidth = 40;
    const int elevatorHeight = 60;

    const int houseBorder = 5;

    const int elevatorPositionLeft = 50;
    const int elevatorPositionTop = 100;

    const int elevatorPositionMargin = 350; // Space between elevators

    const float speed = 0.5;

    const int sleepTime = 60; // sleep time on arrive position

    const int floors = 7;

    const int statusIDLE    = 0;
    const int statusUP      = 1;
    const int statusDOWN    = 2;
}

class Elevator
{
    RectangleShape object;

    int marginLeft = 0;
    int targetPosition;
    int sleep = sleepTime;

     struct request
    {
        int from;
        int to;
    };

    vector<request> requests;

    public:
        int status = statusIDLE;

        static int border;

        Elevator();

        float getPosX();
        float getPosY();
        float getFloor();

        bool haveRequest();

        void addMargin();
        void addRequest(int floorFrom, int floorTo);
        void updateStatus();

        void move();
        void moveUp();
        void moveDown();

        void drawHouse(sf::RenderWindow &window);
        void drawElevator(sf::RenderWindow &window);
};

#endif // ELEVATOR_H
