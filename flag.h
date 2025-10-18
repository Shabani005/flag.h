#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

typedef struct {
  char**    label;
  char**    desc;
  int       (*func_ptr)();
  size_t    count;
  size_t    capacity;
} fg_flags;

#define fg_index fg_naive_index

void   fg_append(fg_flags *flags, char *label, char *desc);
size_t fg_naive_index(fg_flags *flags, const char* value);
void   fg_run(fg_flags *flags, int argc, char** argv);
void   fg_append_ptr(fg_flags *flags, char *label, void (*func)(void));

#ifdef FG_IMPLEMENTATION
void fg_append(fg_flags *flags, char *label, char *desc){
  if (flags->capacity == 0){
    flags->capacity = 128;
    flags->label = (char**)malloc(sizeof(char*)*flags->capacity);
    flags->desc =  (char**)malloc(sizeof(char*)*flags->capacity);
  } if (flags->count >= flags->capacity){
    flags->capacity *=2;
    flags->label = (char**)realloc(flags->label, sizeof(char*) * flags->capacity);
    flags->desc  = (char**)realloc(flags->desc, sizeof(char*) * flags->capacity); 
  }
  flags->label[flags->count] = strdup(label);
  flags->desc[flags->count] = strdup(desc);
  flags->count++;
}

void fg_append_ptr(fg_flags *flags, char *label, void(*func)(void)){
  if (flags->capacity == 0){
    flags->capacity = 128;
    flags->label = (char**)malloc(sizeof(char*)*flags->capacity);
    flags->desc =  (char**)malloc(sizeof(char*)*flags->capacity);
  } if (flags->count >= flags->capacity){
    flags->capacity *=2;
    flags->label = (char**)realloc(flags->label, sizeof(char*) * flags->capacity);
    flags->desc  = (char**)realloc(flags->desc, sizeof(char*) * flags->capacity); 
  }
  flags->label[flags->count] = strdup(label);
  flags->desc[flags->count] = "\0";
  // TODO: remove desc null terminator and fix in terms on fg_run to not print \n
  //flags->func_ptr = func;
  func();
  flags->count++;
}


size_t naive_index(fg_flags *flags, const char* value){
  bool found;
  for(size_t i=0; i<flags->count; ++i){
    if (strcmp(flags->label[i], value) == 0){
      return i;
      found = true;
    }
  }
  assert(found);
  return -1;
}

void fg_run(fg_flags *flags, int argc, char** argv){
  if (flags->count > 0){
    if (argc < 2){
      printf("All commands:\n");
      for (size_t i=0; i<flags->count; ++i){
        if (!flags->desc[i]) flags->desc[i] = "no given desc"; // impossible case
          printf("    --%s, -%s  %s\n", flags->label[i], flags->label[i], flags->desc[i]); //use strlen comp to align by longest string
      }
    } else {
      // here add logic for parsing flags
      for (size_t i=0; i<argc; ++i){
        //printf("%zu\n", i);
        if (argv[i][0] == '-' && argv[i][1] != '-'){ // && argv[i][1] == '-'          //printf("found {-} in %s\n", argv[i]);
          memmove(argv[i], argv[i]+1, strlen(argv[i]));
          printf("%s\n", flags->desc[naive_index(flags, argv[i])]);
          // in python it would be if flags->labels[argv[i]] != null
       }
       if (argv[i][0] == '-' && argv[i][1] == '-'){
         memmove(argv[i], argv[i]+2, strlen(argv[i]));
         printf("%s\n", flags->desc[naive_index(flags, argv[i])]);
       }
      }     
    }
  }     
}
#endif


