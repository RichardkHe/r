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
          clock++;
        }

        if (num_of_errors > 1)
        {
          tx_ok = 0;
        }

      }




     for(int i = 0; i < num_of_blocks; i++)
        {
          if(blockErrors[i] > 1)
          {
            tx_ok = 0;
          }
        }

./esim I 50 10 4000 0.0001 0 0 40000 5 1 2 3 4 7


  //Run over T trials. Trails should equal 5.
  for (int z = 0; z < T; z++)
  {
    srand(seeds[z]);

    int re_tx =0;
    int clock = 0;
    int frame_ok_count = 0;

    while(clock < R)
    {
      vector<int> blockErrors;

      //Check all blocks
      blockErrors = generateBlockErrors(num_of_blocks, length_of_block, &clock);
      
      //Sender waits for receiver
      clock += A;

      //Sender checks if frame tx successful, up frame_ok_count
      //Receiver check block errors
      if((!checkBlockErrors(blockErrors))){
        frame_ok_count++;
      }
      else{
        re_tx++;
      }
    }
    frames_transmitted.push_back(frame_ok_count);
    re_txRecord.push_back(re_tx);
  }
