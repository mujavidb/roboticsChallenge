#include <stdio.h>

//2.1
void bubbleSort(int array[], int length) {
	int temp;
	
	for (int i = 1; i < length; i++) {
		for (int j = 0; j < length - 1; j++) {
			if (array[j] > array[j + 1]) {
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

// //2.2
void bubbleSortPasses(int array[], int length) {
	int i, j, k, temp;
	
	for (i = 1; i < length; i++) {
	   for (j = 0; j < length - 1; j++) {
	      if (array[j] > array[j + 1]) {
	         temp = array[j];
	         array[j] = array[j + 1];
	         array[j + 1] = temp;
	      }
	   }
	
	   printf("%d: ", i);
	   for (k = 0; k < length; k++) {
	      printf("%5d", array[k]);
	   }
	   printf("\n");
	}
}

int main(void){

	int length;

	printf("Enter number of elements: ");
	scanf("%d", &length);

	int array[length];

	for (int i = 0; i < length; i++){
		printf("Enter element %d: ", i + 1);
		scanf("%d", &array[i]);
	}

	//Print unsorted array
	printf("U: ");
	for (int i = 0; i < length; i++) {
	   printf("%5d", array[i]);
	}
	printf("\n");

	bubbleSortPasses(array, length);

	//Print sorted array
	printf("S: ");
	for (int i = 0; i < length; i++){
		printf("%5d", array[i]);
	}
	printf("\n");


}