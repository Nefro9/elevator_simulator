#include <iostream>
#include "Elevator.h"

using namespace sf;
using namespace std;

void addRequest(Elevator &eleLeft, Elevator &eleRight);
void drawMenu(RenderWindow &window);

namespace {
    const int windowWidth = 500;
    const int windowHeight = 700;
}


int floorGoFrom = 1;
int floorGoTo[floors];


Text menu[floors];
Text floorNumbers[floors];
Font font;

int main()
{
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Evelator simulator");
	window.setFramerateLimit(60);

    Elevator elevatorLeft, elevatorRight;

    elevatorRight.addMargin();


    // Create middle menu and floor numbers
    for( int i = 0; i < floors; i = i + 1 ) {
        Text text;
        text.setFont(font);
        text.setCharacterSize(14);
        text.setFillColor(Color::White);
        text.setPosition(elevatorPositionLeft + 135,  elevatorPositionTop + (elevatorHeight/2) + (i * (Elevator::border + elevatorHeight)) - (Elevator::border*2));

        menu[i] = text;

        Text floorText;
        floorText.setFont(font);
        floorText.setCharacterSize(14);
        floorText.setFillColor(Color::White);
        floorText.setPosition(elevatorPositionLeft - Elevator::border - 15,  elevatorPositionTop + elevatorHeight + (i * (Elevator::border + elevatorHeight)) - (Elevator::border*2) - 15);
        floorText.setString(std::to_string(floors - i));

        floorNumbers[i] = floorText;

        // Set default 1 floor
        floorGoTo[i] = 1;
    }

    if (!font.loadFromFile("resources/sansation.ttf"))
        return EXIT_FAILURE;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case Keyboard::Down:
                        if(floorGoFrom == floors) {
                            floorGoFrom = 1;
                        } else {
                            floorGoFrom += 1;
                        }
                        break;
                    case Keyboard::Up:
                        if(floorGoFrom == 1) {
                            floorGoFrom = floors;
                        } else {
                            floorGoFrom -= 1;
                        }
                        break;
                    case Keyboard::Right:
                        if(floorGoTo[floorGoFrom-1] >= floors) {
                            floorGoTo[floorGoFrom-1] = 1;
                        } else {
                            floorGoTo[floorGoFrom-1] += 1;
                        }
                        break;
                    case Keyboard::Left:
                        if(floorGoTo[floorGoFrom-1] <= 1) {
                            floorGoTo[floorGoFrom-1] = floors;
                        } else {
                            floorGoTo[floorGoFrom-1] -= 1;
                        }
                        break;
                    case Keyboard::Enter:
                        addRequest(elevatorLeft, elevatorRight);
                        break;
                    default: break;
                }
            }

			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		// Display menu

		drawMenu(window);



        if(elevatorLeft.haveRequest()) {
            elevatorLeft.updateStatus();
            elevatorLeft.move();
        }


        if(elevatorRight.haveRequest()) {
            elevatorRight.updateStatus();
            elevatorRight.move();
        }

		elevatorLeft.drawElevator(window);
		elevatorLeft.drawHouse(window);

		elevatorRight.drawHouse(window);
		elevatorRight.drawElevator(window);


		window.display();
	}

	return 0;
}

void drawMenu(RenderWindow &window)
{
    for( int i = 0; i < sizeof(menu)/sizeof(*menu); i = i + 1 ) {
        std::string result;

        if(floorGoFrom == i + 1) {

            menu[i].setFillColor(Color::Yellow);
        } else {
            menu[i].setFillColor(Color::White);
        }
        result += " Keliauti i  " + std::to_string(floorGoTo[i]) + " auksta ";

        menu[i].setString(result);

        window.draw(menu[i]);

        window.draw(floorNumbers[i]);
    }

}


void addRequest(Elevator &eleLeft, Elevator &eleRight)
{
    int closest, from, to, direction;

    //Get closest elevator
    if(abs(eleLeft.getFloor() - ((floors+1)-floorGoFrom)) <= abs(eleRight.getFloor() - ((floors+1)-floorGoFrom))) {
        closest = 1;
    } else {
        closest = 2;
    }


    std::cout << "Shorter: " <<  closest << std::endl;
    std::cout << "Go From:" << 6-floorGoFrom << std::endl;
    std::cout << "Current floor L:" << eleLeft.getFloor() << std::endl;
    std::cout << "Current floor R:" << eleRight.getFloor() << std::endl;
    std::cout << "Status L:" << eleLeft.status << std::endl;
    std::cout << "Status R:" << eleRight.status << std::endl;
    std::cout << "Go To:" << floorGoTo[floorGoFrom-1] << std::endl;

    from = (floors+1)-floorGoFrom;
    to = floorGoTo[floorGoFrom-1];

    if(from < to) {
        direction = statusUP;
    } else if(from > to) {
        direction = statusDOWN;
    }


//
//
//    if(closest == 1 && ((eleLeft.status == statusUP && eleLeft.getFloor() < from && direction == statusUP) ))   {
//        eleLeft.addRequest(from, to);
//
//    } else if(closest == 2 && ((eleRight.status == statusUP && eleRight.getFloor() < from && direction == statusUP) )) {
//        eleRight.addRequest(from, to);
//
//    } else if(closest == 1 && eleLeft.status == statusDOWN && eleLeft.getFloor() > from && direction == statusDOWN)   {
//        eleLeft.addRequest(from, to);
//
//    } else if(closest == 2 && eleRight.status == statusDOWN && eleRight.getFloor() > from && direction == statusDOWN)   {
//        eleRight.addRequest(from, to);

    if(closest == 1 && ((eleLeft.status == statusUP && eleLeft.getFloor() < from) ))   {
        eleLeft.addRequest(from, to);

    } else if(closest == 2 && ((eleRight.status == statusUP && eleRight.getFloor() < from) )) {
        eleRight.addRequest(from, to);

    } else if(closest == 1 && eleLeft.status == statusDOWN && eleLeft.getFloor() > from)   {
        eleLeft.addRequest(from, to);

    } else if(closest == 2 && eleRight.status == statusDOWN && eleRight.getFloor() > from)   {
        eleRight.addRequest(from, to);




    } else if(closest == 1 && eleLeft.status == statusIDLE)   {
        eleLeft.addRequest(from, to);

    } else if(closest == 2 && eleLeft.status == statusIDLE)   {
        eleRight.addRequest(from, to);

    } else if(closest == 1)   {
        eleLeft.addRequest(from, to);

    } else if(closest == 2)   {
        eleRight.addRequest(from, to);

    } else {
        std::cout << "ERROR: Can't select elevator" << std::endl;
    }
}