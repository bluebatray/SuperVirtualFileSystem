#pragma once

#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "directory.hpp"

namespace virtualfilesystem
{

enum class ErrorCode
{
    Success,
    Fail
};
class FileSystem
{
   public:
    FileSystem();
    FileSystem(const std::string& serializedFileSystemPath);

    std::vector<Node> GetNodeList();
    ErrorCode MakeDir(const std::string& filex);
    ErrorCode CopyFile(const std::string& fileX, const std::string& fileY);

    // cp X Y - copy a file or a directory from path X to path Y
    /*mv X Y - move(or rename) a file or a directory from path X to path Y
        cd X - change the current working directory(or ..to go up a level)
        mkdir X - create a directorynamed X
        rm X - remove a file named X or an empty directory named X
        create X File Text - create a file named X with contents "File Text"
        cat X - print contents of a file named X
        ls - print files and directoriers in the current working directory
        stat X - prints metadata of a directory / file*/

   private:
    std::expected<std::shared_ptr<Directory>, ErrorCode> GetDirectory(const std::string& path);
    std::vector<std::string> Split(std::string s, const std::string& delimiter);
    long long GetCurrentEpoch();

    std::shared_ptr<Directory> root;
    std::shared_ptr<Directory> currentDirectory;

    const std::string root_symbol = ".";
    const std::string seperator_symbol = "/";
    const std::string parent_directory_symbol = "..";
};

}  // namespace virtualfilesystem