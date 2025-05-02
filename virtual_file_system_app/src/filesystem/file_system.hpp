#pragma once

#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "directory.hpp"
#include "file.hpp"

namespace virtualfilesystem
{

enum class ErrorCode
{
    Success,
    AlreadyExists,
    NotFound,
    Fail
};
class FileSystem
{
   public:
    FileSystem();
    FileSystem(const std::string& serializedFileSystemPath);

    std::vector<std::shared_ptr<Node>> GetNodeList() const;

    //std::vector<std::unique_ptr<Node>> GetNodeList();
    ErrorCode make_directory(const std::string& filex);
    ErrorCode make_file(const std::string& filex, const std::string& fileText);
    ErrorCode copy_file(const std::string& fileX, const std::string& fileY);
    ErrorCode change_directory(const std::string& directoryName);

    // cp X Y - copy a file or a directory from path X to path Y
    /*mv X Y - move(or rename) a file or a directory from path X to path Y
        ✓ cd X - change the current working directory(or ..to go up a level)
        ✓ mkdir X - create a directorynamed X
        rm X - remove a file named X or an empty directory named X
        ✓ create X File Text - create a file named X with contents "File Text"
        cat X - print contents of a file named X
        ✓ ls - print files and directoriers in the current working directory
        stat X - prints metadata of a directory / file*/
    std::shared_ptr<Directory> currentDirectory;

    const std::string seperator_symbol = "/";
    std::string current_full_path;

   private:
    std::expected<std::shared_ptr<Directory>, ErrorCode> get_directory(const std::string& path);
    std::expected<std::pair<std::shared_ptr<Directory>, std::shared_ptr<File>>, ErrorCode>
    split_file_path(const std::string& path);

    std::vector<std::string> split(std::string s, const std::string& delimiter);
    long long get_current_epoch();

    std::shared_ptr<Directory> root;
    
    void calculate_full_path();
    std::vector<std::string> full_directory_structure;

    const std::string root_symbol = ".";
    const std::string root_symbol_display = "~";
    const std::string parent_directory_symbol = "..";        

};

}  // namespace virtualfilesystem