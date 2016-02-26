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

//============================================================================================================================================
//FROM: http://stackoverflow.com/questions/12200486/how-to-remove-duplicates-from-unsorted-stdvector-while-keeping-the-original-or

/*This stuff is used to remove duplicates from an unsorted vector basically. This is used in general in our program for removing duplicates for providing a base case for
  our recursive removing loops function. 
 */
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

//============================================================================================================================================
//FROM: http://stackoverflow.com/questions/10506595/how-do-i-check-if-two-stdvectors-contain-only-the-same-elements
/*
  Used to check if two vectors have the same elements. 
 */

bool compare(vector<int> v1, vector<int> v2)
{
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    return v1 == v2;
}

//============================================================================================================================================
//FROM: http://cboard.cprogramming.com/cplusplus-programming/126689-converting-string-vector-integer-vector.html
/*
  Just used to convert vector of string to vector of ints. This used in general when we are converting the read in values as str's to int's
 */
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

//============================================================================================================================================

//===STAT FUNCTIONS==============================================================================================================
/*
  These are just basic statistic functions.
 */

//Calculate mean
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
/*
  These custom printing functions are used to just print out data for easy use and testing
 */

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
//--------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------

//Print format for Hot potato format
void printOutPut(string x, double a, double a1, double a2, double b, double b1, double b2)
{
  cout << x << ":  " << a <<" (" << a1 <<", " << a2 <<"), " << b <<" (" << b1 <<", " << b2 <<")" <<endl;
}
//--------------------------------------------------------------------------------------
//Print format": Link State Routing:    average number of transmissions,   average path length 
void printOutPut(string x, double a, double b)
{
  cout << x << ":  " << a << ", " << b <<endl;
}
//--------------------------------------------------------------------------------------
//Help print tester
void printOutPut(string x, double a)
{
  cout << x << ":  " << a <<endl;
}

//===Print HELPER FUNCTIONS===============================================================================================================


//===HELPER FUNCTIONS =========================================================================================================

//get the degree of nodes, so we just get size of neighbours, count number of indexes and return that usign .size function.
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

//Calculating the degree of network by adding up all the neighbours of each node and dividing by number of nodes ie degree of nodes.
double degreeOfNetwork(vector< vector<int> > neighbours)
{
  double sum = 0;

  for (unsigned int i =0; i<neighbours.size(); i++)
  {
    sum += degreeOfNode(i, neighbours);
  }
  
  return sum/neighbours.size();
}

//Contains function for vector, check if item is in list or not, will return 1 if found in list, else 0 if not.
bool elementInList(vector <int> list, int item)
{
  return (find(list.begin(), list.end(), item) != list.end()); 
}

//find the minimum index of the smallest distance to neighbour node, this used for dijkstra algorithm.
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

//Find the maximum value of a list and return it.
int findMax( vector<int> list)
{ 
  return *(max_element(list.begin(), list.end())); 
}

//Generate a queue(vector of int) of 0, ..., size-1 and return it.
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

//Remove an element(item) and return the vector
vector<int> removeElement(vector<int> myVector, int item)
{
  vector<int>::iterator position = find(myVector.begin(), myVector.end(), item);
  if (position != myVector.end()) // == myVector.end() means the element was not found
    myVector.erase(position);

  return myVector;
}
//===HELPER FUNCTIONS =========================================================================================================

//============================================================================================================
//Dijkstra - calculating the distance vector with source indicated and with neighbours(the adjustly list)
vector< int > shortPathDistance (int source, vector< vector<int> > neighbours)
{
  //queue contains the nodes that haven't been look at yet
  vector<int> queue = generateQueue(neighbours.size());

  //Pop off source
  queue.erase(queue.begin() + source);

  vector< vector<int> > shortestPaths(neighbours.size());

  shortestPaths[source] = {source};

  //Create storage for distance vector
  vector<int> distance(neighbours.size());

  //initialize 
  for(unsigned int i =0; i<neighbours.size(); i++)
  {
    if (elementInList(neighbours[i], source))
    {
      //The node is a neighbour so it 1 away
      distance[i]= 1;
      
    }
    else
    {
      //currently unreachable, this large value used as infinity
      distance[i] = 9999;
    }
  }
  //The source is 0 distance away from it self.
  //Source to source indication
  distance[source] = 0;

  //main loop, we use breadth first search here
  while(queue.size() > 0)
  {
    //Next node is the next node we are working with
    int nextNodeQIndex = findMinIndex(distance, queue);
    int nextNodeIndex = (queue[nextNodeQIndex]);
    vector<int> neighbours_of_nextNode = (neighbours[nextNodeIndex]);
    
    //pop off
    queue.erase(queue.begin() + nextNodeQIndex);

    for(unsigned int i =0; i< neighbours_of_nextNode.size(); i++)
    {
      int neighbour = (neighbours_of_nextNode)[i];
      
      if( elementInList(queue, neighbour))
      {
        //calculate the min path
        distance[neighbour] = min(distance[nextNodeIndex]+1, distance[neighbour]);
      }
    }
  }
  //Return distance vector (vector of ints)
  return distance;
}
//============================================================================================================

//Find the path length between two nodes indicated a, b. Uses shortPath
int findPathLength(int a, int b, vector< vector<int> > neighbours)
{
  vector<int> neighbour_distances = shortPathDistance (a, neighbours);

  return neighbour_distances[b];
}
//============================================================================================================

//Calculate the diameter of the network
int CalcDiam( vector< vector<int> > neighbours )
{
  //Calculate longest shortest path
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

//Finding the average path length by finding all the paths for each pair.
//We divide by neighbours squared because we are doing pairs both ways.
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

//============================================================================================================

//calculating the distance vector average transmissions.
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

//=============================================================================================================================
/*
  Link state stuff
 */

//Here we simulate the flooding process of linkstate with memory
double linkStateFlooding(int source, vector< vector<int> > neighbours)
{
  //store number of transmissions
  int trans = 0;
  
  vector <int> nodesSend(neighbours.size());
  
  vector<int> queue; //this will contains nodes in a sequence
  vector<int> queueParent; //this will contains parent node parallel list
  
  //send to out going links, does not send if its a deadend, else it must send once, and receive once, and source only once
  //We can check because each node will tranmission unless it is a dead end.
  
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
  return trans;
}

//---------------------------------------------------------------------------------------------------------------------------------------

//Calculate the average number of transmission for link state
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



//=============================================================================================================================================
//Theses are the "Hot Potato" related functions

//we simulate the hot potato path algorithm here given the source and dest and type of whether hot potato 1, or hot potato 2
vector <int> findHotPotatoPath(int source, int dest, vector< vector<int> > neighbours, int type)
{
  vector <int> path;

  //added first to current list
  path.push_back(source);

  int currentNode = path[path.size()-1];

  //While we have not reach the destination
  while((currentNode = path[path.size()-1]) != dest)
  {     
    vector<int> current_node_neighbours = neighbours[currentNode];

    //ensure we can pass to neighbour
    if((path.size() >= 2) && (current_node_neighbours.size() >1))
    {
      int previousNode = path[(path.size()-2)];
      //Do not pass backwards by removing sender from receiver's list 
      current_node_neighbours = removeElement(current_node_neighbours, previousNode);
    }

    //The track the random neighbour, we pass to
    int rand_neighbour;

    //Check whether we are doing hot potato 1 or 2, if 2 we check if neighbour is destination then just pass to it
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

    //Pass to package to next
    path.push_back(rand_neighbour);

  }
  return path;
}

//---------------------------------------------------------------------------------------------------------------------------------------

/*
  Take in vector and remove any loops. A loop is where the package is sent to that node twice so we can remove all the traveling to and back to that node
  This recursively remove all loops from given list which is a path of the hot potato. The base case is checking whether the elements in the list is unqiue,
  because once all loops are removed all duplicates are removed thus we know all loops are removed.
 */
vector <int> removeLoopFromPotato (vector <int> list) 
{
  //-------------------------------------------------------------------------------------
  //Base case stuff
  //Checking uniqueness of the vectors comparing: hot potato trail and duplicates removed from hot potato initial trail with no modifiation ie removing loops.
  vector<int> uniqueArray = list;
  uniqueArray.erase(uniquify(uniqueArray.begin(), uniqueArray.end()), uniqueArray.end());
  if (compare(uniqueArray, list))
  {
    return list;
  }
  //-------------------------------------------------------------------------------------

  //We remove loops by checking the front and back of the vector till we get a match, once we get a match we remove the loop.
  
  vector <int> c = list;

  int front_index = 0;
  int back_index = 0;

  int break1 = 0;

  //iterate over front and back of the potato trail till we find loop.
  for(int i =0; i<(int)list.size(); i++)
  {
    
    for (int x = (int)list.size()-1; x > i+1; x--)
    {
      if (list[i] == list[x])
      {
        //front and back index found of the loop
        front_index = i;
        back_index = x;

        //If we found a loop match, we no longer need to iterate and break out both for loops
        break1 =1;
        break;
      }
    }
    if (break1 ==1)
    {
      break;
    }
    
  }
  //Remove loop portion of the potato trail. This removes one loop found.
  c.erase(c.begin() +front_index, c.begin()+back_index); 
 
  return removeLoopFromPotato (c);
}

//---------------------------------------------------------------------------------------------------------------------------------------

double hotPotato(int source, int dest, vector< vector<int> > neighbours, vector<int> *path, vector<int> *pathLoopRemoved, int type)
{
  
  *path = findHotPotatoPath(source, dest, neighbours, type);
  *pathLoopRemoved = removeLoopFromPotato(*path);
  
  return (*path).size() + (*pathLoopRemoved).size() - 2;  
}

//---------------------------------------------------------------------------------------------------------------------------------------
//performs the hotpotato calculations with results of hotpotato trials with loops removed and not removed.
void hotPotatoTrial(vector< vector<int> > neighbours, double *avgTrans, double *avgPathLength, int type)
{
  //tract transmissions
  double sum_trans =0;
  //tract path
  double sum_path_length =0;

  //We are only checking unique pairs, so a-b is check then b-a is not checked
  int loopCount = 0;
  
  for(unsigned int i =0; i< neighbours.size(); i++)
  {
    
    for(unsigned int j = i+1; j<neighbours.size(); j++)
    {
      loopCount++;
      vector<int> path;
      vector<int> pathLoopRemoved;
      sum_trans += hotPotato(i, j, neighbours, &path, &pathLoopRemoved, type);
      sum_path_length += pathLoopRemoved.size() - 1;
    }
  }

  //calculate average number of transmissions
  *avgTrans = sum_trans/(neighbours.size());
  
  //calculate avergae path legnth
  *avgPathLength = sum_path_length/(loopCount);
  
}
//---------------------------------------------------------------------------------------------------------------------------------------
/*
  For generating the results for the Hot Potato 1 and 2. Note that these are averaged over 10 trials as required from assignment description.
  This function delegates to other functions to get the average over 10
 */
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
//=============================================================================================================================================

//====M A I N=============================================================================================================

int main (int argc, char *argv[])
{
  //Change the random seed each time.
  srand(time(NULL));
  
  //-------------------------------------------------------------------
  //Check the number of arguments, that its valid
  //EX) ./hsim graph1.txt
  //Expect 2 commandline parameters
  if (argc !=2)
  {
    cout << "Invalid number of argument << endl" << endl;
    return 1;
  }
   //------------------------------------------------------------------

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  /*
    Reading in file and preparing neighbours, neighbours is a vector of vectors of ints. Where the index of outer vector of neighbours indicates the node, example index 0 is
    node 0, and the vector at index 0 is node 0's list of neigbhours.
  */
  vector< vector<int> > neighbours;

  //Reading file
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
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------
  

  //--PRINT OUT STUFF----------------------------------------------------------------------------------

  cout << ""<< endl;
  //N        average degree of the network  
  cout <<number_of_nodes<< "  " << degreeOfNetwork(neighbours) << endl;
  
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

   cout <<""<< endl;
   
  //--PRINT OUT STUFF----------------------------------------------------------------------------------

  return 0;

}
//============================================================================================================================================
