#define FG_IMPLEMENTATION
#include "../flag.h"

int main(int argc, char** argv){
  fg_flags flags = {0};
  fg_append(&flags, "help", "look at the other commands!");
  fg_append(&flags, "run", "runs file");
  fg_append(&flags, "rm", "removes file");
  fg_run(&flags, argc, argv);

  return 0;
}
