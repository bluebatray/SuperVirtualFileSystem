#include <iostream>

#include "virtual_file_system.hpp"

VirtualFileSystem::VirtualFileSystem() {
  std::cout << "VirtualFileSystem initialized!" << std::endl;
}

VirtualFileSystem::~VirtualFileSystem() {
  std::cout << "VirtualFileSystem destroyed!" << std::endl;
}

void VirtualFileSystem::PrintFileSystemInfo() {
  std::cout << "File system information retrieved successfully!" << std::endl;
}
