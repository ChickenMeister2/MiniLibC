// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

#define ALIGNMENT 16
#define MIN_BLOCK_SIZE (sizeof(struct mem_list) + ALIGNMENT)
#define MAP_ANONYMOUS 0x20
void *malloc(size_t size)
{
    size_t alloc_size = size + sizeof(struct mem_list);
    struct mem_list *block = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block == MAP_FAILED) {
        return NULL;
    }

    block->start = (void*)block + sizeof(struct mem_list);
    block->len = size;

    if (mem_list_add(block->start, alloc_size) != 0) {
        munmap(block, alloc_size);
        return NULL;
    }

    return block->start;
}

void *calloc(size_t nmemb, size_t size)
{
    size_t total_size = nmemb * size;

    void *ptr = malloc(total_size);

    if (ptr != NULL) {
        memset(ptr, 0, total_size);
    }

    return ptr;
}

void free(void *ptr)
{
    if (ptr == NULL) {
        return;
    }

    struct mem_list *block = (struct mem_list *)((char *)ptr - sizeof(struct mem_list));

    int res = mem_list_del(block->start);

    if (res == 0)
        munmap(block, block->len + sizeof(struct mem_list));
}

void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL) {
        return malloc(size);
    }

    struct mem_list *block = mem_list_find(ptr);
    if (block == NULL) {
        return NULL;
    }

    if (block->len >= size) {
        return ptr;
    }

    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, block->len);

    free(ptr);

    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (nmemb >= ((size_t) -1) / size) {
        return NULL;
    }

    return realloc(ptr, nmemb * size);
}
