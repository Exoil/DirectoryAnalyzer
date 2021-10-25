#include "FileInformation.hpp"

using namespace Analyzer;

FileInformation::FileInformation(std::filesystem::path pathToFile)
    : BaseFileInformation(pathToFile)
{
    SetInformation();
}

void FileInformation::SetInformation()
{
    BaseFileInformation::SetInformation();
    extension = path.extension();
    size = std::filesystem::file_size(path);
    std::string fileContent = ReadFile();
    SetCountWords(fileContent);
    SetCountCharacters(fileContent);
}

std::string FileInformation::ReadFile()
{
    std::string fileContent = "";
    std::fstream fileToRead(path);

    if (!fileToRead.is_open())
        return fileContent;

    fileContent.assign((std::istreambuf_iterator<char>(fileToRead)),
                       (std::istreambuf_iterator<char>()));

    return fileContent;
}

void FileInformation::SetCountWords(std::string fileContent)
{
    countWords = 0;
    std::vector<std::string> splitedStirng;
    std::istringstream iss(fileContent);
    std::string word;

    while(std::getline(iss, word, ' '))
        splitedStirng.push_back(word);

    countWords = splitedStirng.size();
    splitedStirng.clear();
    iss.clear();
}

void FileInformation::SetCountCharacters(std::string fileContent)
{
    countCharacters = 0;
    std::erase(fileContent, ' ');
    std::erase(fileContent, '\n');

    countCharacters = fileContent.size();
}

std::string FileInformation::ToString()
{
    std::stringstream buffer;
    buffer << "FileType: File ";
    buffer << BaseFileInformation::ToString() << " ";
    buffer << "size: " << size << " ";
    buffer << "extension: " << extension << " ";
    buffer << "Word count: " << countWords << " ";
    buffer << "Character count: " << countCharacters << " ";
    std::string outputString = buffer.str();

    return outputString;
}