//function to create new node
Node* create_new_node(int arena,int size,void* address)
{

//printf("INSIDE CREATE NODE\n" );
  //Node * newNode=mmap(0, sizeof(struct Node), PROT_READ | PROT_WRITE,MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	Node * newNode=sbrk(sizeof(struct Node));



  newNode->size=size;
  newNode->free_flag=0;
  newNode->startAddr=address;

  if(Arena_Array[arena].head==NULL)
  {
    Arena_Array[arena].head=newNode;

  }
  else
  {

    Node *last=Arena_Array[arena].head;
  while(last->next!=NULL)
  {

    last=last->next;
  }

    last->next=newNode;
  }

  newNode->next=NULL;

  return newNode;
}

// function to dive the node repeatedly by 2 to get the appropriate memory size.
void divide_node(Node * dividing_node)
{

  int size_of_orignal=dividing_node->size;
  dividing_node->size=(size_of_orignal)/2;
  //Node *div_node=mmap(0, sizeof(struct Node), PROT_READ | PROT_WRITE,MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  Node *div_node=sbrk(sizeof(struct Node));
  div_node->size=(size_of_orignal)/2;
  div_node->free_flag=0;
  div_node->startAddr=dividing_node->startAddr+div_node->size;
  div_node->next=dividing_node->next;
  dividing_node->next=div_node;


}

// function to  merge nodes if they are buddies
void merge_buddy_node(int arena)
{

   Node * lowBud=Arena_Array[arena].head;
   Node * highBud=lowBud->next;

   while(highBud!=NULL)
   {
      if(findBuddies(lowBud,highBud)==0)
      {

        if(lowBud->free_flag==0&&highBud->free_flag==0)
        {

          Node *mergeBuds=lowBud;

          mergeBuds->size=lowBud->size+highBud->size;
          mergeBuds->memory_size=0;
          mergeBuds->free_flag=0;
          mergeBuds->next=highBud->next;

          lowBud=Arena_Array[0].head;
          highBud=lowBud->next;
          continue;

        }
      }
      lowBud=lowBud->next;
      highBud=highBud->next;
   }



}

// function to find an appropriate place for the size requested to go.
Node * search_where_to_put(int arena,size_t memsize)
{
    Node *temp=Arena_Array[arena].head;

    while(temp!=NULL)
    {
            if(temp->size>=memsize&&temp->free_flag==0)
      {

        return temp;
      }
      temp=temp->next;

    }
    return NULL;


}
// functionto find buddies
int findBuddies(Node * LowBuddy,Node * HighBuddy)
{
    int buddies=1;
    long long lowerBudAddr=LowBuddy->startAddr;



  if((LowBuddy->size==HighBuddy->size)&&(lowerBudAddr%(LowBuddy->size*2)==0)&&((LowBuddy->startAddr+LowBuddy->size)==HighBuddy->startAddr))
  {
    buddies=0;
  }

    return buddies;
}

// to check if a number is divisible by 2
int isPowerOfTwo(int n)
{
  if (n == 0)
    return 0;
  while (n != 1)
  {
      if (n%2 != 0)
         return 0;
      n = n/2;
  }
  return 1;
}
// function to ask Kernel for space.
Node  * call_for_space(int arena,int multiple)
{

//printf("CALL FOR SPACE  %d \n",pthread_self() );
 // pthread_mutex_lock(&mutex);
    void * strAddr=sbrk(multiple*getpagesize());//+(arena*1000*getpagesize());
  //void * strAddr=  mmap(0x5300000, multiple*getpagesize(), PROT_READ | PROT_WRITE,MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)+(arena*1000*getpagesize());
    if(strAddr==-1)
   {
     errno=ENOMEM;
     return NULL;
   }
    Node * mainNode=create_new_node(arena,multiple*getpagesize(),strAddr);
   // pthread_mutex_unlock(&mutex);
    return mainNode;

}
// function to find celing of a number
int ceil(float num) {

    int inum = num;
    if (num == (float)inum) {
        return inum;
    }
    return inum + 1;
}
