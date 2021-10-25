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

void FileAnalyzer::MultiThreadGetDirectoryContent(
    std::string directoryPath,
    std::vector<DirectoryInformation> *directoryContainer,
    std::vector<FileInformation> *fileContainer,
    int threadNumber)
{
    if (directoryContainer == nullptr || fileContainer == nullptr)
        return;

    if (threadNumber == 1)
    {
        SingleThreadGetDirectoryContent(directoryPath, directoryContainer, fileContainer);

        return;
    }

    auto getDirectory = [directoryContainer, fileContainer, directoryPath](int threadIndex)
    {
        std::vector<DirectoryInformation> directoriesTmp;
        std::vector<FileInformation> filesTmp;

        for (auto it = std::filesystem::recursive_directory_iterator(directoryPath); it != std::filesystem::recursive_directory_iterator(); it.operator++(threadIndex))
        {
            if (std::filesystem::is_directory(it->path()))
                directoriesTmp.push_back(DirectoryInformation(it->path()));
            else
                filesTmp.push_back(FileInformation(it->path()));
        }

        directoryContainer->insert(directoryContainer->end(), directoriesTmp.begin(), directoriesTmp.end());
        fileContainer->insert(fileContainer->end(), filesTmp.begin(), filesTmp.end());

        directoriesTmp.clear();
        filesTmp.clear();

        return;
    };

    std::vector<std::thread> threads;

    for (int i = 0; i < threadNumber; i++)
    {
        threads.push_back(std::thread(getDirectory, i + 1));
    }

    for (int i = 0; i < threadNumber; i++)
    {
        threads[i].join();
    }

    threads.clear();
}
