#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

extern "C" void buoy_get_dir(char * buf, unsigned buf_sz);
  char * env = getenv("HOME");
  if (env == nullptr) {
    buf[0] = 0;
    return;
  }

  strncpy(buf, env, buf_sz);
  strncat(buf, "/.local", buf_sz - strlen(buf));
  mkdir(buf, 0777);
}
