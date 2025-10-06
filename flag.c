#define NB_IMPLEMENTATION
#include "nb.h"
#include <assert.h>

typedef struct {
  char**    label;
  char**     desc;
  size_t    count;
  size_t capacity;
} nb_flags;

void nb_flag_append_impl(nb_flags *flags, char *label, char *desc){
  if (flags->capacity == 0){
    flags->capacity = 128;
    flags->label = malloc(sizeof(char*)*flags->capacity);
    flags->desc = malloc(sizeof(char*)*flags->capacity);
  } if (flags->count >= flags->capacity){
    flags->capacity *=2;
    flags->label = realloc(flags->label, sizeof(char*) * flags->capacity);
    flags->desc  = realloc(flags->desc, sizeof(char*) * flags->capacity); 
  }
  flags->label[flags->count] = strdup(label);
  flags->desc[flags->count] = strdup(desc);
  flags->count++;
}

size_t naive_index(nb_flags *flags, const char* value){
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

void nb_flag(nb_flags *flags, int argc, char** argv){
  if (flags->count > 0){
    if (argc < 2){
      for (size_t i=0; i<flags->count; ++i){
        if (!flags->desc[i]) flags->desc[i] = "no given desc"; // impossible case
        printf("-%s -> %s \n", flags->label[i], flags->desc[i]);
      }
    } else {
      // here add logic for parsing flags
      for (size_t i=0; i<argc; ++i){
        //printf("%zu\n", i);
        if (argv[i][0] == '-' && argv[i][1] != '-'){ // && argv[i][1] == '-'          //printf("found {-} in %s\n", argv[i]);
          memmove(argv[i], argv[i]+1, strlen(argv[i]));
          printf("found flag: %s\n", flags->label[naive_index(flags, argv[i])]);
          // in python it would be if flags->labels[argv[i]] != null
       }
       if (argv[i][0] == '-' && argv[i][1] == '-'){
         memmove(argv[i], argv[i]+2, strlen(argv[i]));
         printf("found flag: %s\n", flags->label[naive_index(flags, argv[i])]);
       }
      }     
    }
  }     
}

int main(int argc, char **argv){
  nb_flags flags = {0};
  nb_flag_append_impl(&flags, "help", "display other commands");
  nb_flag(&flags, argc, argv);
  //printf("%c\n", flags.label[0][0]);
}
