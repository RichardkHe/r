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
