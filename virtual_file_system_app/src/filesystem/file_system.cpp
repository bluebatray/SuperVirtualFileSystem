#include "file_system.hpp"

#include <algorithm>
#include <chrono>

#include "../helper/container_helper.hpp"

namespace virtualfilesystem
{

FileSystem::FileSystem()
{
    root = std::make_shared<Directory>(root_symbol_display, 0LL, get_current_epoch(), std::weak_ptr<Directory>{});
    currentDirectory = root;
    full_directory_structure.push_back(root_symbol_display);

    calculate_full_path();
}

FileSystem::FileSystem(const std::string& serializedFileSystemPath)
{
    // todo
}

std::vector<std::shared_ptr<Node>> FileSystem::GetNodeList() const
{
    std::vector<std::shared_ptr<Node>> result;
    // currentDirectory->directoryMap.
    for (const auto& dir : currentDirectory->directoryList)
    {
        result.push_back(dir);  // upcast to Node
    }

    for (const auto& file : currentDirectory->fileList)
    {
        result.push_back(file);  // upcast to Node
    }

    return result;
}

// todo check and make sure dir isn't nested (just name)
ErrorCode FileSystem::make_directory(const std::string& dirName)
{
    // check if directory already exists
    auto dirResult = get_directory(dirName);

    // if we have a directory, then it's made already, error out
    if (dirResult)
    {
        return ErrorCode(ErrorCode::AlreadyExists);
    }
    std::shared_ptr<Directory> newDirectory = std::make_shared<Directory>(
        dirName, 0LL, get_current_epoch(), std::weak_ptr<Directory>(currentDirectory));

    currentDirectory->directoryMap.emplace(dirName, newDirectory);
    currentDirectory->directoryList.push_back(newDirectory);

    return ErrorCode(ErrorCode::Success);
}

ErrorCode FileSystem::make_file(const std::string& filex, const std::string& fileText)
{
    auto currentTime = get_current_epoch();

    std::shared_ptr<File> newFile =
        std::make_shared<File>(filex, fileText, fileText.length(), currentTime, currentDirectory);

    currentDirectory->fileList.push_back(newFile);
    currentDirectory->lastModifiedTime = currentTime;
    currentDirectory->size += newFile->size;

    return ErrorCode(ErrorCode::Success);
}

// std::pair<std::string, std::vector<std::string>> CommandManager::split_command(const std::string&
// line)

ErrorCode FileSystem::copy_file(const std::string& fileX, const std::string& fileY)
{
    // split directory and file so we can deal with them seperately

    // std::pair<std::string, std::vector<std::string>> CommandManager::split_command(const
    // std::string& line)
    //// get directory of first file
    // auto originResult = get_directory(fileX);
    // std::shared_ptr<Directory> dirOrigin = originResult? originResult.value() : currentDirectory;

    // check if fileX exists, if so get it

    // 2. check if directoryX exists
    // 3. if new file name is specified use it, otherwise use name of fileX
    // 4. copy file to new directory (with new name if specified)

    return ErrorCode(ErrorCode::Success);
}

ErrorCode FileSystem::change_directory(const std::string& directoryFullName)
{
    // split the directory up by seperator, step through each one and change to that directory
    // (chain)
    std::vector<std::string> directoryList =
        helper::split_string(directoryFullName, seperator_symbol);

    // if it's empty, there's no chaining going on, so just use the path given
    if (directoryList.empty())
    {
        directoryList.push_back(directoryFullName);
    }

    // in case there is an error, we can revert back to what we had before
    std::shared_ptr<Directory> oldCurrentDirectory = currentDirectory;

    for (std::string directoryName : directoryList)
    {
        if (directoryName == parent_directory_symbol)
        {
            if (auto parent = currentDirectory->parentDirectory.lock())
            {
                currentDirectory = parent;

                // check if we're deeper than root
                if (full_directory_structure.size() > 1)
                {
                    full_directory_structure.pop_back();
                }
            }
        }
        else if (directoryName == root_symbol)
        {
            full_directory_structure.erase(full_directory_structure.begin() + 1,
                                           full_directory_structure.end());
            currentDirectory = root;
        }
        else
        {
            // split the path
            bool found = false;

            // actual directory, check current directory lists
            for (std::shared_ptr<Directory> directory : currentDirectory->directoryList)
            {
                if (directory->name == directoryName)
                {
                    full_directory_structure.push_back(directory->name);
                    currentDirectory = directory;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                currentDirectory = oldCurrentDirectory;
                return ErrorCode(ErrorCode::NotFound);
            }
        }
    }

    calculate_full_path();

    return ErrorCode(ErrorCode::Success);
}

std::expected<std::shared_ptr<Directory>, ErrorCode> FileSystem::get_directory(
    const std::string& path)
{
    std::vector<std::string> directoryHierarchy = split(path, seperator_symbol);

    if (directoryHierarchy.size() == 0)
        return std::unexpected(ErrorCode::Fail);

    std::shared_ptr<Directory> tempCurrentDirectory = currentDirectory;

    // loop through only folders
    for (size_t i = 0; i < directoryHierarchy.size(); i++)
    {
        const std::string& nodeName = directoryHierarchy[i];

        if (nodeName == parent_directory_symbol)
        {
            if (auto parent = tempCurrentDirectory->parentDirectory.lock())
            {
                tempCurrentDirectory = parent;
            }
            else
            {
                // at root already, discard
            }
        }
        else if (nodeName == root_symbol)
        {
            tempCurrentDirectory = root;
        }
        else
        {
            if (tempCurrentDirectory->directoryMap.contains(nodeName))
            {
                tempCurrentDirectory = tempCurrentDirectory->directoryMap[nodeName];
            }
            else
            {
                return std::unexpected(ErrorCode::Fail);  // folder doesn't exist
            }
        }
    }

    return tempCurrentDirectory;
}

std::expected<std::pair<std::shared_ptr<Directory>, std::shared_ptr<File>>, ErrorCode>
FileSystem::split_file_path(const std::string& path)
{
    std::vector<std::string> directoryHierarchy = split(path, seperator_symbol);

    std::shared_ptr<Directory> tempCurrentDirectory = currentDirectory;

    // if we have to dig into subdirectories, do it and get the directory
    if (directoryHierarchy.size() > 0)
    {
        // last one is filename, so skip the directory checks
        for (size_t i = 0; i < directoryHierarchy.size() - 1; i++)
        {
            const std::string& nodeName = directoryHierarchy[i];

            if (nodeName == parent_directory_symbol)
            {
                if (auto parent = tempCurrentDirectory->parentDirectory.lock())
                {
                    tempCurrentDirectory = parent;
                }
                else
                {
                    // at root already, discard
                }
            }
            else if (nodeName == root_symbol)
            {
                tempCurrentDirectory = root;
            }
            else
            {
                if (tempCurrentDirectory->directoryMap.contains(nodeName))
                {
                    tempCurrentDirectory = tempCurrentDirectory->directoryMap[nodeName];
                }
                else
                {
                    return std::unexpected(ErrorCode::Fail);  // folder doesn't exist
                }
            }
        }
    }

    // we have folder, now let's get the file
    // tempCurrentDirectory->fileList.con

    std::shared_ptr<File> tempFindFile = nullptr;

    // return tempCurrentDirectory;
    return {std::make_pair(tempCurrentDirectory, tempFindFile)};

    // return std::expected<std::pair<std::shared_ptr<Directory>, std::shared_ptr<File>>,
    // ErrorCode>();
}

// std::expected<std::shared_ptr<File>, ErrorCode> FileSystem::get_file(
//     const std::string& path, std::shared_ptr<Directory> directory)
//{
//     if (directory == nullptr)
//         directory = currentDirectory;
//
//
//     return std::expected<std::shared_ptr<File>, ErrorCode>();
// }

std::vector<std::string> FileSystem::split(std::string s, const std::string& delimiter)
{
    std::vector<std::string> splitStringVector;
    size_t pos = 0;
    while (pos < s.size())
    {
        pos = s.find(delimiter);
        std::string temp = s.substr(0, pos);

        // check if there's spaces, if so ignore
        if (!temp.empty() && !std::all_of(temp.begin(), temp.end(), isspace))
        {
            splitStringVector.push_back(temp);
        }

        s.erase(0, pos + delimiter.length());
    }
    return splitStringVector;
}
long long FileSystem::get_current_epoch()
{
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

void FileSystem::calculate_full_path()
{
    current_full_path = helper::join(full_directory_structure.begin(),
                                     full_directory_structure.end(), seperator_symbol.c_str());
}
}  // namespace virtualfilesystem
