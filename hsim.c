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
#include <sstream>
#include <iterator>
#include <numeric>

using namespace std;

//=================================================================================================================
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
//old functions
//=================================================================================================================

void printoutArray(string x, vector<int> vec)
{
  cout << "[";
  for (unsigned int y=0; y< vec.size(); y++)
  {
    {
      cout << vec[y] << " ";
    }
  }
  cout <<"]"<<endl;
}

int degreeOfNode(int i, vector< vector<int> > neighbours)
{
  return (neighbours[i]).size();
}

double degreeOfNetwork(vector< vector<int> > neighbours)
{
  double sum = 0;

  for (unsigned int i =0; i<neighbours.size(); i++)
  {
    sum += degreeOfNode(i, neighbours);
  }
  
  return sum/neighbours.size();
}


//http://cboard.cprogramming.com/cplusplus-programming/126689-converting-string-vector-integer-vector.html
vector<int> vecstr_to_vecint(vector<string> vs)
{
    vector<int> ret;
    for(vector<string>::iterator it=vs.begin();it!=vs.end();++it)
    {
        istringstream iss(*it);
        int temp;
        iss >> temp;
        ret.push_back(temp);
    }  
    return ret;
}

//=================================================================================================================

int main (int argc, char *argv[])
{
  
  //Check the number of arguments
  if (argc !=2)
  {
    cout << "Invalid number of argument << endl" << endl;
    return 1;
  }

  vector< vector<int> > neighbours;
  
  ifstream file(argv[1]);
  string str; 
  while (getline(file, str))
  {
    //http://www.cplusplus.com/forum/beginner/87238/
    istringstream buf(str);
    istream_iterator<string> beg(buf), end;
    vector<string> tokens(beg, end);

    //vecstr_to_vecint(tokens);
    
    neighbours.push_back(vecstr_to_vecint(tokens));
  }

  
  vector<int> temp = neighbours[0];

  int number_of_nodes = temp[0];

  cout << number_of_nodes << endl;

  
  neighbours.erase(neighbours.begin());

  /*
  for(unsigned int i =0; i< neighbours.size(); i++)
  {
    printoutArray("x", neighbours[i]);
  }
  */

  cout << degreeOfNetwork(neighbours) << endl;
  

  return 0;

}

//=================================================================================================================
