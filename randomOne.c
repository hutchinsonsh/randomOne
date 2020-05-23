#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 

// I decided to use linked list; I've never programmed them before so I figured it would be fun
// also I figured if I could use a circular double linked-list that I could insert elements
// in order in the first place/search both ways which would cut down on time
// don't know if thats actually how the math works out or if I just made this harder
// than it needed to be. 
// linked-list node
struct Node
{
	int data;
	struct Node* next;
	struct Node* prev;
};


void randOneMain(int seed, int digits, int goTill);		// main function for generator one
int randomOne(int seed, int digits);				// first generator
void turnIntoArray(int *numArray, int newNum, int digits);	// converts num into array
int addList(struct Node** node_ref, int newSeed);		// adds each seed to list
void printList(struct Node* node);				// prints out linked list
void printArray(int Array[], int num);


int main()
{
	int seed;
	int digits;
	int goTill = 200;
	
	digits = 1;
	
	seed = 1;
	randOneMain(seed, digits, goTill);
	seed = 3;
	randOneMain(seed, digits, goTill);
	
	digits = 2;
	
	seed = 10;
	randOneMain(seed, digits, goTill);
	seed = 17;
	randOneMain(seed, digits, goTill);
	seed = 49;
	randOneMain(seed, digits, goTill);

	digits = 3;
	
	seed = 742;
	randOneMain(seed, digits, goTill);
	seed = 938;
	randOneMain(seed, digits, goTill);

	digits = 4;

	seed = 1234;
	randOneMain(seed, digits, goTill);
	seed = 9600;
	randOneMain(seed, digits, goTill);
	seed = 9753;
	randOneMain(seed, digits, goTill);

	
	digits = 5;
	seed = 12345;
	randOneMain(seed, digits, goTill);
	
	digits = 6;
	seed = 123456;
	randOneMain(seed, digits, goTill);

	digits = 7;
	seed = 1234567;
	randOneMain(seed, digits, goTill);

	return 0;

}

// this is the main function for the first random # generator
// 	Description: takes a input seed, and length of seed(digits).
// it adds seed to both an array and a linked list, finds a new 'random number', and repeats the process
// until either the 'goTill' value is reached or until it finds a repeat number
//	Calls functions: addList, randomOne, printList, printArray
void randOneMain(int seed, int digits, int goTill)
{
	struct Node* randOneList = NULL;		// linked list sorted numerically
	int randOneArray[goTill];			// array sorted chronologically
	int randOneCount = 1;				// keeps track of total number of elements added
	int alreadyThere;				// goes through linked list-> checks if rand num already called; =-10 if true
	int i;						// for iterating through loops
	
	randOneArray[0] = seed;
	alreadyThere = addList(&randOneList, seed);

	for(i = 1; i < goTill; i++)					// gets new random number; checks if already in list; adds to list/array if not
	{
		if(alreadyThere != -10)					// checks if element already added
		{
			seed = randomOne(seed, digits);			// gets new seed
			if(seed == -100)				// overflow error occured
			{
				alreadyThere = -100;
				break;
			}
			else
				randOneCount += 1;
		}
		else
		{ 
			i = goTill;					// exits out of loop if seed is repeated
		}
		randOneArray[i] = seed;                         	// adds last seed to array
                alreadyThere = addList(&randOneList, seed);     	// adds last seed to linked list
	}
	
	if(alreadyThere == -100)					// prints out list/array
		printf("\nOverflow error occured\t");
	else if(alreadyThere == -10)
		printf("\nRepeated number: %d\n# of iterations: %d\n", seed, randOneCount);
	else
		printf("\nNo repeated numbers.\nLast num = %d\n# of iterations: %d\n", seed, randOneCount);

	printList(randOneList);
	printArray(randOneArray, randOneCount);
}

// this calculates the new number for the first random # generator
// 	Description: this function takes a number; squares it; and then takes the middle
// digits(equal to digits parameter), which it then returns the value of.
int randomOne(int seed, int digits)
{
	if(seed == 0)				// weird: when I try to run this code w/ 0-> gives weird values; this was my solution
		return 0;
	
	int numArray[digits*2];			// for editing new num; converts num into array
	int newNum = (seed * seed);		// gets new random #-> takes middle values of newNum ex) 12345678 == 3456
	int i = 0;
	if(newNum < 0)				// overflow error
		return -100;

	turnIntoArray(numArray, newNum, digits);

	int start = digits / 2;			// where subarray starts
	int end = start + digits;		// where subarray ends
	int count = digits;			// 1o^count = correct 10s place for char
	int finalNum = 0;
	int temp;
	for(i = start; i < end; i++)		// goes through char element/builds back into a int
	{
		count --;
		temp = numArray[i];			// converts char value to int value
		finalNum += temp * (pow(10, count));
	}
	return finalNum;
}

// takes a int, converts into a int array of (digits*2) size
void turnIntoArray(int *numArray, int newNum, int digits)
{
        int editNum = newNum;
        int startHere = digits*2-1;
        int temp = newNum / pow(10, (digits*2)-1);
        int i;


        while(temp > 10)                // newNum.length > digits -> cut off until it matches length ex) 12345678 -> 1234
        {
                editNum = editNum / 10;
                temp = editNum / pow(10, (digits*2)-1);
        }
        
        while(temp <= 0)                        // newNum.length < digits -> add 0's; ex) 12 -> 1200
        {
                editNum = editNum * 10;
                temp = editNum / pow(10, (digits*2)-1);
        }
        
        for(i = (digits*2-1); i >= 0; i--)              // I tried using sprintf but it kept giving me (-) values; this converts num into array
        {       
                numArray[i] = editNum % 10;
                editNum /= 10;
        }
}


int addList(struct Node** nodeRef, int newSeed)
{
	if(*nodeRef == NULL)		// checks to see if linked list is empty
	{
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->data = newSeed;
		newNode->next = newNode->prev = newNode;
		*nodeRef = newNode;
		return 0;
	}	
	
	struct Node *startTemp = *nodeRef;		// points to first element
	struct Node *endTemp = (*nodeRef)->prev;		// points to last element
	struct Node *addHere = (struct Node*)malloc(sizeof(struct Node)); 
	int endLoop = 0;

	// if replacing first element
	if(newSeed < startTemp->data)             // checks if header or not
        {
                addHere = (*nodeRef)->prev;
                struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                newNode-> data = newSeed;

                newNode->next = *nodeRef;
                newNode->prev = addHere;
                addHere->next = (*nodeRef)->prev = newNode;
                *nodeRef = newNode;
	
		return 0;
        }



	// if i'm doing this right, the loop will go from both directions
	// of the linked list and find where in the linked list the new data is
	// either bigger than the value that comes before it or smaller than the one after it
	while(endLoop == 0)
	{
		if(startTemp->data == newSeed)
		{
			return -10;			// already exits
		
		}
		if(endTemp->data == newSeed)
			return -10;			// already exits
		
		// for startTemp- 1st element onward
		if(startTemp->data < newSeed)		// move to next element
		{
			startTemp = startTemp->next;
			if(endTemp->data > newSeed)             // move back one element
                        	endTemp = endTemp->prev;
                	else    
                	{       
                        	endLoop = -1;			// exits out of loop
                        	addHere = endTemp;
                	}
		}
		else		
		{
			endLoop = -1;				// exits out of loop
			addHere = startTemp->prev;
		}
	}
		
	struct Node* next = addHere->next;
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); 
	newNode-> data = newSeed;

	addHere->next = newNode;		// adds in newNode between addHere and next
	newNode->prev = addHere;
	newNode->next = next;
	next->prev = newNode;
	
	return 0;	
}

void printList(struct Node* node)
{
	printf("linked list : \n");
	struct Node *temp = node;
	while(temp->next != node)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("%d ", temp->data);
}

void printArray(int Array[], int num)
{
	int i;
	printf("\nArray: \n");
	for(i = 0; i < num; i++)
	{
		printf("%d ", Array[i]); 
	}
	printf("\n\n");
}













