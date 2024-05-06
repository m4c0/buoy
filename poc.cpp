#pragma leco tool

import hai;
import jute;
import missingno;
import silog;
import yoyo;

namespace buoy {
mno::req<hai::uptr<yoyo::reader>> open_for_reading(jute::view);
mno::req<hai::uptr<yoyo::writer>> open_for_writing(jute::view);
} // namespace buoy

auto write() {
  return buoy::open_for_writing("test.txt").fmap([](auto &&r) {
    return r->write_u32(0xcafe);
  });
}
auto read() {
  return buoy::open_for_reading("test.txt")
      .fmap([](auto &&r) { return r->read_u32(); })
      .map([](auto u32) { silog::log(silog::info, "Got: %d", u32); });
}
int main() {
  write().fmap([] { return read(); }).take(silog::fail);
}
