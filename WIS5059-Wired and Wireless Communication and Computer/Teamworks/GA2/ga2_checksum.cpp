#include <stdio.h>
#include <stdlib.h>

using namespace std;

void* calculate_sum(int a[], int b[]){
	// Initializing carry bit
	int c = 0;
	int temp_c = 0;
	int wrap[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	
	// Calculate the sum
	for(int i=15; i>=0; i--){
		temp_c = ((a[i] & b[i]) | (a[i] & c)) | (b[i] & c);
		a[i] = ((a[i]^b[i])^c);
		c = temp_c;
	}
	
	if(c==1){
		c = 0;
		for(int i=15; i>=0; i--){
			temp_c = ((a[i] & wrap[i]) | (a[i] & c)) | (wrap[i] & c);
			a[i] = ((a[i]^wrap[i])^c);
			c = temp_c;
		}
	}
}

int main(){
	// Initializing the four 16-bits words
	int w1[16] = {1,0,0,0,0,1,1,0,0,1,0,1,1,1,1,0};
	int w2[16] = {1,0,0,0,1,1,0,0,0,1,1,0,1,0,0,0};
	int w3[16] = {0,1,1,1,1,0,0,1,0,0,1,0,0,0,1,0};
	int w4[16] = {1,0,0,0,1,0,0,1,1,0,1,1,1,1,0,1};
	
	// Creating a variable to store checksum
	int checksum[16];
	for(int i=0; i<16; i++){
		checksum[i] = w1[i];
	}
	
	// Calculate the sum of all four 16-bits words
	calculate_sum(checksum, w2);
	calculate_sum(checksum, w3);
	calculate_sum(checksum, w4);
	
	// Calculate the 1s complements
	for(int i=0; i<16; i++){
		if(checksum[i]==0){
			checksum[i] = 1;
		}
		else if(checksum[i]==1){
			checksum[i] = 0;
		}
	}
	
	printf("Checksum: \n");
	for(int i=0; i<16; i++){
		printf("%d", checksum[i]);
	}
	
	return 0;
}
