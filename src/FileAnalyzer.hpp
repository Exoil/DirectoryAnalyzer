#pragma once
#include "FileInformation.hpp"
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>
#include <execution>
#include <list>

namespace Analyzer
{
    class FileAnalyzer
    {
    public:
        void SingleThreadGetDirectoryContent(
            std::string pathToDirectory,
            std::list<DirectoryInformation> *directoryContainer,
            std::list<FileInformation> *fileContainer);
        void MultiThreadGetDirectoryContent(
            std::string pathToDirectory,
            std::list<DirectoryInformation> *directoryContainer,
            std::list<FileInformation> *fileContainer,
            unsigned int threadNumber);
    };
}
