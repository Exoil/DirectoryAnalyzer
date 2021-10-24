#include "FileAnalyzer.hpp"

using namespace Analyzer;

int FileAnalyzer::CountWordsInFile(FileInfo *file)
{
    if (file == nullptr)
        return -1;
    std::string fileContent = ReadFileIntoString(file->path.root_path());

    return 0;
}

int FileAnalyzer::CountCharactersInFile(FileInfo *file)
{
    if (file == nullptr)
        return -1;
    std::string fileContent = ReadFileIntoString(file->path.root_path());

    auto checkCharacter = [](char character)
    {
        int asciiValue = (int)character;

        if (asciiValue == 32)
            return true;
        return false;
    };

    fileContent.erase(std::remove(fileContent.begin(), fileContent.end(), checkCharacter ), fileContent.end());

    return 0;
}

std::string FileAnalyzer::ReadFileIntoString(const std::string &path)
{
    std::ifstream file(path);

    if (!file.is_open())
        return "";

    return std::string(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()));
}

void FileAnalyzer::AnaylzeDirectorySingleThread(FileInfo file)
{
    
}