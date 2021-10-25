#include "FileAnalyzer.hpp"

using namespace Analyzer;

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

    if (threadNumber <= 1)
    {
        SingleThreadGetDirectoryContent(directoryPath, directoryContainer, fileContainer);

        return;
    }

    std::vector<std::filesystem::path> directoryContentPaths;
    std::filesystem::recursive_directory_iterator dirpos{directoryPath};
    std::copy(begin(dirpos), end(dirpos), std::back_inserter(directoryContentPaths));
    std::mutex lockMutex;

    auto addFileInromation = [directoryContainer, fileContainer, &directoryContentPaths, &lockMutex](int startIndex, int iteration)
    {
        for (int i = startIndex; i < directoryContentPaths.size(); i += iteration)
        {
            const std::lock_guard<std::mutex> lock(lockMutex);
            if (std::filesystem::is_directory(directoryContentPaths[i]))
                directoryContainer->push_back(DirectoryInformation(directoryContentPaths[i]));
            else
                fileContainer->push_back(FileInformation(directoryContentPaths[i]));
        }
    };

    std::vector<std::thread> threads;

    for (int i = 0; i < threadNumber; i++)
        threads.push_back(std::thread(addFileInromation, i, threadNumber));

    for (std::thread &thread : threads)
        thread.join();

    threads.clear();
}
