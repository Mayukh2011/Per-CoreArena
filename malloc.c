

void * malloc(size_t size)
{

  //NUM_ARENA=get_nprocs_conf();
 //printf("the number of cpu cores are; %d\n",NUM_ARENA);
  pthread_mutex_lock(&mutex);

  if(global_count==0)
  {
    //printf(":::::::::::::::::::::::FIRST TIME INITIALIZATION:::::::::::::::::::::::\n");
	NUM_ARENA=sysconf(_SC_NPROCESSORS_ONLN);


	int h=0;

	for(h=0;h<NUM_ARENA;h++)
	{

		global_malloc_count[h]=0;
		global_free_count[h]=0;
	}


    //printf("THE NUMBER OF ARENA ALLOCATED IS: %d\n", NUM_ARENA);
    int i = 0;
     initialize_arena();
     for ( i = 0; i < NUM_ARENA; i++)
        pthread_mutex_init(&arena_mutexes[i], NULL);

        global_count++;
  }
  pthread_mutex_unlock(&mutex);





  //printf("THE GLOBAL COUNT IS %d\n",global_count );
  //printf("INSIDE MALLOC %d\n",pthread_self());
  if(size==0)
  {
    return NULL;
  }

  int multiple;

 multiple = ceil(size/(float)getpagesize());
 //printf("The multiple is: %d\n",multiple );

    //
      Node *pointer;
  //  while(1){
  time_t t;
srand((unsigned) time(&t));
  int i=0;
int k=0;
  int pass=0;
 while(1)
 {

   for(i=0;i<NUM_ARENA;i++){
			k=rand() % 32;

                        if(pthread_mutex_trylock(&arena_mutexes[k])==0){

                              pass=1;
                                    break;
                        }

                      }

                      if(pass==1)
                      {

                        break;
        	            }

  }
			//pthread_mutex_unlock(&arena_mutexes[i]);
                                           	  // printf("************* MUTEX %d IS LOCKING*************\n",i);



                      int arena=k;                                      // MALLOC CODE WILL START FROM HERE:
							pthread_mutex_lock(&mutex);
            //  printf("INSIDE MALLOC\n");
            							if(arena<NUM_ARENA){
								//	printf("arena[%d]------>>> %llu\n",arena,global_malloc_count[arena]);
            								global_malloc_count[arena]=global_malloc_count[arena]+1;
								}

                                                        //   printf(" the arena in use is %d\n ",arena);
                                                           //sleep(1);
									//sleep(1);
                                                            //Node *head;
                                                            Node *node;


                                                           if(Arena_Array[arena].head==NULL)
                                                           {
                                                                // printf("INSIDE MALLOC IF\n");

                                                                     node=call_for_space(arena,multiple);
                                                                     pointer=Arena_Array[arena].head;
                                                                     //divide the memory until the appropriate size is achieved.

                                                                      while(size<node->size&& node->size>8)
                                                                      {
                                                                        if((node->size/2)<size)
                                                                        break;
                                                                         divide_node(node);
                                                                      }


                                                                     // once we get the appropriate chunk then populate the information regarding the allocation.
                                                                      pointer->free_flag=1;
                                                                      pointer->memory_size=size;


                                                            }
                                                            else{

                                                                        //printf("INSIDE MALLOC ELSE PART %d \n",pthread_self() );
                                                                        // serach the entire list for appropriate place to insert the requested memory.
                                                                        pointer=search_where_to_put(arena,size);

                                                                                if(pointer!=NULL){
                                                                                          //  printf("IF POINTER IS NOT NULL %d \n",pthread_self() );
                                                                                                // once  we get an memory chunk to place the requested size, divide it, if possible to get an exact fit.
                                                                                                while(1){
                                                                                                  if((pointer->size)/2>=size&&(pointer->size)>8)
                                                                                                  {
                                                                                                    divide_node(pointer);
                                                                                                    continue;
                                                                                                  }
                                                                                                  break;
                                                                                                }
                                                                                                // update the list, regarding the memory chunk.
                                                                                                  pointer->memory_size=size;
                                                                                                  pointer->free_flag=1;

                                                                                            }


                                                                                else{
                                                                                       // printf("IF POINTER IS NOT NULL ELSE PART %d \n",pthread_self() );
                                                                                          Node *newMemorycallNode;

                                                                                          Node *Last;
											//	printf("before last points to head\n");
                                                                                           Last=Arena_Array[arena].head;
											//	printf("after last points to head\n");
                                                                                           //if the size requested is too big then call for more space from the kernel and add that to the list.
                                                                                            while(Last->next!=NULL)
                                                                                            {

                                                                                              Last=Last->next;
                                                                                            }
											//	printf("AFTER LAST POINTS TO NULL\n");
                                                                                            newMemorycallNode=call_for_space(arena,multiple);
                                                                                            Last->next=newMemorycallNode;

                                                                                            pointer=search_where_to_put(arena,size);

                                                                                          while(1){
                                                                                            if((pointer->size)/2>=size)
                                                                                            {
                                                                                              divide_node(pointer);
                                                                                              continue;
                                                                                            }
                                                                                            break;
                                                                                          }
                                                                                            // update the list, regarding the memory chunk.
                                                                                            pointer->memory_size=size;
                                                                                            pointer->free_flag=1;


                                                                                }



                                                                  }



                                                            //MALLOC CODE WILL END HERE:



                                                            pthread_mutex_unlock(&mutex);
								                                            pthread_mutex_unlock(&arena_mutexes[i]);
                                              //  printf("************* MUTEX %d IS UNLOCKING %d*************\n",i,pthread_self());



                                            //    pthread_mutex_lock(&mutex);
                                              //traversal(arena,Arena_Array[arena].head);
                                              //pthread_mutex_unlock(&mutex);
                                               return pointer->startAddr;

                            //}





  //      }



//}
//printf("**************AFTER BREAK***************\n");
//pthread_mutex_unlock(&arena_mutexes[i]);
 //return NULL;
  //return pointer->startAddr;



}
