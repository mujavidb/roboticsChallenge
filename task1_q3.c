#include "abdrive.h"
#include "simpletools.h"

// SET GLOBAL VARS
float total_ticks = 64;
// tick distance = wheel circumference / total_ticks
float tick_distance = 208 / 64;

void moveBot(float distance){
	int ticks = distance / tick_distance;
	drive_goto(ticks, ticks);
}

int main(void){	
	int length = 5;

	int array[] = {4,3,2,1,5};
	 
	int i, j, temp;

	//distance between sheets in ticks
	float sheet_space = 208;

	//BubbleSort
	for (i = 1; i < length; i++) {
		for (j = 0; j < length - 1; j++) {
			if (j == length - 2) {
				moveBot(sheet_space);
				moveBot(- sheet_space * (length - 1));
			} else if (array[j] > array[j + 1]) {
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				moveBot(sheet_space / 2);
				high(26);
				pause(1000);
				low(26);
				moveBot(sheet_space / 2);
			} else {
				moveBot(sheet_space);
			}
		}
	}
}