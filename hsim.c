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
#include <algorithm>

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

//Print format": Link State Routing:    average number of transmissions,   average path length 
void printOutPut(string x, double a, double b)
{
  cout << x << ":  " << a << ", " << b <<endl;
}

//Print format": Link State Routing:    average number of transmissions,   average path length 
void printOutPut(string x, double a)
{
  cout << x << ":  " << a <<endl;
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

//----------------------------------------------------------------------------------------------------------------

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

bool elementInList(vector <int> list, int item)
{
  return (find(list.begin(), list.end(), item) != list.end()); 
}


int findMinIndex(vector <int> list)
{
  int min_value = 999999999;
  int min_index = 0;
  
  for(unsigned int i =0; i< list.size() ; i++)
  {
    if (list[i] <= min_value)
    {
      min_value = list[i];
      min_index = i;
    }
    
  }
  return min_index;
}
//0,1 ,2 ... etc to size
vector<int> generateQueue(int size)
{
  vector<int> queue;

  for(int i=0; i<size;i++)
  {
    queue.push_back(i);
  }
  return queue;
}

vector< int  > shortPath (int source, vector< vector<int> > neighbours)
{
  //queue contains the nodes that haven't been look at yet
  vector<int> queue = generateQueue(neighbours.size());

  queue.erase(queue.begin() + source);



  vector< vector<int> > shortestPaths(neighbours.size());

  shortestPaths[source] = {source};

  /*
  for(unsigned int i =0; i< shortestPaths.size(); i++)
  {
    printoutArray("x", shortestPaths[i]);
  }
  */
  
  vector<int> distance(neighbours.size());

  for(unsigned int i =0; i<neighbours.size(); i++)
  {
    if (elementInList(neighbours[i], source))
    {
      distance[i]= 1;
      
    }
    else
    {
      distance[i] = 9999;
    }
  }

  distance[source] = 0;
  //printoutArray("", neighbours);

  /*
  for(unsigned int i =0; i< neighbours.size(); i++)
  {
    printoutArray("x", neighbours[i]);
  }
  */
  int nextNode = findMinIndex(distance);
  queue.erase(queue.begin() + nextNode);

  for(unsigned int i =0; i< neighbours[nextNode].size(); i++)
  {
    int neighbour = ((neighbours[nextNode])[i]);
    
    if( elementInList(queue, neighbour))
    {
      
      distance[neighbour] = min(distance[nextNode]+1, distance[neighbour]);
    }
    
  }
  printoutArray("", distance);


  //cout << min << endl;

  //printoutArray("", neighbours);
  //cout << "==========" << endl;

  /*
  for(unsigned int i =0; i< neighbours.size(); i++)
  {
    printoutArray("x", neighbours[i]);
  }
  */
  
  return distance;
}


//=================================================================================================================

int main (int argc, char *argv[])
{
  //--------------------------------------------------------------------
  
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


  //Get number of nodes
  vector<int> temp = neighbours[0];
  int number_of_nodes = temp[0];
  cout <<"NUmber of nodes: " <<number_of_nodes << endl;

  //Erase the number of nodes from neighbours
  neighbours.erase(neighbours.begin());

  //Test print neighbours
  /*
  for(unsigned int i =0; i< neighbours.size(); i++)
  {
    printoutArray("x", neighbours[i]);
  }
  */

  //--------------------------------------------------------------------

  //cout << degreeOfNetwork(neighbours) << endl;
  

  //--PRINT OUT STUFF----------------------------------------------------------------------------------

  /*
  //N        average degree of the network
  printOutPut("N", 3.4);
  //Link State Routing:    average number of transmissions,   average path length 
  printOutPut("Link State Routing", 2.3, 3.4);
  //Distance Vector Routing:  average number of transmissions, average path length
  printOutPut("Distance Vector Routing", 2.3, 3.4);
  //Hot Potato I:   average number of transmissions confidence interval,  average path length  confidence interval
  printOutPut("Hot Potato I", 2.3, 3.4);
  //Hot Potato II:   average number of transmissions confidence interval,  average path length  confidence interval
  printOutPut("Hot Potato II", 2.3, 3.4);
  //--PRINT OUT STUFF----------------------------------------------------------------------------------
  */

  shortPath (0, neighbours);
  //vector <int> x = {4,14,3};

  //cout << findMinIndex(x) << endl;
  return 0;

}

//=================================================================================================================
