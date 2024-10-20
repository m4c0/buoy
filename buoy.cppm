export module buoy;

import hai;
import jute;

export namespace buoy {
  extern hai::fn<void, const char *> on_failure;
  void read(jute::view folder, jute::view file, hai::fn<void, hai::array<char> &>);
  void write(jute::view folder, jute::view file, jute::heap data);
} // namespace buoy

#if LECO_TARGET_WINDOWS
#pragma leco add_library Ole32 Shell32
#pragma leco add_impl windows.cpp
#elif LECO_TARGET_APPLE
#pragma leco add_impl posix objc
#elif LECO_TARGET_LINUX
#pragma leco add_impl posix linux
#endif

module :private;
hai::fn<void, const char *> buoy::on_failure {};
