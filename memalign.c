
void *memalign(size_t alignment, size_t size)
{

  void * Addr;
  // malloc the total size
  Addr =(void *) malloc(size + alignment + sizeof(size_t));

  if(Addr==NULL)
      return NULL;

      int total_size=Addr+alignment+sizeof(void*);
      // find the compliment of the alignment and then use the logical and operator to find the return address.
      int compliment_alignment= ~(alignment-1);
      void **return_Addr = (void**)((uintptr_t)total_size & compliment_alignment);
         return_Addr[-1] = Addr;

         return return_Addr;

}
