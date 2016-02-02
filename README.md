CMPUT 313, Assignment 1, Winter 2016  (worth 9%)

A Study of a Combined Error Detection and Error Correction Scheme
Due Tuesday Feb 2, 5pm 

We use the following function to check if power of 2:

//http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/

We going use only 5 trials, T = 5 , t[0.975;4] = 2.776 and 5% confidence interval
For our analysis we will use the following constants:
A(feedback bit time)  = 50
R(simulation bit time) = 5,000,000
F(frame size) = 4000
T(Trials) = 5 with seeds ["1534546", "2133323" ,"377" ,"456548" ,"59998"] 


For our simulation use the Makefile and esim.c in main directory. Run make, and run for example
n the commandline:

./esim I 50 0 4000 0.0001 0 0 5000000 5 153456 2133323 377 456548 59998



The parameters are to be input as command line arguments:

· M (character): Indicates the error model used:  I for independent, B for Burst

· A (integer): You can assume the feedback time is 50 bit time units.

· K (integer):  The number of blocks. You should at least explore the range of values of K =0, 1, 2,10,40,100,400,1000.  Note that your K should be chosen such that F is a multiple of K.

· F (integer)   The size of the frame in number of bits.   You can assume this is 4000 bits. 

· e (floating)  The probability that a bit is in error.  You will vary this for e = 0.0001, 0.0003, 0.0005, 0.0007,  0.001.

· B burst length.  0 for the independent model.  For the burst model, set this to 50 and 500 bit times.

· N non-burst length.  0 for the independent model.  For the burst model, set this to 5000 and 1000 bit times.

· R (integer)   The length of the simulation in bit time units.   You must run this long enough to obtain stable results (for reasonable error rates).  This should be run on the order of 5,000,000 bit time units.

· T  t1 t2 t3 ... tT (integer)   The number of trials, followed by seeds for the trials.  For this simulation, you can set T to 5.



The output of the program:

* the input parameters (in the same format as in the input line)


* the average number of frame transmissions followed by the confidence interval for this metric.  The average number of frame transmissions is the total number of frame transmissions including retransmissions (for frames that were eventually received correctly) divided by the number of frames correctly received averaged over the 5 trial runs.


* the throughput and confidence interval for throughput.  Throughput is  (F * the total number of correctly received frames) divided by the total time required to correctly receive these frames averaged over the 5 trial runs.


For generating all the results, we used the c files in testingTrials directory, all results were pasted in the end of our report. 
