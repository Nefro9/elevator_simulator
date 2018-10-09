#include "Elevator.h"

Elevator::Elevator()
{
    object.setSize(Vector2f(elevatorWidth, elevatorHeight));
    object.setFillColor(Color::Red);
    object.setPosition(elevatorPositionLeft + marginLeft, elevatorPositionTop + ((floors-1) * (elevatorHeight + border)));
}

int Elevator::border = houseBorder;

// Temp params used in sort
int tCurrentFloor;
int tStatus;

bool sortRequest(request i, request j) {

    if(tStatus == 2) {
        if(i.from > j.from && tCurrentFloor > i.from){
            return true;
        } else {
            return false;
        }
    } else {
        if(i.from < j.from && tCurrentFloor < i.from){
            return true;
        } else {
            return false;
        }
    }
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


    tCurrentFloor = getFloor();
    tStatus       = status;

    sort(requests.begin(), requests.end(), sortRequest);
}



void Elevator::updateStatus()
{
    targetPosition = elevatorPositionTop + ((border + elevatorHeight)*(floors - requests[0].from));


    if(getPosY() > targetPosition) {

        status = statusUP;
        object.setFillColor(Color::Yellow);

    } else if(getPosY() < targetPosition)  {
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
    if(status == statusUP && targetPosition < getPosY())
    {
        moveUp();
    }
    else if (status == statusDOWN && targetPosition > getPosY())
    {
        moveDown();
    }
}

void Elevator::moveUp()
{
    object.setPosition(getPosX(), getPosY() - speed);
}

void Elevator::moveDown()
{
    object.setPosition(getPosX(), getPosY() + speed);
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

void Elevator::drawRequests(RenderWindow &window, Text text, string prefix)
{
    string requestsText = "";
    string requestsIn = prefix + "requests in: ";
    string requestsOut = prefix + "requests out: ";


    for( int i = 0; i < requests.size(); i = i + 1 ) {

        if(requests[i].to == 0) {
            requestsOut += std::to_string(requests[i].from) + ", ";
        } else {
            requestsIn += std::to_string(requests[i].from) + ", ";
            requestsOut += std::to_string(requests[i].to) + ", ";
        }
    }

    if(requestsIn.size() != 12) {
        requestsIn = requestsIn.substr(0, requestsIn.size()-2);
    }

    if(requestsOut.size() != 13) {
        requestsOut = requestsOut.substr(0, requestsOut.size()-2);
    }

    requestsText = requestsIn + "\n" + requestsOut;

    text.setString(requestsText);
    window.draw(text);
}


string Elevator::getStatusText()
{
    if(status == statusIDLE) {
        return "IDLE";
    } else if (status == statusUP) {
        return "go up";
    } else if (status == statusDOWN) {
        return "go down";
    }
}