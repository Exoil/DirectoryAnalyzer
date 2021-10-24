#include "FileAnalyzer.hpp"

using namespace Analyzer;

unsigned int FileAnalyzer::CountMachineThreads()
{
    return std::thread::hardware_concurrency();
}

void FileAnalyzer::SingleThreadGetDirectoryContent(
    std::string directoryPath,
    std::vector<DirectoryInformation> *directoryContainer,
    std::vector<FileInformation> *fileContainer)
{
    if (directoryContainer == nullptr 
        || fileContainer == nullptr)
        return;

        for (auto &rIt : std::filesystem::recursive_directory_iterator(directoryPath))
        {
            if (std::filesystem::is_directory(rIt.path()))
                directoryContainer->push_back(DirectoryInformation(rIt.path()));
            else
                fileContainer->push_back(FileInformation(rIt.path()));
        }
}