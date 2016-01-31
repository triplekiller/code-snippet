/*
 * =====================================================================================
 *
 *       Filename:  malloc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/10/2015 04:28:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void *nonfree_malloc(size_t size)
{
	void *p = sbrk(0);
	void *request = sbrk(size);

	if (request == (void *)-1) {
		return NULL;
	} else {
		assert(p == request);
		return p;
	}
}

struct block_meta {
	size_t size;
	struct block_meta *next;
	int free;
	int magic;
};

#define META_SIZE sizeof(struct block_meta)
#define MAGIC_NUM 0x11235813

void *global_base = NULL;

struct block_meta *find_free_block(struct block_meta **last, size_t size)
{
	struct block_meta *pos = global_base;
	while (pos) {
		if (pos && !(pos->free && pos->size >=size)) {
			*last = pos;
			pos = pos->next;
		}
	}

	return pos;
}

struct block_meta *request_space(struct block_meta *last, size_t size)
{
	struct block_meta *block;
	block = sbrk(0);
	void *request = sbrk(size + META_SIZE);
	if (request == (void *)-1)
		return NULL;

	assert((void *)block == request);
	if (last)
		last->next = block;

	block->size = size;
	block->next = NULL;
	block->free = 0;
	block->magic = MAGIC_NUM;

	return block;
}

void *malloc(size_t size)
{
	struct block_meta *block;

	if (size <= 0)
		return NULL;

	if (!global_base) {
		block = request_space(NULL, size);
		if (!block)
			return NULL;

		global_base = block;
	} else {
		struct block_meta *last = global_base;
		block = find_free_block(&last, size);
		if (!block) {
			block = request_space(last, size);
			if (!block)
				return NULL;
		} else {
			block->free = 0;
		}
	}

	return (block + 1);
}

struct block_meta *get_block_ptr(void *ptr)
{
	return (struct block_meta *)ptr - 1;
}

void free(void *ptr)
{
	if (!ptr)
		return;

	struct block_meta *block_ptr = get_block_ptr(ptr);
	assert(block_ptr->free == 0);
	assert(block_ptr->magic == MAGIC_NUM);
	block_ptr->free = 1;
}

void *calloc(size_t nelem, size_t nsize)
{
	size_t size = nelem * nsize;
	void *ptr = malloc(size);
	memset(ptr, 0, size);
	return ptr;
}

void *realloc(void *ptr, size_t size)
{
	if (!ptr)
		return malloc(size);

	struct block_meta *block_ptr = get_block_ptr(ptr);
	if (block_ptr->size >= size)
		return ptr;

	void *new_ptr = malloc(size);
	if (!new_ptr)
		return NULL;

	memcpy(new_ptr, ptr, block_ptr->size);
	free(ptr);

	return new_ptr;
}
