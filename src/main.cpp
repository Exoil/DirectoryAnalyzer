#include <iostream>
#include <typeinfo>
#include "FileAnalyzer.hpp"

using namespace Analyzer;


void PrintDirectories(std::vector<DirectoryInformation> *directories)
{
    std::cout << "Directorys count: " << directories->size() << std::endl;
    std::cout << "Direcotries data:" << std::endl;

    for (DirectoryInformation &directory : *directories)
        std::cout << directory.ToString() << std::endl;
}

void PrintFiles(std::vector<FileInformation> *files)
{
    std::cout << "Files count: " << files->size() << std::endl;
    std::cout << "Files data:" << std::endl;

    for (FileInformation &file : *files)
        std::cout << file.ToString() << std::endl;
}

int main()
{    
    std::cout << "Analyze directory" << std::endl;
    std::string pathToDirectoryToAnalyze = "/Users/exoil/Documents/TestDirectory";

    if (!std::filesystem::exists(pathToDirectoryToAnalyze))
    {
        std::cout << "Target directory doesn't exists";

        return -1;
    }

    if (!std::filesystem::is_directory(pathToDirectoryToAnalyze))
    {
        std::cout << "Target file isn't directory";

        return -1;
    }

    FileAnalyzer fileAnalyzer;

    std::cout << "Machine thread count:" << fileAnalyzer.CountMachineThreads();

    std::vector<DirectoryInformation> directories;
    std::vector<FileInformation> files;

    fileAnalyzer.SingleThreadGetDirectoryContent(pathToDirectoryToAnalyze, &directories, &files);

    PrintDirectories(&directories);
    PrintFiles(&files);

    std::cout << "end program" << std::endl;
}
