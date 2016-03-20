#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"

int distance;
float tick_distance = 208 / 64;
float robot_diameter = 105.8;
int irLeft, irRight=0;
int end = 0;
float degrees = 0;
float moved = 0;
int ticksLeft;
int ticksRight;
float leftDeg;
float rightDeg;

void fullTurn(float angle){
  int ticks = ((robot_diameter / 2) * 2 * 3.1416) * (angle / 360) / tick_distance;
  drive_goto(ticks, - ticks);
}

int checkClose(){
  
  irLeft = 0;
  irRight = 0;
  distance = ping_cm(8);

  for(int dacVal = 0; dacVal < 160; dacVal += 8){
    dac_ctr(26, 0, dacVal);
    freqout(11, 1, 38000);
    irLeft += input(10);

    dac_ctr(27, 1, dacVal);
    freqout(1, 1, 38000);
    irRight += input(2);
  }

  if (irLeft<7) {
    drive_speed(25,0);
  } else if (irLeft > 9 || irLeft == 0){
    drive_speed(0,25);
  } else {
    drive_speed(40,40);
  }
   
  if (distance<=5){
    fullTurn(90);
    degrees+=90;
    end=1;
  }

  drive_getTicks(&ticksLeft, &ticksRight);
  leftDeg = ((ticksLeft * 360) / 332.38128) * 3.25;
  rightDeg = ((ticksRight * 360) / 332.38128) * 3.25;
  degrees = degrees + (rightDeg - leftDeg);
  moved = ticksLeft * 3.25;
 }

int main(){
  low(26);
  low(27);

  while(1){
    checkClose();
    if (end == 1){
      break;
    }
  }

  print("Rotation:%f Distance:%f\n", degrees, moved);
  return 1;
}