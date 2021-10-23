#include "FileInfo.hpp"

using namespace Analyzer;

FileInfo::FileInfo(std::string pathToDirectory) : path(pathToDirectory)
{
    isDirectory = std::filesystem::is_directory(pathToDirectory);
    SetDirectoryContent();
}

FileInfo::FileInfo(std::filesystem::path pathToDirectory) : path(pathToDirectory)
{
    isDirectory = std::filesystem::is_directory(pathToDirectory);
    SetDirectoryContent();
}

void FileInfo::SetDirectoryContent()
{
    content.clear();

    if (!isDirectory)
        return;

    for (auto it = std::filesystem::directory_iterator(path); it != std::filesystem::directory_iterator(); ++it)
        content.push_back(FileInfo(it->path()));
}
