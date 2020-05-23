#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// in short, this turns a number into an array w/ a size of digits.
// it is filled in left to right and any blank spots are filled w/ 0.
// there's a built in function for this I think but it wasn't working for my program
// so I just built one
void turnIntoArray(int *numArray, int newNum, int digits);

int main()
{
	int numArray[6];
	int newNum = 123456;
	turnIntoArray(numArray, newNum, 3);

	int i;
	printf("\n");
	for(i = 0; i < 6; i++)
                printf("%d ", numArray[i]);
}

void turnIntoArray(int *numArray, int newNum, int digits)
{
	int editNum = newNum;
	int startHere = digits*2-1;
	int temp = newNum / pow(10, (digits*2)-1);
	int i;
	
	
	while(temp > 10)		// newNum.length > digits -> cut off until it matches length ex) 12345678 -> 1234
	{
		editNum = editNum / 10;
		temp = editNum / pow(10, (digits*2)-1);
		printf("\tNum less: %d\ttemp = %d\tpower = %d\n", editNum, temp, digits-1); 
	}
	
	while(temp <= 0)			// newNum.length < digits -> add 0's; ex) 12 -> 1200
	{
		editNum = editNum * 10;
		temp = editNum / pow(10, (digits*2)-1);
                printf("\tNum greater: %d\ttemp = %d\tpower = %d\n", editNum, temp, digits-1);

	}
	
	for(i = (digits*2-1); i >= 0; i--)              // I tried using sprintf but it kept giving me (-) values; this converts num into array
        {       
                numArray[i] = editNum % 10;
                editNum /= 10;
        }

	for(i = 0; i < digits*2; i++)
		printf("%d\n", numArray[i]);
	
}
