struct mallinfo{

int arena;
int total_blocks;
int used_blocks;
int free_blocks;
int total_alloc_req;
int total_free_req;

};


void malloc_stats()
{

int i=0;
/*int free_blocks=0;
int total_blocks=0;
int used_blocks=0;*/
//printf("the number of arena is : %d ",NUM_ARENA);
for( i=0;i<NUM_ARENA;i++)
{

int free_blocks=0;
int total_blocks=0;
int used_blocks=0;

	Node* arena_pointer=Arena_Array[i].head;
		printf("\nARENA %d\n----------------------------------------\n",i);
		while(arena_pointer!=NULL)
		{
			total_blocks++;

			if(arena_pointer->free_flag==0)
			{
				free_blocks++;
			}
			if(arena_pointer->free_flag==1)
			{
				used_blocks++;
			}
			arena_pointer=arena_pointer->next;
		}

		printf("total number of blocks:		%d\n",total_blocks);
		printf("free blocks:          	        %d\n",free_blocks);
		printf("used blocks:                    %d\n",used_blocks);
		printf("total allocation request:       %llu\n",global_malloc_count[i]);
		printf("total free request:		%llu\n",global_free_count[i]);


}



}



struct mallinfo mallinfo()
{
	struct mallinfo info;
	int i=0;
int free_blocks=0;
int total_blocks=0;
int used_blocks=0;
printf("\n--------------MALLOC INFO--------------\n");
for( i=0;i<NUM_ARENA;i++)
{
	Node* arena_pointer=Arena_Array[i].head;
//		printf("\nARENA %d\n----------------------------------------\n",i);
		while(arena_pointer!=NULL)
		{
			total_blocks++;

			if(arena_pointer->free_flag==0)
			{
				free_blocks++;
			}
			if(arena_pointer->free_flag==1)
			{
				used_blocks++;
			}
			arena_pointer=arena_pointer->next;
		}


}
		info.arena=NUM_ARENA;
		info.total_blocks=total_blocks;
		info.used_blocks=used_blocks;
		info.free_blocks=free_blocks;
	int total_malloc_count=0;
	int total_free_count=0;
	int j=0;
	for(j=0;j<NUM_ARENA;j++)
	{
		total_malloc_count=total_malloc_count+global_malloc_count[j];
		total_free_count=total_free_count+global_free_count[j];
	}

		info.total_alloc_req=total_malloc_count;
		info.total_free_req=total_free_count;

		printf("total arena:		        %d\n",info.arena);
		printf("total blocks:                   %d\n",info.total_blocks);
		printf("free blocks:          	        %d\n",info.free_blocks);
		printf("used blocks:                    %d\n",info.used_blocks);
		printf("total allocation request:       %llu\n",info.total_alloc_req);
		printf("total free request:		%llu\n",info.total_free_req);





	return info;
}
