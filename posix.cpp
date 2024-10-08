module;
#include <sys/stat.h>

module buoy;
import traits;
import yoyo;

extern "C" void buoy_get_dir(char *);

static auto filename(jute::view folder, jute::view file) {
  char buf[10240];
  buoy_get_dir(buf);

  auto dir = jute::view::unsafe(buf) + "/" + folder;
  mkdir(dir.cstr().begin(), 0777);

  return (dir + "/" + file).cstr();
}

mno::req<yoyo::file_reader> buoy::open_for_reading(jute::view folder,
                                                   jute::view file) {
  auto fn = filename(folder, file);
  return yoyo::file_reader::open(fn.data());
}
mno::req<yoyo::file_writer> buoy::open_for_writing(jute::view folder,
                                                   jute::view file) {
  auto fn = filename(folder, file);
  return yoyo::file_writer::open(fn.data());
}
