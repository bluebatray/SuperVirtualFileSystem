#pragma once

#ifdef _WIN32
#ifdef VIRTUALFILESYSTEMLIB_EXPORTS
#define VIRTUALFILESYSTEMLIB_API __declspec(dllexport)
#else
#define VIRTUALFILESYSTEMLIB_API __declspec(dllimport)
#endif
#else
#define VIRTUALFILESYSTEMLIB_API
#endif

#include <string>

class VIRTUALFILESYSTEMLIB_API VirtualFileSystem {
public:
  VirtualFileSystem();
  ~VirtualFileSystem();

  void PrintFileSystemInfo();
};
