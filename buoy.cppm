module;
#define MCT_SYSCALL_IMPLEMENTATION
#include "../mct/mct-syscall.h"

extern "C" void buoy_get_dir(char * buf, unsigned buf_sz);

export module buoy;

import hai;
import jute;

#if LECO_TARGET_WINDOWS
#define SEP "\\"
#else
#define SEP "/"
#endif

export namespace buoy {
  hai::cstr path(jute::view folder, jute::view file) {
    char buf[10240];
    buoy_get_dir(buf, sizeof(buf));
    auto dir = jute::view::unsafe(buf) + SEP + folder;
    mct_syscall_mkdir(dir.cstr().begin());
    return (dir + SEP + file).cstr();
  }
} // namespace buoy

#if LECO_TARGET_WINDOWS
#pragma leco add_library Ole32 Shell32
#pragma leco add_impl windows
#elif LECO_TARGET_APPLE
#pragma leco add_impl objc
#elif LECO_TARGET_LINUX
#pragma leco add_impl linux
#endif
