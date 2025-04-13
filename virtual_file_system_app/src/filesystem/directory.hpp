#pragma once

#include <vector>
#include <memory>
#include <map>

#include "node.hpp"

namespace virtualfilesystem {

	class File;

	class Directory : public Node {
	public:
		Directory(
			std::string _name, 
			long long _size, 
			long long _creationTime, 
			std::weak_ptr<Directory> _parentDirectory
		)
			: Node(std::move(_name), _size, _creationTime),
			parentDirectory(std::move(_parentDirectory)){
		}

		std::weak_ptr<Directory> parentDirectory;
		std::map<std::string, std::shared_ptr<Directory>> directoryMap;
		std::vector<std::shared_ptr<File>> fileList;
	};
}