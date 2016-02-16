#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

double calcMean (vector<double> inputlist)
{
  double sum =0;
  int n = inputlist.size();
  for(int i=0; i<n; i++)
  {
    sum += inputlist[i];
  }

  return double(sum/n);
}

//calculate the standard deviation 
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

//Calculate the confidence interval
vector<double> conInterval(vector<double> inputlist)
{
  double std = calcStd(inputlist);

  double mean = calcMean(inputlist);

  double crt = 2.776;

  double c1 = mean - crt*(std/sqrt(inputlist.size()));
  double c2 = mean + crt*(std/sqrt(inputlist.size()));

  vector<double> myvector;
  myvector.push_back(c1);
  myvector.push_back(c2);

  return myvector;
}


//Generate an random number between 0 and 1
double randd()
{
  return (double)rand() / (RAND_MAX + 1.0);
}

//Check if random number is <= e (the error rate)
bool checkError(double e)
{
  if (randd() <= e)
  {
    return true;
  }
  return false;
}


int main (int argc, char *argv[])
{


  //Check the number of arguments
  if (argc !=2)
  {
    cout << "Invalid number of argument << endl" << endl;
    return 1;
  }

  ifstream file(argv[1]);
  string str; 
  while (getline(file, str))
  {
    cout << str << endl;
  }

  

  return 0;

}
