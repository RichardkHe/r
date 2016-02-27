CMPUT 313  Assignment 2, Winter 2016 (Worth 9%)

Routing Algorithm Performance  
Due:  Tuesday March 1, 2016, 5:00 pm

by:
Minhal Syed
Richard He

This assignment we explore various routing algorithms: Link State, Distance Vector, Hot potato 1 and 2. We wrote this in c++, to check implementation look in code.

We used the following code from the respective links, and are also indicated where in the code:

//--------------------------------------------------------------------------------------------------------------------------------
//FROM: http://stackoverflow.com/questions/12200486/how-to-remove-duplicates-from-unsorted-stdvector-while-keeping-the-original-or

This stuff is used to remove duplicates from an unsorted vector basically. This is used in general in our program for removing 
duplicates for providing a base case for our recursive removing loops function. 

 
//FROM: http://stackoverflow.com/questions/10506595/how-do-i-check-if-two-stdvectors-contain-only-the-same-elements

Used to check if two vectors have the same elements. 


//FROM: http://cboard.cprogramming.com/cplusplus-programming/126689-converting-string-vector-integer-vector.html

Just used to convert vector of string to vector of ints. This used in general when we are converting the read in values as str's to int's
 

//--------------------------------------------------------------------------------------------------------------------------------

To run the simulation on commandline, first open to correct directory with files:

type:
make

TO RUN, graph1.txt is an adjacency list txt file:
./hsim graph1.txt

All adjacency list txt files are provided in main directory and picture of corresponding adjacency list are inside graph images.

The expected output of your program will be:

N        average degree of the network

Link State Routing:    average number of transmissions,   average path length

Distance Vector Routing:  average number of transmissions, average path length
Hot Potato I:   average number of transmissions confidence interval,  average path length  confidence interval
Hot Potato II:   average number of transmissions confidence interval,  average path length  confidence interval