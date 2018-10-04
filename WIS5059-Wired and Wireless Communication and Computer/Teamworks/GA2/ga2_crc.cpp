#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Shift bits to the left
void shift_bit(int* arr, int ar, int length){
	for(int t=0; t<ar; t++){
		for(int k=0; k<length; k++){
			arr[k] = arr[k+1];	
		}
		arr[length-1] = 0;
	}
}

int main(){
	// Initializing D, G, and R
	int d[9] = {0,0,0,1,1,0,0,0,1};
	int g[4] = {1,0,0,1};
	int r[3];
	int rem[4] = {1,1,0,0};	// The remainder in the modulo-2 arithmetric division
	
	int ar = 0;	// The number of bits compensated
	int i = 4;	// The position of compensated bit in D
	
	shift_bit(d, 3, sizeof(d)/sizeof(*d));
	
	while(i<9){
		ar = 0;
		
		// Check how many bits we need to offset
		for(int j=0; j<4; j++){
			if(rem[j]==1){
				break;
			}
			else if(rem[j]==0){
				ar = ar + 1;
			}
		}
		
		// Offset bits
		if(ar!=0){
			shift_bit(rem, ar, sizeof(rem)/sizeof(*rem));
			
			for(int j=0; j<ar; j++){
				rem[4-ar+j] = d[j+i];
			}
			
			i = i + ar;
		}
		
		// XOR between remainder and G
		for (int j=0; j<4; j++){
			rem[j] = (rem[j]^g[j]);
		}
	}
	
	// Get the remainder R
	for(int t=0; t<3; t++){
		r[t] = rem[t+1];
	}
	
	// Print the results
	printf("The remainder: \n");
	for(int t=0; t<3; t++){
		printf("%d", r[t]);
	}
	printf("\nThe trasmitting frame: \n");
	for(int t=0; t<9; t++){
		if(t<6){
			printf("%d", d[t]);
		}
		else{
			printf("%d", r[t-6]);
		}
	}
	
	return 0;
}
