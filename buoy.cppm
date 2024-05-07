export module buoy;

import hai;
import jute;
import missingno;
import yoyo;

export namespace buoy {
mno::req<hai::uptr<yoyo::reader>> open_for_reading(jute::view folder,
                                                   jute::view file);
mno::req<hai::uptr<yoyo::writer>> open_for_writing(jute::view folder,
                                                   jute::view file);
} // namespace buoy

#if LECO_TARGET_WINDOWS
#pragma leco add_library Ole32 Shell32
#pragma leco add_impl windows.cpp
#endif
