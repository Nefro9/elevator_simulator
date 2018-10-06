#include "Elevator.h"

Elevator::Elevator()
{
    object.setSize(Vector2f(elevatorWidth, elevatorHeight));
	object.setFillColor(Color::Red);
	object.setPosition(elevatorPositionLeft + marginLeft, elevatorPositionTop + ((floors-1) * (elevatorHeight + 10)));
}

float Elevator::getPosX()
{
    return object.getPosition().x;
}


float Elevator::getPosY()
{
    return object.getPosition().y;
}

float Elevator::getFloor()
{
    for( int i = 0; i < floors; i = i + 1 ) {

        if(getPosY() > elevatorPositionTop + (i * (elevatorHeight + 10)) && getPosY() < elevatorPositionTop + ((i+1) * (elevatorHeight + 10))) {
            return 4-i;
        } else if (getPosY() == elevatorPositionTop + ((i) * (elevatorHeight + 10)) && getPosY()) {
            return 5-i;
        }
    }

    return 0;
}

bool Elevator::haveRequest()
{
    if(requests.size() > 0) {
        return true;
    } else {
        return false;
    }
}

void Elevator::addMargin()
{
    marginLeft = elevatorPositionMargin;
    object.setPosition(elevatorPositionLeft + marginLeft, elevatorPositionTop + ((floors-1) * (elevatorHeight + 10)));
}

void Elevator::addRequest(int floorFrom, int floorTo)
{
    request newRequest = {floorFrom, floorTo};
    requests.push_back(newRequest);


    std::cout << "___________" << std::endl;

    for( int i = 0; i < requests.size(); i = i + 1 ) {
        std::cout << i << ". From :" << requests[i].from << std::endl;
        std::cout << i << ". To :" << requests[i].to << std::endl;

    }
}


void Elevator::updateStatus()
{
    targetPosition = elevatorPositionTop + ((10 + elevatorHeight)*(5 - requests[0].from));

    if(getPosY() < targetPosition) {

        status = statusUP;
        object.setFillColor(Color::Yellow);

    } else if(getPosY() > targetPosition)  {
        object.setFillColor(Color::Blue);
        status = statusDOWN;

    } else {

        if(sleep != 0) {
            sleep -= 1;
        } else {

            if(requests[0].to != 0) {
                addRequest(requests[0].to, 0);

            }

            requests.erase(requests.begin());
            sleep = sleepTime;

            object.setFillColor(Color::Red);
            status = statusIDLE;
        }
    }
}

void Elevator::move()
{
    if(status == statusUP && targetPosition > getPosY()) {

        moveUp();
    } else if (status == statusDOWN && targetPosition < getPosY()) {

        moveDown();
    }
}

void Elevator::moveUp()
{
    object.setPosition(getPosX(), getPosY() + 1);
}

void Elevator::moveDown()
{
    object.setPosition(getPosX(), getPosY() - 1);
}

void Elevator::drawHouse(sf::RenderWindow &window)
{
    for( int i = 0; i < floors; i = i + 1 ) {
        RectangleShape house;
        house.setSize(Vector2f(elevatorWidth, elevatorHeight));
        house.setFillColor(Color::Transparent);
        house.setOutlineColor(Color::White);
        house.setOutlineThickness(10);
        house.setPosition(elevatorPositionLeft + marginLeft, elevatorPositionTop + (i*elevatorHeight)+(i*10));
        window.draw(house);
    }

}

void Elevator::drawElevator(sf::RenderWindow &window)
{
   window.draw(object);
}

