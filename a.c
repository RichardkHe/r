#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <cmath>

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

double calcMean (vector<double> inputlist)
{
  double sum =0;
  int n = inputlist.size();
  for(int i=0; i<n; i++)
  {
    sum += inputlist[i];
  }
  cout << double(sum/n) << endl;
  return double(sum/n);
}


double calcStd(vector<double> inputlist)
{
  double mean = calcMean(inputlist);

  double sum =0;
  for(double i=0; i<inputlist.size(); i++)
  {
    sum += (inputlist[i] - mean)*(inputlist[i] - mean);
  }
  double std = sum/(inputlist.size()-1);
  
  std = sqrt(std);

  return std;
}

vector<double> conInterval(vector<double> inputlist)
{
  double std = calcStd(inputlist);
  cout << std << endl;

  double mean = calcMean(inputlist);

  double crt = 2.776;

  double c1 = mean - crt*(std/sqrt(inputlist.size()));
  double c2 = mean + crt*(std/sqrt(inputlist.size()));

  vector<double> myvector;
  myvector.push_back(c1);
  myvector.push_back(c2);


  cout << myvector.size()<< endl;
  cout << myvector[0] << endl;
  cout << myvector[1] << endl;
  
  return myvector;
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

  vector<double> myvector(5);
  myvector = {13,23,12,44,55};
  //for (int i=0; i<2; i++) myvector[i]=i;

  
  
  conInterval(myvector);
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
