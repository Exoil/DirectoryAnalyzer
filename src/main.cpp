#include <iostream>
#include <typeinfo>
#include "FileAnalyzer.hpp"

using namespace Analyzer;

unsigned int static numberOfThreads = 1;

void PrintDirectories(std::vector<DirectoryInformation> *directories)
{
    std::cout << "Direcotries data:" << std::endl;

    for (DirectoryInformation &directory : *directories)
        std::cout << directory.ToString() << std::endl;
}

void PrintFiles(std::vector<FileInformation> *files)
{
    std::cout << "Files data:" << std::endl;

    for (FileInformation &file : *files)
        std::cout << file.ToString() << std::endl;
}

void PrintMenu()
{
    std::stringstream buffer;
    buffer << "1. Set number threads to use\n";
    buffer << "2. Analyze Folder\n";
    buffer << "Count machine threads: " << std::thread::hardware_concurrency() << "\n";
    buffer << "Current machine threads set use: " << numberOfThreads <<"\n";
    buffer << "Eneter any other character to exit\n";

    std::cout << buffer.str() << std::endl;
}

void SetNumberOfThreads()
{
    std::string numberOfThreadsCount = "";
    std::cout << "Set number of threads to use" << std::endl;
    std::cin >> numberOfThreadsCount;

    try
    {
        numberOfThreads = std::stoi(numberOfThreadsCount);
    }
    catch (const std::exception &e)
    {
        std::cout << "entered character isn't a number, setting to default threads number: 1 " << std::endl;
        numberOfThreads = 1;
    }
}

void AnalyzeDirectory(
    BaseFileInformation &currentDirectoryToAnalyze,
    BaseFileInformation &lastAnalyzedDirectory,
    std::vector<DirectoryInformation> &directoryResult,
    std::vector<FileInformation> &filesResult)
{
    std::string pathToDirectory = "";
    std::cout << "Enter path to directory" << std::endl;
    std::cin >> pathToDirectory;

    if (pathToDirectory.compare("") == 0 || !std::filesystem::exists(pathToDirectory) || !std::filesystem::is_directory(pathToDirectory))
    {
        std::cout << "Target path isn't directrory or not exists, return to menu" << std::endl;

        return;
    }

    FileAnalyzer fileAnalyzer;
    currentDirectoryToAnalyze = BaseFileInformation(std::filesystem::path(pathToDirectory));

    if (currentDirectoryToAnalyze.Equals(lastAnalyzedDirectory) && difftime(currentDirectoryToAnalyze.GetTime(), lastAnalyzedDirectory.GetTime()) == 0.0)
    {
        std::cout << "Is same directory and nothing changed last time" << std::endl;
        PrintDirectories(&directoryResult);
        PrintFiles(&filesResult);
        std::cout << std::endl;
        std::cout << "Is same directory and nothing changed last time" << std::endl;
        std::cout << "Directory count " << directoryResult.size() << std::endl;
        std::cout << "Files count " << filesResult.size() << std::endl;

        return;
    }

    auto start = std::chrono::steady_clock::now();

    try
    {
        fileAnalyzer.MultiThreadGetDirectoryContent(pathToDirectory, &directoryResult, &filesResult, numberOfThreads);
    }
    catch (std::invalid_argument exception)
    {
        std::cout << exception.what() << " back to menu";

        return;
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << "Directory count " << directoryResult.size() << std::endl;
    std::cout << "Files count " << filesResult.size() << std::endl;
    PrintDirectories(&directoryResult);
    PrintFiles(&filesResult);
    std::cout << std::endl;
    std::cout << "Time elapsed: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";
    std::cout << "Directory count " << directoryResult.size() << std::endl;
    std::cout << "Files count " << filesResult.size() << std::endl;

    lastAnalyzedDirectory = currentDirectoryToAnalyze;
}

int main()
{
    bool exitFlag = false;
    std::string chosedOption = "";
    int chosedOptionAsInt = -1;
    BaseFileInformation lastAnalyzedDirectory;
    BaseFileInformation currentAnalyzedDirectory;
    std::vector<DirectoryInformation> directories;
    std::vector<FileInformation> files;

    while (exitFlag != true)
    {
        PrintMenu();
        std::cin >> chosedOption;

        try
        {
            chosedOptionAsInt = std::stoi(chosedOption);
        }
        catch (const std::exception &e)
        {
            std::cout << "entered character is' not a number, exiting program" << std::endl;
            break;
        }

        switch (chosedOptionAsInt)
        {
        case 1:
            SetNumberOfThreads();
            break;
        case 2:
            AnalyzeDirectory(currentAnalyzedDirectory, lastAnalyzedDirectory, directories, files);
            break;
        default:
            exitFlag = true;
            break;
        }
    }

    std::cout << "end program" << std::endl;
}
