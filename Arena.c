

typedef struct Arena
{

    Node * head;

}Arena;

struct Arena Arena_Array[32];

void initialize_arena()
{
  //printf("INITIALIZING ARENA\n" );
      int i=0;
      for( i=0;i<NUM_ARENA;i++)
      {

        Arena_Array[i].head=NULL;
      }



}
