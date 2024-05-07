module;
#include <shlobj.h>

module buoy;

// https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
// FOLDERID_SavedGames

namespace {
struct deleter {
  void operator()(PWSTR *p) { CoTaskMemFree(*p); }
};
hai::holder<PWSTR, deleter> get_sg_folder() {
  hai::holder<PWSTR, deleter> res{};
  if (S_OK != SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_CREATE, nullptr,
                                   *res)) {
    return {};
  }
  return res;
}
} // namespace

mno::req<hai::uptr<yoyo::reader>> buoy::open_for_reading(jute::view) {
  return {};
}
mno::req<hai::uptr<yoyo::writer>> buoy::open_for_writing(jute::view) {
  return {};
}
