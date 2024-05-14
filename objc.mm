@import Foundation;

extern "C" void buoy_get_dir(char *buffer) {
  NSString *dir = [NSSearchPathForDirectoriesInDomains(
      NSApplicationSupportDirectory, NSUserDomainMask, YES) firstObject];
  strcpy(buffer, dir.UTF8String);
}
