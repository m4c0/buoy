module;
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

module buoy;
import silog;

extern "C" void buoy_get_dir(char * buf) {
  char * env = getenv("HOME");
  if (env == nullptr)
    silog::fail("Could not find $HOME");

  strcpy(buf, env);
  strcat(buf, "/.local");
  mkdir(buf, 0777);
  strcat(buf, "/m4c0");
  mkdir(buf, 0777);
}
