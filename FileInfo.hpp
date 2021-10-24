#pragma once 
#include <filesystem>
#include <string>
#include <vector>

namespace Analyzer
{
    class FileInfo
    {
    public:
        std::filesystem::path path;
        bool isDirectory;
        std::vector<FileInfo> content;

        FileInfo(std::string pathToDirectory);
        FileInfo(std::filesystem::path pathToDirectory);

    private:
        void SetDirectoryContent();
    };
}