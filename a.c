#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std; 

//http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
/*
int isPowerOfTwo (unsigned int x)
{
  return ((x != 0) && ((x & (~x + 1)) == x));
}
*/

int isPowerOfTwo (unsigned int x)
{
 while (((x % 2) == 0) && x > 1) /* While x is even and > 1 */
   x /= 2;
 return (x == 1);
}

int calcrbits(int n)
{
  int x =n;
  int i= 0;
  while(n>0)
  {
//cout <<"i = " <<i << endl;
    //  cout <<"n = " << n<< endl;
    i++;
    if(isPowerOfTwo(i))
    {
      continue;
    }
    n--;
  }
  return i-x;
   
}






double randd()
{
  return (double)rand() / (RAND_MAX + 1.0);
}

bool checkError(double e)
{
  if (randd() <= e)
  {
    return true;
  }
  return false;
}

double checkBurstError(int N, int B, double e)
{
  return checkError((N+B)/B*e);
}




//-----------------------------
//Global Commandline arguments
char M[2];
int A;
int K;
int F;
double e;
int B;
int N;
int R;
//-----------------------------

int main (int argc, char *argv[])
{
  /*
  Check the number of arguments 
  if (argc != 14)
  {
    printf("invalid arguments\n");
    return 1;
  }
  */
  
  strcpy(M, argv[1]);
  A = atoi(argv[2]);
  /*
  K = atoi(argv[3]);
  F = atoi(argv[4]);
  e = atof(argv[5]);
  B = atoi(argv[6]);
  N = atoi(argv[7]);
  R = atoi(argv[8]);
  */
  
  //print out all command line arguments in the same line
  // M A K F e B N R T seed1 seed2 seed3 seed4 seed5
  for(int i = 1; i < argc; i++)
  {
    //cout << argv[i] << " ";
  }
  cout <<"" << endl;
  
  cout << calcrbits(1)<< endl;
  cout << calcrbits(2)<< endl;
  cout << calcrbits(3)<< endl;
  cout << calcrbits(4)<< endl;
  cout << calcrbits(5)<< endl;
  cout << calcrbits(6)<< endl;
  cout << calcrbits(10)<< endl;
  cout << calcrbits(11)<< endl;
  cout << calcrbits(12)<< endl;
  /*
  if (strcmp( argv[1], "I" ) == 0)
  {
    cout << "I mode" << endl;
  }
  else 
  {
    cout << "B mode" << endl;
  }
  */

  return 0;
  
}
