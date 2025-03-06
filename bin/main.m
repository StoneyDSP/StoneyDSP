#include "main.h"

#include <Foundation/Foundation.h>

int main(int argc, char *argv[]) {
  @autoreleasepool {
    NSLog(@"Objective-C or Objective-C++ code is being compiled.");
    NSString *greeting = [NSString stringWithFormat:@"Hello, %@", @"World!"];
    NSLog(@"%@", greeting);
  }
  return EXIT_SUCCESS;
}
