module;
#include <direct.h>
#include <shlobj.h>
#include <stdio.h>

module buoy;
import traits;

// https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
// FOLDERID_SavedGames

namespace {
struct deleter {
  void operator()(PWSTR p) { CoTaskMemFree(p); }
};
using pwstr = hai::value_holder<PWSTR, deleter>;

mno::req<pwstr> get_sg_folder() {
  pwstr res{};
  if (S_OK ==
      SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_CREATE, nullptr, &*res))
    return mno::req<pwstr>{traits::move(res)};

  return mno::req<pwstr>::failed("Could not find Saved Games folder");
}

mno::req<void> find_file(const pwstr &sgfld, jute::view folder,
                         jute::view file) {
  size_t count{};

  wchar_t wfld[MAX_PATH + 1];
  mbstowcs_s(&count, wfld, folder.size() + 1, folder.data(), _TRUNCATE);
  wfld[count + 1] = 0;

  wchar_t wfn[MAX_PATH + 1];
  mbstowcs_s(&count, wfn, file.size() + 1, file.data(), _TRUNCATE);
  wfn[count + 1] = 0;

  wchar_t buffer[MAX_PATH];
  wcscpy_s(buffer, MAX_PATH, *sgfld);
  wcscat_s(buffer, MAX_PATH, L"\\");
  wcscat_s(buffer, MAX_PATH, wfld);

  auto res = _wmkdir(buffer);
  if (res != 0 && errno != EEXIST) {
    return mno::req<void>::failed("Could not create folder in 'Saved Games'");
  }

  wcscat_s(buffer, MAX_PATH, L"\\");
  wcscat_s(buffer, MAX_PATH, wfn);

  _putws(buffer);
  //_wfopen_s(&f, name, L"rb");
  return {};
}
} // namespace

mno::req<hai::uptr<yoyo::reader>> buoy::open_for_reading(jute::view folder,
                                                         jute::view file) {
  return get_sg_folder()
      .fmap([&](auto &&sg) { return find_file(sg, folder, file); })
      .fmap([] { return mno::req<hai::uptr<yoyo::reader>>::failed("TBD"); });
}
mno::req<hai::uptr<yoyo::writer>> buoy::open_for_writing(jute::view folder,
                                                         jute::view file) {
  return get_sg_folder()
      .fmap([&](auto &&sg) { return find_file(sg, folder, file); })
      .fmap([] { return mno::req<hai::uptr<yoyo::writer>>::failed("TBD"); });
}
