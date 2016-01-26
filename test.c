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


