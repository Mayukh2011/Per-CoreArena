int posix_memalign(void **memptr, size_t alignment, size_t size){
   // if size is 0 then set memptr to NULL.
        if(size==0)
        {
            memptr=NULL;
            return 0;
        }
        // if the alignment is not a power of 2 or alignment is not divisible by the size of void * the return errono.
      if(!(isPowerOfTwo(alignment)&&((alignment%sizeof(void *))==0)))
      {
          errno=EINVAL;
          return errno;
      }

      // use memalign to get the proper alignment.
      void * mem_value=memalign(alignment,size);
      memptr=&mem_value;

      return 0;

}
