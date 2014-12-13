PHYS2200Series
==============



This was by far the hardest of all the questions, but also the most rewarding, as it tested my creativity in minimizing numerical round-off errors.

First, I naively implemented the series using floats. However, as n increased, the accuracy of the calculation stopped improving. I hypothesized that the float datatype was causing too many roundoff errors. To test this hypothesis, I replaced all of the floats with doubles; however, I still kept the machine epsilon at the same value as before.

As it turns out, adding very small floating point numbers to much larger floating point numbers doesn't always change the larger number, since machine epsilon is much smaller near 0 than it is near 1. One way to fix the issues discussed above is to sum in reverse.

The following is what I had initially tried... although it's inferior to the method that was discussed in review, I thought it might be interesting to leave it here. The Makefile will produce an executable named "sum" and "sum_reverse". The "sum" executable uses the method discussed below; the "sum_reverse" uses the method discussed above.


The solution worked within the requested accuracy (3 times machine epsilon for floats), with n = 160. This supported my hypothesis that the float datatype simply wasn't precise enough to support the accuracy I needed.

I switched everything back to floats, since the assignment requested that all floating point numbers be floats. Then, I had a good idea: Treat every element in the series as a simple fraction (1/k^4), and add them using the following formula:

> a/b + c/d = (ad + bc)/(bd)

This approach seemed to work at first; however, as n increased, the numerator and denominator of the fraction that held the sum of the series grew. To minimize the size of the the numerator and denominator in numerator/denominator, I divided each part of the fraction by gcd(numerator, denominator). Even combining this approach with 64 bit integers (unsigned long long), the numerator and denominator still caused integer overflow sometimes.

	while(num_temp > 0 && denom_temp > 0 && ((order(num_temp) + order(series[i]) > 62 && order(denom_temp) + order(series[i]) > 62) || (order(denom_temp/(num_temp*series[i])) > 62))){

		num_temp /= 2;
		denom_temp /= 2;
	} 

Basically, when it was predicted that multiplying the denominator, or multiplying the numerator and adding to it, would cause either part of the fraction to create an integer overflow, both parts of the fraction would be divided by 2. This approach introduced small rounding errors; however, it should introduce significantly fewer errors than using floats. It calculated the value with n = 160.