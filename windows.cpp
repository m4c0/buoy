#include <direct.h>
#include <shlobj.h>
#include <stdio.h>

// https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
// FOLDERID_SavedGames

extern "C" void buoy_get_dir(char * buf, unsigned buf_sz) {
  PWSTR sg {};
  if (S_OK != SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_CREATE, nullptr, &sg)) {
    buf[0] = 0;
    return;
  }

  size_t count {};
  wcstombs_s(&count, buf, buf_sz, sg, buf_sz - 1);
  CoTaskMemFree(sg);
}
