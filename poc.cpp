#pragma leco tool

import buoy;
import jute;
import silog;

using namespace jute::literals;

int main() {
  buoy::on_failure = [] (auto msg) {
    silog::log(silog::error, "failed: %s (might be expected for first run)", msg);
  };

  buoy::read("poc", "test2.txt", [](auto & data) {
    silog::trace("had", jute::view { data.begin(), data.size() });
  });

  buoy::write("poc", "test2.txt", "my test works"_hs);
}
