module;
#include <sys/stat.h>

module buoy;
import traits;
import jojo;

extern "C" void buoy_get_dir(char *);

static auto filename(jute::view folder, jute::view file) {
  char buf[10240];
  buoy_get_dir(buf);

  auto dir = jute::view::unsafe(buf) + "/" + folder;
  mkdir(dir.cstr().begin(), 0777);

  return (dir + "/" + file).cstr();
}

void buoy::read(jute::view folder, jute::view file, hai::fn<void, hai::array<char> &> callback) {
  auto fn = filename(folder, file);
  // TODO: handle errors
  jojo::read(fn, nullptr, [&](auto *, hai::array<char> & data) { callback(data); });
}
void buoy::write(jute::view folder, jute::view file, jute::heap data) {
  auto fn = filename(folder, file);
  // TODO: handle errors
  jojo::write(fn, nullptr, data, [&](auto *) {});
}
