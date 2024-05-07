export module buoy;

import hai;
import jute;
import missingno;
import yoyo;

// https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
// FOLDERID_SavedGames

export namespace buoy {
mno::req<hai::uptr<yoyo::reader>> open_for_reading(jute::view);
mno::req<hai::uptr<yoyo::writer>> open_for_writing(jute::view);
} // namespace buoy

#if LECO_TARGET_WINDOWS
#pragma leco add_impl windows.cpp
#endif
