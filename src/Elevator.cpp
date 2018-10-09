#include "Elevator.h"

Elevator::Elevator()
{
    object.setSize(Vector2f(elevatorWidth, elevatorHeight));
	object.setFillColor(Color::Red);
	object.setPosition(elevatorPositionLeft + marginLeft, elevatorPositionTop + ((floors-1) * (elevatorHeight + border)));
}

int Elevator::border = houseBorder;

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

        if(getPosY() > elevatorPositionTop + (i * (elevatorHeight + border)) && getPosY() < elevatorPositionTop + ((i+1) * (elevatorHeight + border))) {
            return floors-i;
        } else if (getPosY() == elevatorPositionTop + ((i) * (elevatorHeight + border)) && getPosY()) {
            return floors-i;
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
    object.setPosition(elevatorPositionLeft + marginLeft, elevatorPositionTop + ((floors-1) * (elevatorHeight + border)));
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
    targetPosition = elevatorPositionTop + ((border + elevatorHeight)*(floors - requests[0].from));

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
    object.setPosition(getPosX(), getPosY() + speed);
}

void Elevator::moveDown()
{
    object.setPosition(getPosX(), getPosY() - speed);
}

void Elevator::drawHouse(RenderWindow &window)
{
    for( int i = 0; i < floors; i = i + 1 ) {
        RectangleShape house;
        house.setSize(Vector2f(elevatorWidth, elevatorHeight));
        house.setFillColor(Color::Transparent);
        house.setOutlineColor(Color::White);
        house.setOutlineThickness(border);
        house.setPosition(elevatorPositionLeft + marginLeft, elevatorPositionTop + (i*elevatorHeight)+(i*border));
        window.draw(house);
    }
}

void Elevator::drawElevator(RenderWindow &window)
{
   window.draw(object);
}

