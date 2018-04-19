

void *realloc(void *ptr, size_t size)
{

// if size is 0 then return Null. and free the pointer
  if(size==0)
  {
    free(ptr);
    return NULL;
  }
  else{
    //  printf("INDISE REALLOC\n" );

      pthread_mutex_lock(&mutex);

                Node * go_to_the_address;
              int i=0;
              int pass=0;
              for(i=0;i<NUM_ARENA;i++)
              {
                  //printf("STRATING FIRST I %d\n",i );



                           go_to_the_address=Arena_Array[i].head;
                            while(go_to_the_address!=NULL)
                            {
                                //printf("INSID FREE bhfuyf %d\n",i );
                                if(go_to_the_address->startAddr==ptr)
                                {
                                    pass=1;
                                    break;
                                }

                               go_to_the_address=go_to_the_address->next;
                            }




                  if(pass==1)
                   {
                     //printf("THE ARENA RETURNED IS %d\n", i);
                     break;
                   }
                   //printf("ENDNING FIRST I %d\n",i );


               }

            pthread_mutex_unlock(&mutex);


            void *Addr;
              // if address is not found the malloc the size
              if (!go_to_the_address) {

                  Addr = malloc(size);
              }
              else {
                    // if size asked for is greater than the original size then reserve the space using malloc and then copy the original content.
                  if (go_to_the_address->size < size) {

                      Addr = malloc(size);

                      Addr = memcpy(Addr, ptr, go_to_the_address->size );
                      // once allocated the free the original address.
                      free(ptr);
                  }
                  else {
                    // else point to the original address.
                      Addr = ptr;
                  }
              }

              return Addr;
      }




}
