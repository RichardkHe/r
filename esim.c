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
char M[2];
int A;
int K;
int F;
double e;
int B;
int N;
int R;
int T;
vector<double> seeds;
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

void parseInputArguments(int argc, char * argv[])
{
  strcpy(M, argv[1]);
  A = atoi(argv[2]);
  K = atoi(argv[3]);
  F = atoi(argv[4]);
  e = atof(argv[5]);
  B = atoi(argv[6]);
  N = atoi(argv[7]);
  R = atoi(argv[8]);
  T = atoi(argv[9]);

  for(int i =10; i < argc; i++)
  {
      seeds.push_back(stod(argv[i]));
  }
}


void printInputArguments()
{
  //print out all command line arguments in the same line
  // M A K F e B N R T seed1 seed2 seed3 seed4 seed5

  printf("%s %d %d %d %lf %d %d %d %d", M, A, K, F, e, B, N, R, T);

  for(double i =0; i < seeds.size(); i++)
  {
      cout << seeds[i] << " ";
  }

  cout << endl;
}


void printArgumentError(int argc)
{
    printf("Invalid number of arguments. Need at least 11, given %d\n", argc);
    printf("Refer to the Readme.md to see proper execution parameters.\n");
}

int calculateLengthOfBlock(int F, int K)
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
vector<double> avgFrameTx(vector<int> re_txRecord , vector<int> frame_ok_counts)
{
  //assuming 5 trials

  vector<double> avgFrameTxRecord;

  for(int i =0; i<T; i++)
  {
    avgFrameTxRecord.push_back((frame_ok_counts[i] + re_txRecord[i])/frame_ok_counts[i]);
  }

  return avgFrameTxRecord;
}


/*
  AVERAGED OVER 5 trail runs

  Through = (F * the total number of correctly received frames)/(the total time required
  to correctly receive these frames)

 */

vector<double> calcThroughputVector(int R, vector<int> frame_ok_countRecordOfTrails)
{
  //Right now assuming total time is the clockRecord, and 5 trials

  vector<double> throughputRecord;

  for(int i=0; i<T; i++)
  {
    throughputRecord.push_back((F* frame_ok_countRecordOfTrails[i])/R);
  }

  return throughputRecord;
}



//=============================================================================================



int main (int argc, char *argv[])
{

  //Check the number of arguments
  if (argc < 11)
  {
    printArgumentError(argc);
    return 1;
  }

  parseInputArguments(argc, argv);

  printInputArguments();

  int num_of_blocks = K;


  int length_of_block = calculateLengthOfBlock(F, K);

  //Store results

  vector <int> frames_transmitted;
  vector <int> re_txRecord;

  //Run over T trials. Trails should equal 5.
  for (int z = 0; z < T; z++)
  {
    srand(seeds[z]);

    int re_tx;
    int clock = 0;
    int frame_ok_count = 0;
    //int num_of_blocks = K;
    //int length_of_block = calculateLengthOfBlock(F, K);

    while(clock < R)
    {
      int tx_ok = 1;

      if(K == 0)
      {
        int num_of_errors = 0;

        for (int i =0; i < F; i++)
        {
          if (strcmp(M, "I") == 0)
          {
            if(checkError(e))
            {
              num_of_errors++;
            }
          }
          else
          {
            if (checkBurstError(N, B, e))
            {
              num_of_errors++;
            }
          }
        }

        if (num_of_errors > 1)
        {
          tx_ok = 0;
        }

      }
      else
      {
        vector<int> blockErrors;

        //Check all blocks
        for(int i = 0; i < num_of_blocks;i++)
        {
          int num_of_errors = 0;

          //Check each bit of each block
          for(int j = 0; j < length_of_block; j++)
          {
            if (strcmp(M, "I") ==0)
            {

              if(checkError(e))
              {
                num_of_errors++;
              }
            }
            else
            {
              if (checkBurstError(N, B, e))
              {
                num_of_errors++;
              }
            }
            clock++;
          }

          blockErrors.push_back(num_of_errors);
        }

        //Receiver check block errors
        for(int i = 0; i < num_of_blocks; i++)
        {
          if(blockErrors[i] > 1)
          {
            tx_ok = 0;
          }
        }
      }

      //Sender waits for receiver
      clock += A;


      //Sender checks if frame tx successful, up frame_ok_count
      if(tx_ok){
	       frame_ok_count++;
      }
      //else we add additional A bit time for frames that were eventually received correctly
      //and deal with retransmissions
      else{
        re_tx++;
      }

      //clock++;
    }
    frames_transmitted.push_back(frame_ok_count);
    re_txRecord.push_back(re_tx);
  }


  //=========================================================================================================
  //For throughput
  vector<double> Throughput = calcThroughputVector(R, frames_transmitted);
  vector<double> ThroughputConfidenceInterval = conInterval(Throughput);
  //=========================================================================================================
  //for average number of frame tx
  vector<double> avgTxs = avgFrameTx(re_txRecord, frames_transmitted);
  vector<double> avgTxConfidenceInterval = conInterval(avgTxs);
  //=========================================================================================================
  cout << calcMean(avgTxs) <<" (" <<  avgTxConfidenceInterval[0] << ", " << avgTxConfidenceInterval[1] << ") "<< endl;
  cout << calcMean(Throughput) <<" (" <<  ThroughputConfidenceInterval[0] << ", " << ThroughputConfidenceInterval[1] << ") "<< endl;

  return 0;

}
