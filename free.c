
void free(void *ptr)
{

   //if pointer is null then return.
   if(ptr==NULL)
   {

      return;
   }
   else{



        pthread_mutex_lock(&mutex);
		
            // go to the node with the same address as that odf the argument.
          //  printf("INSIDE FREE\n" );
             Node * go_to_the_address;
             int i=0;
             int pass=0;
             for(i=0;i<NUM_ARENA;i++)
             {

                  go_to_the_address=Arena_Array[i].head;
                   while(go_to_the_address!=NULL)
                   {
                       //printf("INSID FREE bhfuyf\n" );
                     if(go_to_the_address->startAddr==ptr)
                     {
                         pass=1;
                         break;
                     }

                      go_to_the_address=go_to_the_address->next;
                   }


                  if(pass==1)
                  {
                  //  printf("THE ARENA RETURNED IS %d\n", i);
                    break;
                  }


              }
		if(i<NUM_ARENA)
		global_free_count[i]=global_free_count[i]+1;
            //  printf("INSID Flkhlokh;lREE\n" );
                //if the address is not found in the list or is already freed then  return.
                if(!go_to_the_address||go_to_the_address->free_flag==0)
                {

                  pthread_mutex_unlock(&mutex);
                  return;

                }
              // update the list and merge the buddies.
             go_to_the_address->memory_size=0;
             go_to_the_address->free_flag=0;
             merge_buddy_node(i);

              pthread_mutex_unlock(&mutex);

      }


}
