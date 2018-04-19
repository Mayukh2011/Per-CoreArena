typedef struct Node{

  int size;
  int memory_size;
  int free_flag;
  void * startAddr;
  struct Node *next;
}Node;


#define MAX_ARENA 40
//#define NUM_ARENA 32
int NUM_ARENA;
unsigned long int global_malloc_count[MAX_ARENA]={0};
unsigned long int global_free_count[MAX_ARENA]={0};
static pthread_mutex_t arena_mutexes[MAX_ARENA];
int global_count=0;
//extern Node *head=NULL;
//extern void *struct_start_addr=NULL;
extern pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


Node* create_new_node(int,int,void *);
Node * search_where_to_put(int,size_t);
void divide_node(Node * );
int findBuddies(Node *,Node *);
void merge_buddy_node(int);
void traversal();
void * malloc(size_t );
Node  * call_for_space(int,int);
int ceil(float );
void free(void *);
void *calloc(size_t, size_t );
void *realloc(void *, size_t);
void *reallocarray(void *, size_t, size_t);
void *memalign(size_t, size_t);
int posix_memalign(void **, size_t, size_t);
int isPowerOfTwo(int );
