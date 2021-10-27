#include "FileAnalyzer.hpp"

using namespace Analyzer;

void FileAnalyzer::SingleThreadGetDirectoryContent(
    std::string pathToDirectory,
    std::vector<DirectoryInformation> *directoryContainer,
    std::vector<FileInformation> *fileContainer)
{
    if (pathToDirectory.compare("") == 0 || !std::filesystem::exists(pathToDirectory) || !std::filesystem::is_directory(pathToDirectory))
        throw std::invalid_argument("directoryPath is empty or  path does not point to a directory");
    if (directoryContainer == nullptr)
        throw std::invalid_argument("direcotryContainer is null pointer");
    if (fileContainer)
        throw std::invalid_argument("fileContainer is null pointer");

    directoryContainer->clear();
    fileContainer->clear();

    for (auto &rIt : std::filesystem::recursive_directory_iterator(pathToDirectory))
    {
        if (std::filesystem::is_directory(rIt.path()))
            directoryContainer->push_back(DirectoryInformation(rIt.path()));
        else
            fileContainer->push_back(FileInformation(rIt.path()));
    }
}

void FileAnalyzer::MultiThreadGetDirectoryContent(
    std::string pathToDirectory,
    std::vector<DirectoryInformation> *directoryContainer,
    std::vector<FileInformation> *fileContainer,
    unsigned int threadNumber)
{
    if (pathToDirectory.compare("") == 0 || !std::filesystem::exists(pathToDirectory) || !std::filesystem::is_directory(pathToDirectory))
        throw std::invalid_argument("directoryPath is empty or  path does not point to a directory");
    if (directoryContainer == nullptr)
        throw std::invalid_argument("direcotryContainer is null pointer");
    if (fileContainer)
        throw std::invalid_argument("fileContainer is null pointer");
    if (threadNumber == 0)
        throw std::invalid_argument("threadNumber is equal 0");

    directoryContainer->clear();
    fileContainer->clear();

    if (threadNumber = 1)
    {
        SingleThreadGetDirectoryContent(pathToDirectory, directoryContainer, fileContainer);

        return;
    }

    std::vector<std::filesystem::path> directoryContentPaths;
    std::filesystem::recursive_directory_iterator dirpos{pathToDirectory};
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
