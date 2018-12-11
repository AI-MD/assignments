#include<stdio.h>


int main() {
	int arr[3][3] = { 0, };
	int val = 1;
	int arr_one[9] = { 0, };
	int k = 0;
	int *p;
	


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arr[i][j] = val;
			val++;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arr_one[k] = arr[i][j];
			k++;
		}
	}

	p = arr_one;

	for (int i = 0; i < 9; i++) {
		printf("%d", *(p+i));
	}
	printf("\n");

	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			printf("%d", *(p + i*3+j));
		}
		printf("\n");
	}

	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			printf("%d", *(p + i * 3 + j)+10);
		}
		printf("\n");
	}



	for (int i = 0; i < 9; i++) {
		printf("%d", arr_one[i]);
	}
	printf("\n");
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			printf("%d", arr[i][j]);
		}
		printf("\n"); 
	}

	return 0;
}