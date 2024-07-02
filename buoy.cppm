export module buoy;

import hai;
import jute;
import missingno;
import yoyo;

export namespace buoy {
mno::req<yoyo::file_reader> open_for_reading(jute::view folder,
                                             jute::view file);
mno::req<yoyo::file_writer> open_for_writing(jute::view folder,
                                             jute::view file);
} // namespace buoy

#if LECO_TARGET_WINDOWS
#pragma leco add_library Ole32 Shell32
#pragma leco add_impl windows.cpp
#elif LECO_TARGET_APPLE
#pragma leco add_impl apple.cpp
#elif LECO_TARGET_LINUX
#pragma leco add_impl linux.cpp
#endif
