#pragma once
#include "FileInformation.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <thread>


namespace Analyzer
{
    class FileAnalyzer
    {
    public:
        void SingleThreadGetDirectoryContent(
            std::string directoryPath,
            std::vector<DirectoryInformation> *directoryContainer,
            std::vector<FileInformation> *fileContainer);
        unsigned int CountMachineThreads();
    };
}