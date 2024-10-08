@import Foundation;

extern "C" void buoy_get_dir(char * buffer) {
  NSArray * arr = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
  NSString * dir = [arr firstObject];
  [[NSFileManager defaultManager] createDirectoryAtPath:dir
                            withIntermediateDirectories:YES
                                             attributes:nil
                                                  error:nil];
  strcpy(buffer, dir.UTF8String);
}
