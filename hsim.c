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
//=====Print HELPER FUNCTIONS============================================================================================================

void printoutArray(string x, vector<int> vec)
{
  cout << x;
  for (unsigned int y=0; y< vec.size(); y++)
  {
    {
      cout <<vec[y] << " ";
    }
  }
  cout <<""<<endl;
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

//===Print HELPER FUNCTIONS===============================================================================================================



//---HELPER FUNCTIONS-------------------------------------------------------------------------------------------------------------

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

//Contains function
bool elementInList(vector <int> list, int item)
{
  return (find(list.begin(), list.end(), item) != list.end()); 
}

int findMinIndex(vector <int> distance, vector<int> queue)
{
  int min_value = 999999999;
  int min_index = -1;
  
  for(unsigned int i =0; i< queue.size() ; i++)
  {
    if (distance[(queue[i])] < min_value)
    {
      min_value = distance[(queue[i])];
      min_index = i;
    }
    
  }

  return min_index;
}

int findMax( vector<int> list)
{ 
  return *(max_element(list.begin(), list.end())); 
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

//---HELPER FUNCTIONS-------------------------------------------------------------------------------------------------------------







//============================================================================================================
//Dijstraka - calcuates the distance vector
vector< int > shortPathDistance (int source, vector< vector<int> > neighbours)
{
  //queue contains the nodes that haven't been look at yet
  vector<int> queue = generateQueue(neighbours.size());
  
  queue.erase(queue.begin() + source);

  vector< vector<int> > shortestPaths(neighbours.size());

  shortestPaths[source] = {source};
  
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
  
  while(queue.size() > 0)
  {
    int nextNodeQIndex = findMinIndex(distance, queue);
    int nextNodeIndex = (queue[nextNodeQIndex]);
    vector<int> neighbours_of_nextNode = (neighbours[nextNodeIndex]);
    
    queue.erase(queue.begin() + nextNodeQIndex);

    for(unsigned int i =0; i< neighbours_of_nextNode.size(); i++)
    {
      int neighbour = (neighbours_of_nextNode)[i];
      
      if( elementInList(queue, neighbour))
      {
        
        distance[neighbour] = min(distance[nextNodeIndex]+1, distance[neighbour]);
      }
    }
  }
  //printoutArray("", distance);
  return distance;
}
//============================================================================================================

int CalcDiam( vector< vector<int> > neighbours )
{
  int max_path = 0;
  
  for(unsigned int i=0; i<neighbours.size(); i++)
  {
    int node = i;
    
    int localmax = findMax(shortPathDistance(node, neighbours));

    if(localmax > max_path)
    {
      max_path = localmax;
    }
  }

  return max_path;
  
}

//TO DO
int findPathLength(int a, int b, vector< vector<int> > neighbours)
{
  vector<int> neighbour_distances = shortPathDistance (a, neighbours);

  return neighbour_distances[b];
}

double findAvgPathLength(vector< vector<int> > neighbours)
{
  int sum = 0;

  for(unsigned int i=0; i< neighbours.size(); i++)
  {
    for (unsigned int x =0; x< neighbours.size(); x++)

    {
      sum += findPathLength(x, i, neighbours);

    }
  }
  return (double)sum/(neighbours.size()*neighbours.size());
}


double DV_avgtrans(vector< vector<int> > neighbours)
{
  double numb_of_trans = 0;

  double diameter_of_network = CalcDiam(neighbours);

  for(unsigned int i=0; i< neighbours.size(); i++)
  {
    numb_of_trans += degreeOfNode(i, neighbours)*diameter_of_network;
  }

  return numb_of_trans/neighbours.size();
}

double linkStateFlooding(int source, vector< vector<int> > neighbours)
{
  int trans = 0;
  
  vector <int> nodesSend(neighbours.size());
  
  vector<int> queue; //this will contains nodes in a sequence
  vector<int> queueParent; //this will contains parent node parallel list
  
  //send to out going links, does not send if its a deadend, else it must send once, and receive once, and source only once

  queueParent.push_back(-1);
  queue.push_back(source);
  
  while(!queue.empty())
  {

    /*
    //remove source
    vector<int>::iterator position = std::find(queue.begin(), queue.end(), source);
    if (position != queue.end()) // == myVector.end() means the element was not found
    {
      queue.erase(position);
    }
    */
    
    //Pop the front
    int current_node = queue[0];
    
    queue.erase(queue.begin());

    int parent = queueParent[0];
    
    queueParent.erase(queueParent.begin());
    
    //If it has not send yet
    if(nodesSend[current_node] != 1)
    {
      //current node's neighbours
      vector<int> node_neighbours = neighbours[current_node];

      //Now the current node has been marked that it has sent
      nodesSend[current_node] = 1;

      //Sending to its neighbours
      for(unsigned int i=0; i< node_neighbours.size(); i++)
      {
        if(parent != node_neighbours[i])
        {
          queueParent.push_back(current_node);
          queue.push_back(node_neighbours[i]);
          trans++;
        }
      }
    }

    

  }

  printOutPut("trans", trans );
  
  return 0;
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

  cout << ""<< endl;
  //N        average degree of the network  
  cout <<"#ofNodes: "  <<number_of_nodes<< "  DEGREE: " << degreeOfNetwork(neighbours) << endl;
  
  //Link State Routing:    average number of transmissions,   average path length 
  printOutPut("Link State Routing", 123456, findAvgPathLength(neighbours) );
  
  //Distance Vector Routing:  average number of transmissions, average path length
  printOutPut("Distance Vector Routing", DV_avgtrans( neighbours ), findAvgPathLength(neighbours) );

  /*
  //Hot Potato I:   average number of transmissions confidence interval,  average path length  confidence interval
  printOutPut("Hot Potato I", 2.3, 3.4);
  //Hot Potato II:   average number of transmissions confidence interval,  average path length  confidence interval
  printOutPut("Hot Potato II", 2.3, 3.4);
  //--PRINT OUT STUFF----------------------------------------------------------------------------------
  */

  cout <<""<< endl;
  


  //vector <int> y = {0,5,2};

  
  
  cout << "Currently testing: "<< linkStateFlooding(1, neighbours) << endl;


  
  
  return 0;

}

//=================================================================================================================
