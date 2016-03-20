#include "simpletools.h"
#include "abdrive.h"

// SET GLOBALS
float pi = 3.141593;
float total_ticks = 64;
float wheel_circ = 208;
// tick_distance = wheel_circumference / total_ticks;
float tick_distance = 208 / 64;
float robot_diameter = 105.8;
// quarter_arc_distance = robot_diameter * (pi / 2);
float quarter_arc_distance = 105.8 * (3.141593 / 2);

// LIBRARY FUNCTIONS
void arcRight(){
	int ticks = quarter_arc_distance / tick_distance;
	drive_goto(ticks, 0);
}

void arcLeft(){
	int ticks = quarter_arc_distance / tick_distance;
	drive_goto(0, ticks);
}

void fullTurn(float angle){
	int ticks = ((robot_diameter / 2) * 2 * pi) * (angle / 360) / tick_distance;
	drive_goto(ticks, - ticks);
}

void fullRight(){
	fullTurn(90);
}

void fullLeft(){
	fullTurn(-90);
}

void moveBot(float distance){
	int ticks = distance / tick_distance;
	drive_goto( ticks, ticks);
}

float mtm(float m) {
	return m * 1000;
}

// MAIN FUNCTION
int main(){
	
	//MOVE FORWARD
	moveBot(mtm(1.0));

	//SQUARE
	for(int i = 0; i < 4; i++) {
		moveBot(mtm(1.0));
		fullRight();	
	}

	//FULLTURN
	fullTurn(360.0);
}