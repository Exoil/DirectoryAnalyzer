#include "FileInformation.hpp"

using namespace Analyzer;

DirectoryInformation::DirectoryInformation(std::filesystem::path pathToFile)
    : BaseFileInformation(pathToFile)
{
    if (!pathToFile.empty())
        SetInformation();
}

void DirectoryInformation::SetInformation()
{
    BaseFileInformation::SetInformation();
    countElementContent = std::filesystem::hard_link_count(path);
}

std::string DirectoryInformation::ToString()
{
    std::stringstream buffer;
    buffer << "FileType: Directory ";
    buffer << BaseFileInformation::ToString() << " ";
    buffer << "Count contnent " << countElementContent << " ";
    std::string outputString = buffer.str();

    return outputString;
}