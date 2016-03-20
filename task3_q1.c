#include "stdio.h"
#include "abdrive.h"

// SET GLOBALS
float total_ticks = 64;
// tick distance = wheel circumference / total_ticks
float tick_distance = 208 / 64;
//distance between sheets in ticks
float sheet_space = 208;

char first='B';
char last='A';
char mid='C';
char temp='B';


void moveBot(float distance){
	int ticks = distance / tick_distance;
	drive_goto(ticks,ticks);
}

void towers(int,char,char,char);
void checkMove(char first,char last);

void moveStart(char first,char last){
	if ((first=='A' && last=='B')||(first=='B' && last=='C')){
    moveBot(sheet_space);
    high(26);
    pause(2000);
    low(26);
  } else if ((first=='B' && last=='A')||(first=='C' && last=='B')){
    moveBot(-sheet_space);
    high(26);
    pause(2000);
    low(26);
  } else if (first=='A' && last=='C'){
    moveBot(sheet_space * 2);
    high(26);
    pause(2000);
    low(26);
  } else if (first=='C' && last=='A'){
    moveBot(-sheet_space * 2);
    high(26);
    pause(2000);
    low(26);
  }
}

void checkMove(char first,char last){
	moveStart(temp,first);
  if ((first=='A' && last=='B')||(first=='B' && last=='C')){
    moveBot(sheet_space);
    high(26);
    pause(2000);
    low(26);
  } else if ((first=='B'&& last=='A')||(first=='C' && last=='B')){
    moveBot(-sheet_space);
    high(26);
    pause(2000);
    low(26);
  } else if (first=='A' && last=='C'){
    moveBot(sheet_space * 2);
    high(26);
    pause(2000);
    low(26);
  } else if (first=='C'&& last=='A'){
    moveBot(-sheet_space * 2);
    high(26);
    pause(2000);
    low(26);      
  }
	temp = last;
}

void towers(int n, char first, char last, char mid){
  
  // If only 1 disk, make the move and return
  if(n==1){ printf("\nDisk 1 from peg %c to %c",first,last);
    checkMove(first,last);
    return;
  }
  
  // Move top n-1 disks from A to B, using C as auxiliary
  towers(n-1,first,mid,last);

  // Move remaining disks from A to C 
  printf("\nMove disk %d from peg %c to peg %c",n,first,last);
  checkMove(first,last);

  // Move n-1 disks from B to C using A as auxiliary
  towers(n-1,mid,last,first);
}

int main (void){
  //number of disks
  int n = 4;
  towers(n,first,last,mid);
  drive_goto(52,0);
  return 0;
}
