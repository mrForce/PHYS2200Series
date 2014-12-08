
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <gsl/gsl_const_mksa.h>

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

float calc_sum(unsigned long long n){
	/*
	float two_quart = 1./(2.0*2*2*2);

	float series[n];

	unsigned long long i;
	for(i = 0; i < n; i++){
		series[i] = -1.;
	}
	
	//we always know that the first term will be 1.
	series[0] = scalar*1.;
	

	//go through odd values of k. Even valued indices, since arrays indexed at zero.
	float odd_sum = series[0];
	for(i = 0; i < n; i += 2){
		if(series[i] < -.1){

			series[i] = scalar*1./((i+1.)*(i+1.)*(i+1.)*(i+1.));
			odd_sum += series[i];
		}
	} 
	//for(i = 0; i <n; i+=2){
	//	printf("i = %llu, %.10f \n", i, series[i]);
	//}
	//now fill in for when k is even
	float even_sum = 0.;
	for(i = 1; i < n; i += 2){
		if(series[i] < -0.1){
			//printf("i = %llu, i_2 = %.10f \n", i, series[(i + 1)/2 - 1]);
			series[i] = two_quart*series[(i+1)/2 - 1];
			even_sum += series[i];
		}
	}
	float sum = odd_sum + even_sum;

	return sum/scalar;
	*/

	

	unsigned long long series[n];

	unsigned long long i;
	for(i = 0; i < n; i++){
		series[i] = 0;
	}
	
	//we always know that the first term will be 1.
	series[0] = 1;
	

	//go through odd values of k. Even valued indices, since arrays indexed at zero.

	for(i = 0; i < n; i += 2){

		if(series[i] == 0){
			series[i] = (i+1)*(i+1)*(i+1)*(i+1);
			if(series[i] == 0){
				printf("BAD!, %llu", i);
				exit(-1);
			}
		}
	} 
	//for(i = 0; i <n; i+=2){
	//	printf("i = %llu, %.10f \n", i, series[i]);
	//}
	//now fill in for when k is even

	for(i = 1; i < n; i += 2){
		if(series[i] == 0){
			//printf("i = %llu, i_2 = %.10f \n", i, series[(i + 1)/2 - 1]);
			series[i] = 16*series[(i+1)/2 - 1];
			if(series[i] == 0){
				printf("very bad, %llu %llu %llu \n", i, series[(i+1)/2 - 1], series[i]);
				exit(-1);
			}
		}
	}
	
	unsigned long long num_temp = 0;
	unsigned long long denom_temp = 1;
	unsigned long long common;
	for(i = 0; i < n; i++){

		/*
		If creating the numerator or denominator will cause integer overflow, then approximate each, by dividing both the numerator and denominator by 2. This causes some slight roundoff issues, but it shouldn't be a massive issue.
		my issue here: How do we deal with the addition? Orders of magnitude usually add when we multiply, but what about when we add? Well, multiply the a and b. (num_temp and series[i], respectively) to get c. Now, divide denom_temp by c, to get d. Add the order of magnitude (base 2) of d and c, and make sure this is less than 62. 

		I chose 62, because unsigned long long integers can hold up to 2^64 - 1. 62 was simply a reasonable sounding number for this application; I didn't perform any formal anlysis to arrive at 62.

		*/
		while(num_temp > 0 && denom_temp > 0 && ((order(num_temp) + order(series[i]) > 62 && order(denom_temp) + order(series[i]) > 62) || (order(denom_temp/(num_temp*series[i])) > 62))){
			num_temp /= 2;
			denom_temp /= 2;
		}
		//use formula a/b + c/d = (ad + bc)/(bd), then simplify using gcd.
		num_temp = num_temp*series[i] + denom_temp;
		denom_temp *= series[i];
		//We'll use the 
		common = gcd(num_temp, denom_temp);

		num_temp /= common;
		denom_temp /= common;

	}


	return ((float)num_temp)/denom_temp;
	
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
	unsigned long long n = 10;

	do{
		summed_value = calc_sum(n);
		error = fabs((true_value - summed_value)/(true_value));
		printf("summed value = %.20f, n = %llu, error = %.20f\n", summed_value, n, error);
		n *= 2;
	}while(error > 3*macheps);

	return 0;
}