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

//-----------------------------
//Global Commandline arguments
char M[2] = "B";
int A =50;
int K;
int F = 4000;
//double e;
//int B;
//int N;
int R = 5000000;
int T = 5;
vector<int> seeds;

int N_cpy;
int B_cpy;
//-----------------------------

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

  double mean = calcMean(inputlist);

  double crt = 2.776;

  double c1 = mean - crt*(std/sqrt(inputlist.size()));
  double c2 = mean + crt*(std/sqrt(inputlist.size()));

  vector<double> myvector;
  myvector.push_back(c1);
  myvector.push_back(c2);

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


int calculateLengthOfBlock(int F,double K)
{
  if (K == 0)
  {
    return 0;
  }

	int bitsPerBlock = F/K;
	int r_bits = calcrbits(F/K);

	return bitsPerBlock + r_bits;
}

//=============================================================================================
/*

  AVERAGED OVER 5 trail runs

 calculate the average number of frame tx's
 = (total number of frame tx including re tx "this be F + retransmissions")/ (the number of frames correctly received)

 */
vector<double> avgFrameTx(vector<double> re_txRecord , vector<double> frame_ok_counts)
{
  //assuming 5 trials

  vector<double> avgFrameTxRecord;

  for(int i =0; i<T; i++)
  {
    //cout << frame_ok_counts[i] << endl;
    //cout << 5/2.3 << endl;
    //cout << (frame_ok_counts[i] + re_txRecord[i])/frame_ok_counts[i]<< endl;
    avgFrameTxRecord.push_back((frame_ok_counts[i] + re_txRecord[i])/frame_ok_counts[i]);
  }

  return avgFrameTxRecord;
}


/*
  AVERAGED OVER 5 trail runs

  Through = (F * the total number of correctly received frames)/(the total time required
  to correctly receive these frames)

 */

vector<double> calcThroughputVector(int R, vector<double> frame_ok_countRecordOfTrails)
{
  //Right now assuming total time is the clockRecord, and 5 trials

  vector<double> throughputRecord;

  for(int i=0; i<T; i++)
  {
    //cout << (F* frame_ok_countRecordOfTrails[i])/double(R) << endl;
    //cout << float(R)<< endl;
    throughputRecord.push_back((F* frame_ok_countRecordOfTrails[i])/double(R));
  }

  return throughputRecord;
}


//--------------------------------------------------------------------------------------------------------------------------------

int GetNumberBurstOfErrors(double N,double B,double length_block,double * clock, double e)
{
  //int N_cpy = N;
  //int B_cpy = B;

  bool isBurstPeriod = false; //was false

  double NumErrors = 0;

  for(int i =0; i < length_block; i++)
  {
    if(isBurstPeriod)
    {
      B_cpy--;
      if(B_cpy <= 0)
      {
        isBurstPeriod = false;
        B_cpy = B;
      }

      if(checkBurstError(N, B, e))
      {
        NumErrors++;
      }
    }
    else
    {
      N_cpy--;

      if(N_cpy <= 0)
      {
        isBurstPeriod = true;
        N_cpy = N;
      }
    }
    //cout << isBurstPeriod << endl;

    (*clock)++;

  }
  //cout << *clock << endl;
  //cout << NumErrors << endl;
  return NumErrors;
}


//--------------------------------------------------------------------------

//=============================================================================================


int generateRandomError(int length_block,double *clock, int N, int B, double e)
{
 double num_of_errors = 0;
  //Check each bit of each block
  if (strcmp(M, "I") ==0)
  {
    //Independent model
    for(int j = 0; j < length_block; j++)
    {

      if(checkError(e))
      {
        num_of_errors++;
      }


      (*clock)++;
    }
  }

  else //Burst model
  {
    //cout << "Burst Model" << endl;
    num_of_errors = GetNumberBurstOfErrors(N, B, length_block, clock, e);
  }
  //cout << num_of_errors << endl;
  return num_of_errors;

}

//=============================================================================================

//generateRandomError(F, &clock, N, B)
vector<int> generateBlockErrors(int num_of_blocks,double length_of_block,double *clock, int N, int B, double e)
{
  vector<int> blockErrors;

  for(int i = 0; i < num_of_blocks;i++)
  {
    double num_of_errors = generateRandomError(length_of_block, clock, N, B, e);

    blockErrors.push_back(num_of_errors);
  }

  return blockErrors;

}

int checkBlockErrors(vector<int> blockErrors)
{
  for(double i = 0; i < blockErrors.size(); i++)
  {
    if(blockErrors[i] > 1)
    {
      return 1;
    }
  }
  return 0;
}





//=============================================================================================



double oneTrival(int K, double e, int B, int N)
{

  double num_of_blocks = K;
  double length_of_block = calculateLengthOfBlock(F, K);

  //Store results
  vector <double> frames_transmitted;
  vector <double> re_txRecord;



  //=========================================================================================================
  if(K == 0)
  {
    //Run over T trials. Trails should equal 5.
    for (int z = 0; z < T; z++)
    {
      N_cpy = N;
      B_cpy = B;
      srand(seeds[z]);

      double re_tx =0;
      double clock = 0;
      double frame_ok_count = 0;

      while(clock < R)
      {
        double num_of_errors = generateRandomError(F, &clock, N, B, e);
        if(num_of_errors > 1)
        {
          re_tx++;
        }
        else
        {
          frame_ok_count++;
        }

        clock += A;
      }
      frames_transmitted.push_back(frame_ok_count);
      re_txRecord.push_back(re_tx);
    }
  }
  else
  {
    //else everything below
    //=========================================================================================================
    //working
    //Run over T trials. Trails should equal 5.
    for (int z = 0; z < T; z++)
    {
      N_cpy = N;
      B_cpy = B;
      srand(seeds[z]);

      double re_tx =0;
      double clock = 0;
      double frame_ok_count = 0;

      while(clock < R)
      {
        vector<int> blockErrors;

        //Check all blocks
        blockErrors = generateBlockErrors(num_of_blocks, length_of_block, &clock, N, B, e);

        //Sender waits for receiver
        clock += A;

        //Sender checks if frame tx successful, up frame_ok_count
        //Receiver check block errors
        if((!checkBlockErrors(blockErrors))){
          frame_ok_count++;
          //cout << frame_ok_count<< endl;
        }
        else{
          re_tx++;
        }
      }
      frames_transmitted.push_back(frame_ok_count);
      re_txRecord.push_back(re_tx);
    }
  //=========================================================================================================
  }


  /*
  cout << "F:" << frames_transmitted[0] << "Re-Tran:" << re_txRecord[0] <<endl;
  cout << "F:" << frames_transmitted[1] << "Re-Tran:" << re_txRecord[1] <<endl;
  cout << "F:" << frames_transmitted[2] << "Re-Tran:" << re_txRecord[2] <<endl;
  cout << "F:" << frames_transmitted[3] << "Re-Tran:" << re_txRecord[3] <<endl;
  cout << "F:" << frames_transmitted[4] << "Re-Tran:" << re_txRecord[4] <<endl;
  */

  //int i=0;
  //cout << GetNumberBurstOfErrors(9, 10, 10, &i) << endl;



  //=========================================================================================================
  //for average number of frame tx
  vector<double> avgTxs = avgFrameTx(re_txRecord, frames_transmitted);
  vector<double> avgTxConfidenceInterval = conInterval(avgTxs);

  //=========================================================================================================

  //For throughput
  vector<double> Throughput = calcThroughputVector(R, frames_transmitted);
  vector<double> ThroughputConfidenceInterval = conInterval(Throughput);
  //=========================================================================================================
  //cout << calcMean(avgTxs) <<" (" <<  avgTxConfidenceInterval[0] << ", " << avgTxConfidenceInterval[1] << ") "<< endl;
  //cout << calcMean(Throughput) <<" (" <<  ThroughputConfidenceInterval[0] << ", " << ThroughputConfidenceInterval[1] << ") "<< endl;
  //cout << ""<< endl;

  return calcMean(Throughput);
}


void printoutArray(string x, vector<double> vec)
{
  cout << x << " = [";
  for (unsigned int y=0; y< vec.size(); y++)
  {
    if (y == (vec.size()-1))
    {
      cout << vec[y];
    }
    else
    {
      cout << vec[y] << ", ";
    }
  }
  cout << "]";
  cout <<""<<endl;
}

int main()
{

  seeds.push_back(1534546);
  seeds.push_back(2133323);
  seeds.push_back(377);
  seeds.push_back(456548);
  seeds.push_back(59998);

  //static const int arr[] = {16,2,77,29};
  //vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );

  static const int arr1[] = {0,1,2,10,40,100,400,1000};
  vector<int> K_array (arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]) );

  static const double arr[] = {0.0001,0.0003,0.0005,0.0007,0.001};
  vector<double> e_array (arr, arr + sizeof(arr) / sizeof(arr[0]) );

  static const int arr2[] = {50,500};
  vector<int> B_array (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );

  static const int arr3[] = {5000, 1000};
  vector<int> N_array (arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]) );

  vector<double> printout_array;
  vector<double> printout_array1;
  

//void oneTrival(int K, double e, int B, int N);
//cout << oneTrival(0, 0.0001, 50, 5000) << endl;

//-INDEPENDENT MODEL--------------------------------------------------------------------------------------------------
  /*
  cout << "------------------------------------------------------------------------------------------"<<endl;
  cout << "independent Model, B=0, N=0"<< endl;
  for (unsigned int i =0; i < e_array.size(); i++)
  {
    cout << "================================================"<< endl;
    cout << "Error rate: " << e_array[i] << endl;

    for (unsigned int x=0; x < K_array.size(); x++)
    {

      printout_array.push_back(oneTrival(K_array[x], e_array[i], 0, 0));
      
    }
    
    printoutArray("Throughput", printout_array);
    printout_array.clear();

    cout << "================================================"<< endl;
  }
  cout << "------------------------------------------------------------------------------------------"<<endl;
  */
//----------------------------------------------------------------------------------------------------


//-Burst MODEL (N=5000,B=50) ----------------------------------------------------------------------------
  
  cout << "------------------------------------------------------------------------------------------"<<endl;
  cout << "Burst Model, N=5000,B=50 "<< endl;
  for (unsigned int i =0; i < e_array.size(); i++)
  {
    cout << "================================================"<< endl;
    cout << "Error rate: " << e_array[i] << endl;

    for (unsigned int x=0; x < K_array.size(); x++)
    {      
      printout_array.push_back(oneTrival(K_array[x], e_array[i], 50, 5000));
    }

    printoutArray("Throughput", printout_array);
    printout_array.clear();
    
    cout << "================================================"<< endl;
  }
  cout << "------------------------------------------------------------------------------------------"<<endl;
//-Burst MODEL (N=5000,B=50) ----------------------------------------------------------------------------
  
//-Burst MODEL (N=1000,B=50) ----------------------------------------------------------------------------
  
  cout << "------------------------------------------------------------------------------------------"<<endl;
  cout << "Burst Model, N=1000,B=50 "<< endl;
  for (unsigned int i =0; i < e_array.size(); i++)
  {
    cout << "================================================"<< endl;
    cout << "Error rate: " << e_array[i] << endl;

    for (unsigned int x=0; x < K_array.size(); x++)
    {      
      printout_array.push_back(oneTrival(K_array[x], e_array[i], 50, 1000));
    }

    printoutArray("Throughput", printout_array);
    printout_array.clear();
    
    cout << "================================================"<< endl;
  }
  cout << "------------------------------------------------------------------------------------------"<<endl;
//-Burst MODEL (N=1000,B=50) ----------------------------------------------------------------------------


  //-Burst MODEL (N=5000,B=500) ----------------------------------------------------------------------------
  
  cout << "------------------------------------------------------------------------------------------"<<endl;
  cout << "Burst Model, N=5000,B=500 "<< endl;
  for (unsigned int i =0; i < e_array.size(); i++)
  {
    cout << "================================================"<< endl;
    cout << "Error rate: " << e_array[i] << endl;

    for (unsigned int x=0; x < K_array.size(); x++)
    {      
      printout_array.push_back(oneTrival(K_array[x], e_array[i], 500, 5000));
    }

    printoutArray("Throughput", printout_array);
    printout_array.clear();
    
    cout << "================================================"<< endl;
  }
  cout << "------------------------------------------------------------------------------------------"<<endl;
//-Burst MODEL (N=5000,B=500) ----------------------------------------------------------------------------


  //-Burst MODEL (N=1000,B=500) ----------------------------------------------------------------------------
  
  cout << "------------------------------------------------------------------------------------------"<<endl;
  cout << "Burst Model, N=5000,B=500 "<< endl;
  for (unsigned int i =0; i < e_array.size(); i++)
  {
    cout << "================================================"<< endl;
    cout << "Error rate: " << e_array[i] << endl;

    for (unsigned int x=0; x < K_array.size(); x++)
    {      
      printout_array.push_back(oneTrival(K_array[x], e_array[i], 500, 1000));
    }

    printoutArray("Throughput", printout_array);
    printout_array.clear();
    
    cout << "================================================"<< endl;
  }
  cout << "------------------------------------------------------------------------------------------"<<endl;
//-Burst MODEL (N=1000,B=500) ----------------------------------------------------------------------------
  return 0;
}
