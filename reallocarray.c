#define SIZE_MAX  65535
#define MUL_OVERFLOW (1UL << (sizeof(size_t) * 4))

void* reallocarray(void *ptr, size_t nmemb, size_t size)
{

   size_t new_size=size * nmemb;

// multiplication over flow check.
  if ((nmemb >= MUL_OVERFLOW || size >= MUL_OVERFLOW) && nmemb > 0 && SIZE_MAX / nmemb < size) {

                errno = ENOMEM;
                return NULL;
        }


        return realloc(ptr,new_size);
}
