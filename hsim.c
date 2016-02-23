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

//http://stackoverflow.com/questions/12200486/how-to-remove-duplicates-from-unsorted-stdvector-while-keeping-the-original-or

struct target_less
{
    template<class It>
    bool operator()(It const &a, It const &b) const { return *a < *b; }
};
struct target_equal
{
    template<class It>
    bool operator()(It const &a, It const &b) const { return *a == *b; }
};
template<class It> It uniquify(It begin, It const end)
{
    std::vector<It> v;
    v.reserve(static_cast<size_t>(std::distance(begin, end)));
    for (It i = begin; i != end; ++i)
    { v.push_back(i); }
    std::sort(v.begin(), v.end(), target_less());
    v.erase(std::unique(v.begin(), v.end(), target_equal()), v.end());
    std::sort(v.begin(), v.end());
    size_t j = 0;
    for (It i = begin; i != end && j != v.size(); ++i)
    {
        if (i == v[j])
        {
            using std::iter_swap; iter_swap(i, begin);
            ++j;
            ++begin;
        }
    }
    return begin;
}


//http://stackoverflow.com/questions/10506595/how-do-i-check-if-two-stdvectors-contain-only-the-same-elements

bool compare(vector<int> v1, vector<int> v2)
{
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    return v1 == v2;
}


//===STAT FUNCTIONS==============================================================================================================
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

  return (double)std;
}

//Calculate the confidence interval
vector<double> conInterval(vector<double> inputlist)
{
  double std = calcStd(inputlist);

  double mean = calcMean(inputlist);

  double crt = 2.262;

  double c1 = mean - crt*(std/sqrt(inputlist.size()));
  double c2 = mean + crt*(std/sqrt(inputlist.size()));

  vector<double> myvector;
  myvector.push_back(c1);
  myvector.push_back(c2);

  return myvector;
}
//===STAT FUNCTIONS==============================================================================================================


//=====Print HELPER FUNCTIONS============================================================================================================

//Print out whats in an vector
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

void printoutArray(string x, vector<double> vec)
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


//Print format for Hot potato format
void printOutPut(string x, double a, double a1, double a2, double b, double b1, double b2)
{
  cout << x << ":  " << a <<" (" << a1 <<", " << a2 <<"), " << b <<" (" << b1 <<", " << b2 <<")" <<endl;
}

//Print format": Link State Routing:    average number of transmissions,   average path length 
void printOutPut(string x, double a, double b)
{
  cout << x << ":  " << a << ", " << b <<endl;
}

//Help print tester
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

//Return random element from list
int randElement(vector<int> list)
{
  int x = rand();
  int rand_index = x % list.size();
  return list[rand_index];
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

//Remove an element and return the vector
vector<int> removeElement(vector<int> myVector, int item)
{

  vector<int>::iterator position = find(myVector.begin(), myVector.end(), item);
  if (position != myVector.end()) // == myVector.end() means the element was not found
    myVector.erase(position);

  return myVector;
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

//TO DO ?????
int findPathLength(int a, int b, vector< vector<int> > neighbours)
{
  vector<int> neighbour_distances = shortPathDistance (a, neighbours);

  return neighbour_distances[b];
}

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

//============================================================================================================


//--------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------


//=============================================================================================================================
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
  //printOutPut("trans", trans );
  return trans;
}

double linkStateAvgTrans(vector< vector<int> > neighbours)
{
  double sum = 0;

  for (unsigned int i=0; i< neighbours.size();i++)
  {
    sum += linkStateFlooding(i,neighbours);
  }

  return (double)sum/neighbours.size();
}

//=============================================================================================================================




//---potato-------------------------------------------------------------------------------------------------------------------
//hotpotato1 = false
//hotpotato2 = true
vector <int> findHotPotatoPath(int source, int dest, vector< vector<int> > neighbours, int type)
{
  vector <int> path;

  //added first to current list
  path.push_back(source);

  int currentNode = path[path.size()-1];
  
  while((currentNode = path[path.size()-1]) != dest)
  {
     
    vector<int> current_node_neighbours = neighbours[currentNode];

    
    if((path.size() >= 2) && (current_node_neighbours.size() >1))
    {
      int previousNode = path[(path.size()-2)];
      current_node_neighbours = removeElement(current_node_neighbours, previousNode);
    }

    int rand_neighbour;
    
    //hotpotato1 = 1
    //hotpotato2 = 2
    if((type == 2) && (elementInList(current_node_neighbours, dest)))
    {      
      rand_neighbour = dest;
    }
    else
    {
      rand_neighbour = randElement(current_node_neighbours);
    }
    
    path.push_back(rand_neighbour);

  }

  //printoutArray("Potato", path);

  return path;
}


//Take in vector and remove any loops
///x.erase(uniquify(x.begin(), x.end()), x.end())
vector <int> removeLoopFromPotato (vector <int> list) 
{

  vector<int> uniqueArray = list;

  uniqueArray.erase(uniquify(uniqueArray.begin(), uniqueArray.end()), uniqueArray.end());

  //printoutArray("x ",uniqueArray);

  
  //printoutArray("list: ", list);
  
  if (compare(uniqueArray, list))
  {
    return list;
  }

  
  vector <int> c = list;

  int front_index = 0;
  int back_index = 0;

  int break1 = 0;
  
  for(int i =0; i<(int)list.size(); i++)
  {
    
    for (int x = (int)list.size()-1; x > i+1; x--)
    {
      //printOutPut("x : ", x);
      if (list[i] == list[x])
      {

        /*
        cout << "hi" << endl;
        printOutPut("i : ", i);
        cout << "list[i] " << list[i] << endl;
        printOutPut("x : ", x);
        cout << "list[x] " << list[x] << endl;
        */
        front_index = i;
        back_index = x;// - 1;

        break1 =1;
        break;
      }
    }
    
    
    if (break1 ==1)
    {
      break;
    }
    
  }
  //printOutPut("front : ", front_index);
  //printOutPut("back : ", back_index);
  c.erase(c.begin() +front_index, c.begin()+back_index); 
  
  
  return removeLoopFromPotato (c); //was c
}

double hotPotato(int source, int dest, vector< vector<int> > neighbours, vector<int> *path, vector<int> *pathLoopRemoved, int type)
{
  
  *path = findHotPotatoPath(source, dest, neighbours, type);
  *pathLoopRemoved = removeLoopFromPotato(*path);
  
  return (*path).size() + (*pathLoopRemoved).size() - 2;  
}

void hotPotatoTrial(vector< vector<int> > neighbours, double *avgTrans, double *avgPathLength, int type)
{
  double sum_trans =0;
  double sum_path_length =0;
  for(unsigned int i =0; i< neighbours.size(); i++)
  {
    for(unsigned int j =0; j<neighbours.size(); j++)
    {
      vector<int> path;
      vector<int> pathLoopRemoved;
      sum_trans += hotPotato(i, j, neighbours, &path, &pathLoopRemoved, type);
      sum_path_length += pathLoopRemoved.size() - 1;
      //printoutArray("path :", path);
    }
  }

  *avgTrans = sum_trans/(neighbours.size());//*neighbours.size());

  *avgPathLength = sum_path_length/(neighbours.size()*neighbours.size());
  
}

//averaged over 10 trials
void generateHotPotatoTrials(vector< vector<int> > neighbours, vector<double> *avgTransTrial, vector<double> *avgPathLengthTrials, int type)
{
  double avgTrans = 0;
  double avgPathLength = 0;

  for(int i =0; i<10; i++)
  {
    hotPotatoTrial(neighbours, &avgTrans, &avgPathLength, type);
    (*avgTransTrial).push_back(avgTrans);
    (*avgPathLengthTrials).push_back(avgPathLength);
  }

}

//====M A I N=============================================================================================================

int main (int argc, char *argv[])
{
  srand(time(NULL));
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


  //--PRINT OUT STUFF----------------------------------------------------------------------------------

  cout << ""<< endl;
  //N        average degree of the network  
  cout <<"#ofNodes: "  <<number_of_nodes<< "  Avg#OfNeighbours(DEGREE): " << degreeOfNetwork(neighbours) << endl;
  
  //Link State Routing:    average number of transmissions,   average path length 
  printOutPut("Link State Routing", linkStateAvgTrans(neighbours), findAvgPathLength(neighbours) );
  
  //Distance Vector Routing:  average number of transmissions, average path length
  printOutPut("Distance Vector Routing", DV_avgtrans(neighbours), findAvgPathLength(neighbours) );

  vector <double> hotPotato1_Trans_Trials;
  vector <double> hotPotato1_Paths_Trials;
  generateHotPotatoTrials(neighbours, & hotPotato1_Trans_Trials, &hotPotato1_Paths_Trials, 1);

  
  
  //Hot Potato I:   average number of transmissions confidence interval,  average path length  confidence interval
  printOutPut("Hot Potato I", calcMean(hotPotato1_Trans_Trials), conInterval(hotPotato1_Trans_Trials)[0], conInterval(hotPotato1_Trans_Trials)[1], calcMean(hotPotato1_Paths_Trials), conInterval(hotPotato1_Paths_Trials)[0], conInterval(hotPotato1_Paths_Trials)[1]);


  vector <double> hotPotato2_Trans_Trials;
  vector <double> hotPotato2_Paths_Trials;
  generateHotPotatoTrials(neighbours, & hotPotato2_Trans_Trials, &hotPotato2_Paths_Trials, 2);
  
  //Hot Potato II:   average number of transmissions confidence interval,  average path length  confidence interval
   printOutPut("Hot Potato II", calcMean(hotPotato2_Trans_Trials), conInterval(hotPotato2_Trans_Trials)[0], conInterval(hotPotato2_Trans_Trials)[1], calcMean(hotPotato2_Paths_Trials), conInterval(hotPotato2_Paths_Trials)[0], conInterval(hotPotato2_Paths_Trials)[1]);
  //--PRINT OUT STUFF----------------------------------------------------------------------------------

  

  cout <<""<< endl;

  cout <<"Diam: "<<CalcDiam(neighbours) << endl;
  //vector <int> acc = {0,1,2,4,1,0,2,1,3,4,2,1,3,4,3,1,2,4,5 };

  //printoutArray("before : ", acc);
  //printoutArray("testing :", removeLoopFromPotato(acc));
  
  //vector <int> y = {0,5, 32 ,2,1, 33, 56, 56, 56};
  //vector <int> x = {5,0, 32 ,2,1, 33, 56, 32, 32,  32, 56, 32};

  //x.erase(x.begin()+5, x.begin()+1);

  //printoutArray("x :", x);
  
  //y.erase(uniquify(y.begin(), y.end()), y.end());
  //x.erase(uniquify(x.begin(), x.end()), x.enxd());
  
  //cout << compare(y, x) << endl;

  /*
  vector <int> temp1 = findHotPotato1Path(0, 1, neighbours);
  
  printoutArray("Before: ", temp1);

  
  printoutArray("After:  ", removeLoopFromPotato(temp1));
  */

  
  //cout << "Currently testing: "<< findHotPotato1Path(0, 1, neighbours) << endl;
  
  
  return 0;

}

//=================================================================================================================
