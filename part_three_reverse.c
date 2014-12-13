
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


unsigned long long gcd(unsigned long long x, unsigned long long y){
	if(x == 0){
		return y;
	}else{
		return gcd(y % x, x);
	}
}
int order(unsigned long long x){
	return log2l(x);
}

float calc_sum(int n){
	float two_quart = 1./(2.0*2*2*2);

	float series[n];

	int i;
	for(i = 0; i < n; i++){
		series[i] = -1.;
	}
	
	//we always know that the first term will be 1.
	series[0] = 1.;
	

	//go through odd values of k. Even valued indices, since arrays indexed at zero.

	for(i = 0; i < n; i += 2){
		if(series[i] < -.1){

			series[i] = 1./((i+1.)*(i+1.)*(i+1.)*(i+1.));
		}
	} 
	for(i = 1; i < n; i += 2){
		if(series[i] < -0.1){
			//printf("i = %llu, i_2 = %.10f \n", i, series[(i + 1)/2 - 1]);
			series[i] = two_quart*series[(i+1)/2 - 1];

		}
	}
	float sum = 0.;
	for(i = n - 1; i >= 0; i--){
		sum += series[i];
	}

	return sum;
	

	
	
}

int main(void){
	float macheps = 1.;
	while ((float) (1. + macheps) != 1.){
		macheps /= 2.;
	}
	printf("macheps = %g\n", macheps);

	float true_value = 1.0823232337111381915160036965411679027747509519187269;
	printf("true: %.12f\n", true_value);
	float error;
	float summed_value;
	int n = 10;

	do{
		summed_value = calc_sum(n);
		error = fabs((true_value - summed_value)/(true_value));
		printf("summed value = %.20f, n = %d, error = %.20f\n", summed_value, n, error);
		n *= 2;
	}while(error > 3*macheps);

	return 0;
}