#include <iostream>
#include "FileAnalyzer.hpp"

using namespace Analyzer;

int main()
{    
    std::cout << "Analyze directory" << std::endl;
    std::string pathToDirectoryToAnalyze = "/Users/exoil/Documents/TestDirectory";

    if (!std::filesystem::exists(pathToDirectoryToAnalyze))
        std::cout << "Target directory doesn't exists";

    FileInfo file(pathToDirectoryToAnalyze);
    FileAnalyzer fileAnalyzer;

    if (!file.isDirectory)
    {
        int countCharacters = fileAnalyzer.CountCharactersInFile(&file);
        int countWords = fileAnalyzer.CountWordsInFile(&file);
    }
    else
    {
        for (auto& file : file.content)
        {
        }
    }

    std::cout << "end" << std::endl;
}
