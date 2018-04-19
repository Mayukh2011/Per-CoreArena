

void *calloc(size_t nmemb, size_t size)
{

  // if total size is 0 the return NULL.
  size_t total = nmemb * size;
  if(total==0)
  {

  	return NULL;
  }
//  printf("INSIDE CALLLOC\n" );
  // reserve space using malloc.
	void *p = malloc(total);

	if (!p) return NULL;
// call memset to initialize it to 0.
	p = memset(p, 0, total);


	return p;

}
