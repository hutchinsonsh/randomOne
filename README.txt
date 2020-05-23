This is my attempt at a random number generator. This PRNG uses the middle square method.
I used a double circular linked list to sort each generated number in numerical order to cut down on search time(and because i've never used them before and thought it would be fun. it wasn't) and array to place each number in the order it was generated.
this code
    1. takes original number- the 'seed'
    2. generates a new number using the middle square method
    3. places the new number in the linked list and array in the order described above
    4. if that number has already been generated, meaning that the generator will go into a loop, the code stops
    5. if it hasn't been used, the number is passed on as the new seed
This process is repeated until either 1) a number is repeated or 2) it reaches the specified number of digits it needed to reach. In my test cases, I set it to 200 numbers since the run time for searching was n/2, which isn't great.

Problems: squaring a number takes up a lot of space so for a int variable, the number could only be up to 4 digits 
before overflow errors occured.
Also, sidenote, I decided to transfer the squared number into an array and then take the middle digits from the array.
This seems super simple but it was actually the hardest part to code. I created a side program to figure this out, which I 
included in this repository. It's in makeArray.c
