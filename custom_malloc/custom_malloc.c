#include <stdio.h>
#include <string.h>
#include <unistd.h>  //need linux

typedef struct Block {
  size_t size;
  int free;
  struct Block* next;
} Block;

#define BLOCK_SIZE sizeof(Block)

Block* head = NULL;

Block* find_free_block(size_t size) {
  Block* current = head;
  while (current) {
    if (current->free && current->size >= size) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

Block* request_space(size_t size) {
  void* request = sbrk(size + BLOCK_SIZE);
  if (request == (void*)-1) return NULL;

  Block* block = (Block*)request;
  block->size = size;
  block->free = 0;
  block->next = NULL;

  if (!head) {
    head = block;
  } else {
    Block* last = head;
    while (last->next) last = last->next;
    last->next = block;
  }

  return block;
}

void* my_malloc(size_t size) {
  if (size == 0) return NULL;

  Block* block = find_free_block(size);
  if (block) {
    block->free = 0;
    return (void*)(block + 1);
  }

  block = request_space(size);
  if (!block) return NULL;

  return (void*)(block + 1);
}

void my_free(void* ptr) {
  if (!ptr) return;
  Block* block = (Block*)ptr - 1;
  block->free = 1;
}

void* my_realloc(void* ptr, size_t new_size) {
  if (!ptr) return my_malloc(new_size);
  if (new_size == 0) {
    my_free(ptr);
    return NULL;
  }

  Block* block = (Block*)ptr - 1;

  if (block->size >= new_size) {
    return ptr;
  }

  void* new_ptr = my_malloc(new_size);
  if (!new_ptr) return NULL;

  memcpy(new_ptr, ptr, block->size);
  my_free(ptr);
  return new_ptr;
}

void print_blocks() {
  Block* current = head;
  printf("Memory blocks:\n");
  while (current) {
    printf("  Address: %p, Size: %zu, Free: %d\n", (void*)(current + 1),
           current->size, current->free);
    current = current->next;
  }
  printf("\n");
}

int main() {
  printf("Allocating 10 bytes...\n");
  char* a = (char*)my_malloc(10);
  strcpy(a, "Hello");

  printf("Allocating 20 bytes...\n");
  char* b = (char*)my_malloc(20);
  strcpy(b, "World!");

  print_blocks();

  printf("Freeing a\n");
  my_free(a);

  print_blocks();

  printf("Reallocating b to 40 bytes\n");
  b = (char*)my_realloc(b, 40);
  strcat(b, "!!!");

  print_blocks();

  printf("b = %s\n", b);

  my_free(b);

  print_blocks();

  return 0;
}
