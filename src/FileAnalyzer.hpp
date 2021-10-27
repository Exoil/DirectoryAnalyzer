#pragma once
#include "FileInformation.hpp"
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>
#include <execution>

namespace Analyzer
{
    class FileAnalyzer
    {
    public:
        void SingleThreadGetDirectoryContent(
            std::string pathToDirectory,
            std::vector<DirectoryInformation> *directoryContainer,
            std::vector<FileInformation> *fileContainer);
        void MultiThreadGetDirectoryContent(
            std::string pathToDirectory,
            std::vector<DirectoryInformation> *directoryContainer,
            std::vector<FileInformation> *fileContainer,
            unsigned int threadNumber);
    };
}
