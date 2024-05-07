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

using wcb = hai::array<wchar_t>;
mno::req<wcb> find_folder(const pwstr &sgfld, jute::view folder) {
  size_t count{};

  wchar_t wfld[MAX_PATH + 1];
  mbstowcs_s(&count, wfld, folder.size() + 1, folder.data(), _TRUNCATE);
  wfld[count + 1] = 0;

  wcb buffer{MAX_PATH};
  wcscpy_s(buffer.begin(), MAX_PATH, *sgfld);
  wcscat_s(buffer.begin(), MAX_PATH, L"\\");
  wcscat_s(buffer.begin(), MAX_PATH, wfld);
  return mno::req<wcb>{traits::move(buffer)};
}

mno::req<wcb> mkdir(wcb dir) {
  auto res = _wmkdir(dir.begin());
  if (res != 0 && errno != EEXIST) {
    return mno::req<wcb>::failed("Could not create folder in 'Saved Games'");
  }
  return mno::req<wcb>{traits::move(dir)};
}

mno::req<FILE *> find_file(wchar_t *buffer, jute::view file,
                           const wchar_t *mode) {
  size_t count{};

  wchar_t wfn[MAX_PATH + 1];
  mbstowcs_s(&count, wfn, file.size() + 1, file.data(), _TRUNCATE);
  wfn[count + 1] = 0;

  wcscat_s(buffer, MAX_PATH, L"\\");
  wcscat_s(buffer, MAX_PATH, wfn);

  FILE *f{};
  if (0 != _wfopen_s(&f, buffer, mode))
    return mno::req<FILE *>::failed("Could not open save file");

  return mno::req<FILE *>{f};
}
} // namespace

mno::req<hai::uptr<yoyo::reader>> buoy::open_for_reading(jute::view folder,
                                                         jute::view file) {
  return get_sg_folder()
      .fmap([&](auto &&sg) { return find_folder(sg, folder); })
      .fmap([&](auto &&dir) { return find_file(dir.begin(), file, L"rb"); })
      .map([](FILE *f) { return new yoyo::file_reader{f}; })
      .fmap([](auto *f) { return mno::req{hai::uptr<yoyo::reader>{f}}; });
}
mno::req<hai::uptr<yoyo::writer>> buoy::open_for_writing(jute::view folder,
                                                         jute::view file) {
  return get_sg_folder()
      .fmap([&](auto &&sg) { return find_folder(sg, folder); })
      .fmap([&](auto &&dir) { return mkdir(traits::move(dir)); })
      .fmap([&](auto &&dir) { return find_file(dir.begin(), file, L"wb"); })
      .map([](FILE *f) { return new yoyo::file_writer{f}; })
      .fmap([](auto *f) { return mno::req{hai::uptr<yoyo::writer>{f}}; });
}
