module;
#include <direct.h>
#include <shlobj.h>
#include <stdio.h>

module buoy;
import jojo;
import traits;

// https://learn.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
// FOLDERID_SavedGames

namespace {
struct deleter {
  void operator()(PWSTR p) { CoTaskMemFree(p); }
};
using pwstr = hai::value_holder<PWSTR, deleter>;

void to_wide(wchar_t * wide, jute::view str) {
  size_t count{};
  mbstowcs_s(&count, wide, str.size() + 1, str.data(), _TRUNCATE);
  wide[count + 1] = 0;
}

static bool get_fn(jute::view folder, jute::view file, char * out) {
  pwstr sg {};
  if (S_OK != SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_CREATE, nullptr, &*sg)) {
    buoy::on_failure("Could not find Saved Games folder");
    return false;
  }

  wchar_t wfld[MAX_PATH + 1] {};
  to_wide(wfld, folder);
  wchar_t wfn[MAX_PATH + 1] {};
  to_wide(wfn, file);

  wchar_t buffer[MAX_PATH] {};
  wcscpy_s(buffer, MAX_PATH, *sg);
  wcscat_s(buffer, MAX_PATH, L"\\");
  wcscat_s(buffer, MAX_PATH, wfld);
  if (_wmkdir(buffer) != 0 && errno != EEXIST) {
    buoy::on_failure("Could not create folder in 'Saved Games'");
    return false;
  }

  wcscat_s(buffer, MAX_PATH, L"\\");
  wcscat_s(buffer, MAX_PATH, wfn);

  size_t count {};
  wcstombs_s(&count, out, MAX_PATH, buffer, MAX_PATH);
  out[count + 1] = 0;
  return true;
}
} // namespace

void buoy::read(jute::view folder, jute::view file, hai::fn<void, hai::array<char> &> callback) {
  char fn[MAX_PATH + 1] {};
  if (!get_fn(folder, file, fn)) return;

  // TODO: handle errors
  jojo::read(fn, nullptr, [&](auto *, hai::array<char> & data) { callback(data); });
}
void buoy::write(jute::view folder, jute::view file, jute::heap data) {
  char fn[MAX_PATH + 1] {};
  if (!get_fn(folder, file, fn)) return;

  // TODO: handle errors
  jojo::write(fn, nullptr, data, [&](auto *) {});
}
