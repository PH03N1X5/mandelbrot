#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<complex.h>

#define STEP 0.05
#define X0 1.5
#define X1 1.1
#define Y 1.0

int main()
{
	for(float j = -Y; j <= Y; j += STEP, puts(""))
		for(float i = -X0; i <= X1 ; i += STEP )
		{
			complex float c = i + I * j ;
			complex float z = 0;
			int iter;
			for(iter = 0; iter < 128 && creal(z) + cimag(z) < 4 ; ++iter)
				z = z*z + c;
			if( crealf(z) < 2 && cimagf(z) < 2 )
				printf("%c ", '#' );
			else 
				printf("%c ", ' ');

		}

	return 0;
}

