#pragma leco add_impl objc
module;
#include <sys/stat.h>

module buoy;
import traits;
import yoyo;

extern "C" void buoy_get_dir(char *);

mno::req<hai::uptr<yoyo::reader>> buoy::open_for_reading(jute::view folder,
                                                         jute::view file) {
  char buf[10240];
  buoy_get_dir(buf);

  auto dir = jute::view::unsafe(buf) + "/" + folder;
  mkdir(dir.cstr().begin(), 0777);

  auto fn = (dir + "/" + file).cstr();
  return yoyo::file_reader::open(fn.data())
      .map([](auto &&r) { return new yoyo::file_reader{traits::move(r)}; })
      .map([](auto *r) { return hai::uptr<yoyo::reader>{r}; });
}
mno::req<hai::uptr<yoyo::writer>> buoy::open_for_writing(jute::view folder,
                                                         jute::view file) {
  char buf[10240];
  buoy_get_dir(buf);

  auto dir = jute::view::unsafe(buf) + "/" + folder;
  mkdir(dir.cstr().begin(), 0777);

  auto fn = (dir + "/" + file).cstr();
  return yoyo::file_writer::open(fn.data())
      .map([](auto &&r) { return new yoyo::file_writer{traits::move(r)}; })
      .map([](auto *r) { return hai::uptr<yoyo::writer>{r}; });
}
