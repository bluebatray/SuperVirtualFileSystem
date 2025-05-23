﻿#pragma once

#include <expected>
#include <memory>
#include <string>
#include <vector>

#include "directory.hpp"
#include "file.hpp"

namespace virtualfilesystem
{

enum class ErrorCodeType
{
    Success,
    AlreadyExists,
    NotFound,
    WrongType,
    Fail
};
struct ErrorCode
{
    ErrorCodeType type = ErrorCodeType::Fail;
    std::string extraData1;
    std::string extraData2;
};

class FileSystem
{
   public:
    FileSystem();
    FileSystem(const std::string& serializedFileSystemPath);

    std::vector<std::shared_ptr<Node>> GetNodeList() const;

    // std::vector<std::unique_ptr<Node>> GetNodeList();
    ErrorCode make_directory(const std::string& path);
    ErrorCode make_file(const std::string& filex, const std::string& fileText);
    ErrorCode copy_node(const std::string& originFullPath, const std::string& destinationFullPath);
    ErrorCode change_directory(const std::string& directoryName);
    ErrorCode get_file(const std::string& fullPathFile);

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
    std::shared_ptr<File> copy_file(std::shared_ptr<File> origin,
                                                std::weak_ptr<Directory> weakParent,
                                                const std::string& newName);
    std::shared_ptr<Directory> deep_copy_directory(std::shared_ptr<Directory> originDirectory);
    std::expected<std::shared_ptr<Directory>, ErrorCode> get_directory(const std::string& path);
    std::expected<std::pair<std::shared_ptr<Directory>, std::shared_ptr<Node>>, ErrorCode>
    get_node_with_path(const std::string& path);

    std::expected<std::pair<std::shared_ptr<Directory>, std::string>, ErrorCode>
                    get_node_name_with_path(const std::string& nodefullpath);
    //std::expected<std::shared_ptr<Node>, ErrorCode> get_node(const std::string& path);

    std::vector<std::string> split(std::string s, const std::string& delimiter);
    std::time_t get_current_epoch();

    std::shared_ptr<Directory> root;

    void calculate_full_path();
    std::vector<std::string> full_directory_structure;

    const std::string root_symbol = ".";
    const std::string root_symbol_display = "~";
    const std::string parent_directory_symbol = "..";
};

}  // namespace virtualfilesystem
