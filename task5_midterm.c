#include <stdio.h>
#include <stdlib.h>
#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"

//Set up global vars
float tick_distance = 208 / 64;
float robot_diameter = 105.8;
int irLeft, irRight = 0;
int forwardFinished = 0;
int backwardsFinished = 0;
float uvFront;
int counter = 0;
int right[300];
int left[300];
int diff = 0;


//Reads values from sensors and updates right, left, counter, irLeft and irRight
void updateSensors(){
    irLeft = 0;
    irRight = 0;
    uvFront = ping_cm(8);

    for(int dacVal = 0; dacVal < 160; dacVal += 8){
        dac_ctr(26, 0, dacVal);
        freqout(11, 1, 38000);
        irLeft += input(10);
        dac_ctr(27, 1, dacVal);
        freqout(1, 1, 38000);
        irRight += input(2);
    }

    right[counter] = irRight;
    left[counter] = irLeft;
    counter++;
}

//Reads stored values and updates counter, irLeft and irRight
void retrieveValues() {

    irLeft = right[counter];
    irRight = left[counter];
    counter--;

    if (counter == -1) {
        backwardsFinished = 1;
    }
}

void checkClose(){

    //Strategy
    if (forwardFinished == 0) {
        updateSensors();
    } else {
        retrieveValues();

        //Accounts for time taken for sensor to read values in updateSensors
        pause(70); 
    }

    diff = irLeft - irRight;
    
    if (uvFront <=12 && forwardFinished == 0){
        
        //Magic numbers to account for bad robots
        drive_speed(5,5);
        //180 degree turn
        drive_goto(52, -52);

        //Adjustment for specific robot
        drive_goto(-2, 2);

        //return to correct speed
        drive_speed(30 - 2 * diff, 30 + 2 * diff);

        forwardFinished = 1;
    }
    
    drive_speed(30 - 2 * diff, 30 + 2 * diff);

}

int main(void){

    //Switch Infrared sensors ON
    low(26);
    low(27);

    while(backwardsFinished == 0){
        checkClose();
    }

    drive_speed(0,0);

	return 0;
}