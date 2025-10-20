#define FG_IMPLEMENTATION
#include "../flag.h"

void helpf(){
  printf("help func ptr works!\n");
}

int main(int argc, char** argv){
  fg_flags flags = {0};
  fg_append_ptr(&flags, "help", helpf);
  fg_append(&flags, "run", "runs file");
  fg_append(&flags, "rm", "removes file");
  fg_run(&flags, argc, argv);

  return 0;
}
