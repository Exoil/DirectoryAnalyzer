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
    BaseFileInformation lastAnalyzedDirectory;
    BaseFileInformation currentAnalyzedDirectory;

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
    std::vector<DirectoryInformation> directories;
    std::vector<FileInformation> files;

    for (int i = 0; i < 1; i++)
    {
        
        currentAnalyzedDirectory = BaseFileInformation(pathToDirectoryToAnalyze);    
        
        if (currentAnalyzedDirectory.Equals(lastAnalyzedDirectory) && difftime(currentAnalyzedDirectory.GetTime(), lastAnalyzedDirectory.GetTime()) == 0.0)
        {
            std::cout << "Is Same directory!" << std::endl;
            PrintDirectories(&directories);
            PrintFiles(&files);
            
        }

    else
    {
        directories.clear();
        files.clear();

        fileAnalyzer.MultiThreadGetDirectoryContent(pathToDirectoryToAnalyze, &directories, &files,4);

        PrintDirectories(&directories);
        PrintFiles(&files);
    }

    //lastAnalyzedDirectory = currentAnalyzedDirectory;
    }

    std::cout << "end program" << std::endl;
}
