#include "stdio.h"

// SET GLOLBALS
float total_ticks = 64;
// float tick_distance = wheel_circ / total_ticks;
float tick_distance = 208 / 64;
//distance between sheets in metres
float sheet_space = 208;

int n;
char first[50];
char last[50];
char mid[50];
char temp;
int stack[3]={0,0,0};

int convert(char a){

	if (a == 'A'){
		return 0;

	} else if (a == 'B'){
		return 1;

	} else if (a == 'C'){
		return 2;
	}
	return 3;
}

void checkMove(char first,char last){
	int t = convert(first);
	int z = convert(last);

	switch (t){
		case 0: stack[0]--; break;
		case 1: stack[1]--; break;
		case 2: stack[2]--; break;
	}

	switch (z){
		case 0:	stack[0]++;	break;
		case 1:	stack[1]++;	break;
		case 2:	stack[2]++;	break;
	}

	printf("A:%i, B:%i, C:%i\n",stack[0],stack[1],stack[2]);
}

void towers(int n,char first,char last,char mid){ 

	// If only 1 disk, make the move and return
	if(n == 1){
        checkMove(first,last);
	    return;
	}

	// Move top n-1 disks from A to B, using C as auxiliary
	towers(n-1, first, mid, last);

	// Move remaining disks from A to C
    checkMove(first,last);

	// Move n-1 disks from B to C using A as auxiliary
	towers(n-1,mid,last,first);
}

int main (void){

	printf("Number of disks?");
	scanf("%i",&n);

	printf("First Peg? (A,B or C)");
	scanf("%s",first);

	printf("Second Peg? (A,B or C)");
	scanf("%s",mid);

	printf("Last peg? (A,B or C)");
	scanf("%s",last);

    int fSwitch = convert(first[0]);
	
	switch(fSwitch){
		case 0:	stack[0] = n; break;
		case 1:	stack[1] = n; break;
		case 2:	stack[2] = n; break;
		default: break;
	}

	temp = first[0];
  	
  	towers(n, first[0], last[0], mid[0]);

	return 0;
}
